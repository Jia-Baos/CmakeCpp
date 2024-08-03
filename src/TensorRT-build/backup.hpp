// /*
// TensorRT build engine的过程
// 1. 创建builder
// 2. 创建网络定义：builder ---> network
// 3. 配置参数：builder ---> config
// 4. 生成engine：builder ---> engine (network, config)
// 5. 序列化保存：engine ---> serialize
// 6. 释放资源：delete
// */

// #include <iostream>
// #include <fstream>
// #include <cassert>
// #include <vector>

// #include <NvInfer.h>

// // logger用来管控打印日志级别
// // TRTLogger继承自nvinfer1::ILogger
// class TRTLogger : public nvinfer1::ILogger
// {
//     void log(Severity severity, const char *msg) noexcept override
//     {
//         // 屏蔽INFO级别的日志
//         if (severity != Severity::kINFO)
//             std::cout << msg << std::endl;
//     }
// } gLogger;

// // 保存权重
// void saveWeights(const std::string &filename, const float *data, int size)
// {
//     std::ofstream outfile(filename, std::ios::binary);
//     assert(outfile.is_open() && "save weights failed");  // assert断言，如果条件不满足，就会报错
//     outfile.write((char *)(&size), sizeof(int));         // 保存权重的大小
//     outfile.write((char *)(data), size * sizeof(float)); // 保存权重的数据
//     outfile.close();
// }
// // 读取权重
// std::vector<float> loadWeights(const std::string &filename)
// {
//     std::ifstream infile(filename, std::ios::binary);
//     assert(infile.is_open() && "load weights failed");
//     int size;
//     infile.read((char *)(&size), sizeof(int));                // 读取权重的大小
//     std::vector<float> data(size);                            // 创建一个vector，大小为size
//     infile.read((char *)(data.data()), size * sizeof(float)); // 读取权重的数据
//     infile.close();
//     return data;
// }

// int main()
// {
//     // ======= 1. 创建builder =======
//     TRTLogger logger;
//     nvinfer1::IBuilder *builder = nvinfer1::createInferBuilder(logger);

//     // ======= 2. 创建网络定义：builder ---> network =======

//     // 显性batch
//     // 1 << 0 = 1，二进制移位，左移0位，相当于1（y左移x位，相当于y乘以2的x次方）
//     auto explicitBatch = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
//     // 调用createNetworkV2创建网络定义，参数是显性batch
//     nvinfer1::INetworkDefinition *network = builder->createNetworkV2(explicitBatch);

//     // 定义网络结构
//     // mlp多层感知机：input(1,3,1,1) --> fc1 --> sigmoid --> output (2)

//     // 创建一个input tensor ，参数分别是：name, data type, dims
//     const int input_size = 3;
//     const int output_size = 2;
//     nvinfer1::ITensor *input = network->addInput("data", nvinfer1::DataType::kFLOAT, nvinfer1::Dims4{1, input_size, 1, 1});

//     // 创建全连接层fc1
//     // weight and bias
//     const float *fc1_weight_data = new float[input_size * 2]{0.1, 0.2, 0.3, 0.4, 0.5, 0.6};
//     const float *fc1_bias_data = new float[2]{0.1, 0.5};

//     // 将权重保存到文件中，演示从别的来源加载权重
//     saveWeights("/home/jia-baos/Project-CPP/CmakeTensorRT/model/fc1.wts", fc1_weight_data, 6);
//     saveWeights("/home/jia-baos/Project-CPP/CmakeTensorRT/model/fc1.bias", fc1_bias_data, 2);

//     // 读取权重
//     auto fc1_weight_vec = loadWeights("/home/jia-baos/Project-CPP/CmakeTensorRT/model/fc1.wts");
//     auto fc1_bias_vec = loadWeights("/home/jia-baos/Project-CPP/CmakeTensorRT/model/fc1.bias");

