#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::cout << CV_VERSION << std::endl;

  std::string img_path = "E:\\ExposureDetect\\imgs\\35.jpg";

  cv::Mat img = cv::imread(img_path);

  cv::Mat src_split{};
  std::vector<cv::Mat> vec{};
  cv::cvtColor(img, src_split, cv::COLOR_BGR2HLS);
  cv::split(src_split, vec);
  cv::Mat src_L = vec.at(1).clone();

  cv::cvtColor(img, src_split, cv::COLOR_BGR2HSV);
  cv::split(src_split, vec);
  cv::Mat src_V = vec.at(2);

  cv::namedWindow("img", cv::WINDOW_NORMAL);
  cv::imshow("img", img);

  cv::namedWindow("src_L", cv::WINDOW_NORMAL);
  cv::imshow("src_L", src_L);
  cv::namedWindow("src_V", cv::WINDOW_NORMAL);
  cv::imshow("src_V", src_V);

  cv::waitKey();

  return 0;
}