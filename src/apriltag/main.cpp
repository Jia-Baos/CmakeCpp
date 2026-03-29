#include <iostream>
#include <opencv2/opencv.hpp>

#include "apriltag.h"
#include "tag36h11.h"
#include "common/image_u8.h"

int main()
{
    std::string img_path = "/home/jia-baos/Project-Cpp/CmakeCpp/data/apriltag_bound.jpg";

    cv::Mat img_rgb = cv::imread(img_path);

    apriltag_family_t *family = tag36h11_create();
    apriltag_detector_t *detector = apriltag_detector_create();
    apriltag_detector_add_family(detector, family);

    cv::Mat gray;
    cv::cvtColor(img_rgb, gray, cv::COLOR_BGR2GRAY);
    image_u8_t t_img_gray = { gray.cols, gray.rows, gray.cols, gray.data };
    zarray_t *detections = apriltag_detector_detect(detector, &t_img_gray);

    std::cout << "detections size: " << zarray_size(detections) << std::endl;

    // get points
    for (int i = 0; i < zarray_size(detections); i++) {
        apriltag_detection_t *det;
        zarray_get(detections, i, &det);

        // point ordering
        //        3-------2
        //  y     | TAG 1 |
        // ^      0-------1
        // |-->x
        const float tag_size = 0.12;    // 二维码的宽度
        const float tag_spacing = 0.3;  // 二维码中心之间的间距
        const float tag_pos_x = 0.3;    // 两个二维码中心连线的中点在车体坐标系的x坐标
        const float tag_pos_y = 0.0;    // 两个二维码中心连线的中点在车体坐标系的y坐标
        const float tag_pos_z = 0.5216; // 两个二维码中心连线的中点在车体坐标系的z坐标

        std::cout << "id: " << det->id << std::endl;
        std::cout << "p0: " << det->p[0][0] << ", " << det->p[0][1] << std::endl;
        std::cout << "p1: " << det->p[1][0] << ", " << det->p[1][1] << std::endl;
        std::cout << "p2: " << det->p[2][0] << ", " << det->p[2][1] << std::endl;
        std::cout << "p3: " << det->p[3][0] << ", " << det->p[3][1] << std::endl;

        cv::circle(img_rgb, cv::Point(det->p[0][0], det->p[0][1]), 5, cv::Scalar(0, 0, 0xff), -1);
        cv::line(img_rgb, cv::Point(det->p[0][0], det->p[0][1]),cv::Point(det->p[1][0], det->p[1][1]),cv::Scalar(0, 0xff, 0), 2);
        cv::line(img_rgb, cv::Point(det->p[0][0], det->p[0][1]),cv::Point(det->p[3][0], det->p[3][1]),cv::Scalar(0, 0, 0xff), 2);
        cv::line(img_rgb, cv::Point(det->p[1][0], det->p[1][1]),cv::Point(det->p[2][0], det->p[2][1]),cv::Scalar(0xff, 0, 0), 2);
        cv::line(img_rgb, cv::Point(det->p[2][0], det->p[2][1]),cv::Point(det->p[3][0], det->p[3][1]),cv::Scalar(0xff, 0, 0), 2);
        std::stringstream ss;
        ss << det->id;
        cv::String text = ss.str();
        int baseline;
        cv::Size textsize = cv::getTextSize(text,cv::FONT_HERSHEY_SCRIPT_SIMPLEX,1.0,2,&baseline);
        putText(img_rgb, text, cv::Point(det->c[0]-textsize.width/2,det->c[1]+textsize.height/2),cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, cv::Scalar(0xff, 0x99, 0), 2);
    }

    apriltag_detections_destroy(detections);
    apriltag_detector_destroy(detector);
    tag36h11_destroy(family);

    // cv::namedWindow("img_rgb", cv::WINDOW_NORMAL);
    // cv::imshow("img_rgb", img_rgb);
    // cv::waitKey(0);

    cv::imwrite("img_rgb.jpg", img_rgb);

    return 0;
}