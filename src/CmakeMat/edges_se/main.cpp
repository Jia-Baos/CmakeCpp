#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include <string>

int main(int argc, char *argv[]) {
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
  std::cout << "hello world..." << std::endl;
  std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

  std::string image_path =
      "D:\\CmakeProject\\CmakeMat\\edges_se\\frame_0001.png";
  std::string model_path = "D:\\CmakeProject\\CmakeMat\\edges_se\\model.yml";
  std::string edges_path =
      "D:\\CmakeProject\\CmakeMat\\edges_se\\frame_0001.txt";

  cv::Mat image = cv::imread(image_path);
  image.convertTo(image, CV_32FC3, 1 / 255.0);

  cv::Mat edges;
  cv::Ptr<cv::ximgproc::StructuredEdgeDetection> pDollar =
      cv::ximgproc::createStructuredEdgeDetection(model_path);
  pDollar->detectEdges(image, edges);

  cv::normalize(edges, edges, 0.0, 1.0, cv::NORM_MINMAX, -1, cv::Mat());
  edges.convertTo(edges, CV_8UC1, 255.0);

  // // 设置图像叠加显示
  // cv::Mat heatmap{};
  // cv::applyColorMap(edges, heatmap, cv::COLORMAP_JET);

  cv::namedWindow("heatmap", cv::WINDOW_NORMAL);
  cv::imshow("heatmap", edges);
  cv::waitKey();

  // const int w = edges.cols;
  // const int h = edges.rows;

  // FILE *stream_write = fopen(edges_path.c_str(), "wb");
  // if (stream_write == nullptr)
  //   std::cout << "Failed to open files..." << std::endl;

  // std::cout << "	malloc..." << std::endl;
  // float *arr_write = (float *)malloc(sizeof(float) * w * h);
  // for (int i = 0; i < h; i++) {
  //   for (int j = 0; j < w; j++) {
  //     const int index = i * w + j;
  //     *(arr_write + index) = edges.at<float>(i, j);
  //   }
  // }

  // fwrite(arr_write, sizeof(float), w * h, stream_write);
  // fclose(stream_write);
  // free(arr_write);
  // arr_write = nullptr;
  // std::cout << "	free..." << std::endl;

  // FILE *stream_read = fopen(edges_path.c_str(), "rb");
  // if (stream_read == nullptr)
  // 	std::cout << "Failed to open files..." << std::endl;

  // std::cout << "malloc..." << std::endl;
  // float *arr_read = (float *)malloc(sizeof(float) * w * h);
  // rewind(stream_read);
  // fread(arr_read, sizeof(float), w * h, stream_read);
  // cv::Mat edges_rocover = cv::Mat::zeros(h, w, CV_32FC1);
  // for (int i = 0; i < h; i++)
  // {
  // 	for (int j = 0; j < w; j++)
  // 	{
  // 		const int index = i * w + j;
  // 		edges_rocover.at<float>(i, j) = *(arr_read + index);
  // 	}
  // }
  // fclose(stream_read);
  // free(arr_read);
  // arr_read = nullptr;
  // std::cout << "free..." << std::endl;

  return 0;
}