//     // 转为nvinfer1::Weights类型，参数分别是：data type, data, size
//     nvinfer1::Weights fc1_weight{nvinfer1::DataType::kFLOAT, fc1_weight_vec.data(), fc1_weight_vec.size()};
//     nvinfer1::Weights fc1_bias{nvinfer1::DataType::kFLOAT, fc1_bias_vec.data(), fc1_bias_vec.size()};

//     // 调用addFullyConnected创建全连接层，参数分别是：input tensor, output size, weight, bias，此函数8.4后废除，采用 IMatrixMultiplyLayer 和 IElementwiseLayer 代替
//     int32_t const batch = input->getDimensions().d[0]; // 添加一个 Shuffle 层来重塑输入为二维矩阵，为矩阵乘法做准备
//     int32_t const mmInputs = input->getDimensions().d[1] * input->getDimensions().d[2] * input->getDimensions().d[3];
//     nvinfer1::IShuffleLayer *inputReshape = network->addShuffle(*input);
//     inputReshape->setReshapeDimensions(nvinfer1::Dims2{mmInputs, batch});

//     nvinfer1::IConstantLayer *fc1_weight_layer = network->addConstant(nvinfer1::Dims2{output_size, input_size}, fc1_weight);
//     nvinfer1::IMatrixMultiplyLayer *matrix_multi_layer = network->addMatrixMultiply(*fc1_weight_layer->getOutput(0), nvinfer1::MatrixOperation::kNONE,
//                                                                                     *inputReshape->getOutput(0), nvinfer1::MatrixOperation::kNONE);

//     nvinfer1::IConstantLayer *fc1_bias_layer = network->addConstant(nvinfer1::Dims2{output_size, 1}, fc1_bias);
//     nvinfer1::IElementWiseLayer *bias_add_later = network->addElementWise(*matrix_multi_layer->getOutput(0), *fc1_bias_layer->getOutput(0), nvinfer1::ElementWiseOperation::kSUM);

//     std::cout << *bias_add_later->getOutput(0)->getDimensions().d << std::endl;

//     // 添加sigmoid激活层，参数分别是：input tensor, activation type（激活函数类型）
//     nvinfer1::IActivationLayer *sigmoid_layer = network->addActivation(*bias_add_later->getOutput(0), nvinfer1::ActivationType::kSIGMOID);

//     std::cout << *sigmoid_layer->getOutput(0)->getDimensions().d << std::endl;

//     // 设置输出名字
//     sigmoid_layer->getOutput(0)->setName("output");
//     // 标记输出，没有标记会被当成顺时针优化掉
//     network->markOutput(*sigmoid_layer->getOutput(0));

//     // ====== 3. 配置参数：builder ---> config ======
//     // 添加配置参数，告诉TensorRT应该如何优化网络
//     nvinfer1::IBuilderConfig *config = builder->createBuilderConfig();
//     // 设置最大工作空间大小，单位是字节
//     config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE, 1 << 28); // 256MiB

//     // 使用 buildSerializedNetwork 构建并序列化网络
//     nvinfer1::IHostMemory *serialized_engine = builder->buildSerializedNetwork(*network, *config);
//     if (!serialized_engine)
//     {
//         std::cerr << "build engine failed" << std::endl;
//         // 将之前堆内存分配的变量释放
//         std::cerr << "build engine failed" << std::endl;
//         delete[] fc1_weight_data;
//         delete[] fc1_bias_data;
//         delete config;
//         delete network;
//         delete builder;
//         return -1;
//     }

//     // 存入文件
//     std::ofstream outfile("/home/jia-baos/Project-CPP/CmakeTensorRT/model/mlp.engine", std::ios::binary);
//     assert(outfile.is_open() && "Failed to open file for writing");
//     outfile.write((char *)serialized_engine->data(), serialized_engine->size());
//     outfile.close();

//     delete[] fc1_weight_data;
//     delete[] fc1_bias_data;

//     delete config;
//     delete network;
//     delete builder;

//     std::cout << "engine文件生成成功！" << std::endl;

//     return 0;
// }