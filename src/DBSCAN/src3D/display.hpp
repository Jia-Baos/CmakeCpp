#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "./dbscan.hpp"
#include <opencv2/opencv.hpp>

struct DisplayInfo {
  float x_min = 0.0;
  float x_max = 0.0;
  float y_min = 0.0;
  float y_max = 0.0;
  float z_min = 0.0;
  float z_max = 0.0;
};

DisplayInfo getBorder(const std::vector<Point> &vec) {

  DisplayInfo info{};
  for (auto iter : vec) {

    // x
    if (iter.x > info.x_max) {
      info.x_max = iter.x;
    }
    if (iter.x < info.x_min) {
      info.x_min = iter.x;
    }

    // y
    if (iter.y > info.y_max) {
      info.y_max = iter.y;
    }
    if (iter.y < info.y_min) {
      info.y_min = iter.y;
    }

    // z
    if (iter.z > info.z_max) {
      info.z_max = iter.z;
    }
    if (iter.z < info.z_min) {
      info.z_min = iter.z;
    }
  }

  return info;
}

bool getPointsFig(const std::vector<Point> &vec, cv::Mat &dst) {
  // Get border
  auto info = getBorder(vec);
  std::cout << "info.x_min: " << info.x_min << ", info.x_max: " << info.x_max
            << ", info.y_min: " << info.y_min << ", info.y_max: " << info.y_max
            << std::endl;

  // Initialize the fig
  dst = cv::Mat::zeros(640, 640, CV_8UC3);

  // max classes is 100
  cv::RNG rng(10086);
  std::vector<cv::Vec3b> colors;
  for (int i = 0; i < 100; i++) {
    cv::Vec3b vec3 = cv::Vec3b(rng.uniform(0, 256), rng.uniform(0, 256),
                               rng.uniform(0, 256));
    colors.push_back(vec3);
  }

  for (auto iter : vec) {
    if (iter.clusterID != -1) {
      cv::Point2f point =
          cv::Point2f(640 * (iter.x - info.x_min) / (info.x_max - info.x_min),
                      640 * (iter.y - info.y_min) / (info.y_max - info.y_min));
      cv::circle(dst, point, 1, colors[iter.clusterID], 4);
    }
  }

  return true;
}

#endif // DISPLAY_HPP