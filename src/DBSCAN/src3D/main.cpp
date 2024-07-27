#include "dbscan.hpp"
#include "display.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

#define MINIMUM_POINTS 4      // minimum number of cluster
#define EPSILON (0.75 * 0.75) // distance for clustering, metre^2

void readBenchmarkData(std::vector<Point> &points) {
  // load point cloud
  const std::string path =
      "D:\\CmakeProject\\DBSCAN\\src3D\\benchmark_hepta.txt";
  FILE *stream = fopen(path.c_str(), "r");
  if (stream == 0) {
    fprintf(stderr, "error: could not open file \n");
    exit(1);
  }

  unsigned int minpts, num_points, cluster, i = 0;
  double epsilon;
  fscanf(stream, "%u\n", &num_points);
  std::cout << "num_points: " << num_points << std::endl;

  Point *p = (Point *)calloc(num_points, sizeof(Point));

  while (i < num_points) {
    fscanf(stream, "%f,%f,%f,%d\n", &(p[i].x), &(p[i].y), &(p[i].z), &cluster);
    // std::cout << "p[i].x: " << p[i].x << ", p[i].y: " << p[i].y
    //           << ", p[i].z: " << p[i].z << std::endl;

    p[i].clusterID = UNCLASSIFIED;
    points.push_back(p[i]);
    ++i;
  }

  free(p);
  fclose(stream);
}

void printResults(std::vector<Point> &points, int num_points) {
  int i = 0;
  printf("Number of points: %u\n"
         " x     y     z     cluster_id\n"
         "-----------------------------\n",
         num_points);
  while (i < num_points) {
    // printf("%5.2lf %5.2lf %5.2lf: %d\n", points[i].x, points[i].y,
    // points[i].z,
    //        points[i].clusterID);
    ++i;
  }
}

int main() {
  std::vector<Point> points;

  // read point data
  readBenchmarkData(points);

  // constructor
  DBSCAN ds(MINIMUM_POINTS, EPSILON, points);

  // main loop
  ds.run();

  // result of DBSCAN algorithm
  printResults(ds.m_points, ds.getTotalPointSize());

  cv::Mat dst{};
  getPointsFig(ds.m_points, dst);

  cv::namedWindow("Points Fig", cv::WINDOW_NORMAL);
  cv::imshow("Points Fig", dst);
  cv::waitKey();

  return 0;
}
