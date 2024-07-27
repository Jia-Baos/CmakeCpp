#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main(int argc, char *argv[]) {
  // read img
  std::string img_path = "E:\\ExposureDetect-test\\imgs\\1.jpg";
  cv::Mat img = cv::imread(img_path, 0);

  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8));
  cv::morphologyEx(img, img, cv::MORPH_TOPHAT, kernel);

  // cv::Sobel(img, img, CV_8UC1, 2, 2, 5);

  cv::namedWindow("img", cv::WINDOW_NORMAL);
  cv::imshow("img", img);
  cv::waitKey();

  return 0;
}
