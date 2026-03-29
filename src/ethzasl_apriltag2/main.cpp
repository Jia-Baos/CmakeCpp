#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/opencv.hpp>

#include <apriltags/TagDetector.h>
#include <apriltags/TagFamily.h>
#include <apriltags/Tag36h11.h>

bool isImageIdentical(const cv::Mat& img1, const cv::Mat& img2) {

    std::cout << "img1's size: " << img1.size() << std::endl;
    std::cout << "img2's size: " << img2.size() << std::endl;

    if (img1.size() != img2.size() || img1.channels() != img2.channels())
    {
        return false;
    }
    cv::Mat diff;
    cv::compare(img1, img2, diff, cv::CMP_NE);
    
    // 处理多通道情况：将差异图转为单通道（灰度图）
    cv::Mat diff_gray;
    if (diff.channels() > 1) {
        cv::cvtColor(diff, diff_gray, cv::COLOR_BGR2GRAY); // BGR转灰度（如果是RGB则用COLOR_RGB2GRAY）
    } else {
        diff_gray = diff; // 单通道直接使用
    }

    // 统计非零元素数量，为0则表示图像完全一致
    return cv::countNonZero(diff_gray) == 0;
}

int main()
{
    std::string img_path = "/home/jia-baos/Project-Cpp/CmakeCpp/data/apriltag_multi.jpg";

    cv::Mat img_rgb = cv::imread(img_path);
    std::cout << "img_rgb channels: " << img_rgb.channels() << std::endl;
    cv::resize(img_rgb, img_rgb, cv::Size(img_rgb.cols / 4, img_rgb.rows / 4));


    {
        cv::Mat test = img_rgb.clone();

        std::cout << "identy " << isImageIdentical(img_rgb, test) << std::endl;
    }

    cv::Mat gray;
    cv::cvtColor(img_rgb, gray, cv::COLOR_BGR2GRAY);
    std::shared_ptr<AprilTags::TagDetector> _tagDetector;
    _tagDetector = std::make_shared<AprilTags::TagDetector>(AprilTags::tagCodes36h11, 2);   // 2 is blackBorder 表示“读码时忽略最外几圈黑边”的圈数
    std::vector<AprilTags::TagDetection> detections = _tagDetector->extractTags(gray);

    std::cout << "detections size: " << detections.size() << std::endl;

    // sort detections by tagId
    std::sort(detections.begin(), detections.end(), AprilTags::TagDetection::sortByIdCompare);

    // get points
    for (int i = 0; i < detections.size(); i++) {
        AprilTags::TagDetection det = detections[i];
        // detections[i].draw(img_rgb);

        std::cout << "id: " << det.id << std::endl;
        // std::cout << "good valid: " << det.good << std::endl;
        // std::cout << "p0: " << det.p[0].first << ", " << det.p[0].second << std::endl;
        // std::cout << "p1: " << det.p[1].first << ", " << det.p[1].second << std::endl;
        // std::cout << "p2: " << det.p[2].first << ", " << det.p[2].second << std::endl;
        // std::cout << "p3: " << det.p[3].first << ", " << det.p[3].second << std::endl;

        cv::circle(img_rgb, cv::Point(det.p[0].first, det.p[0].second), 5, cv::Scalar(0, 0, 0xff), -1);
        cv::line(img_rgb, cv::Point(det.p[0].first, det.p[0].second), cv::Point(det.p[1].first, det.p[1].second), cv::Scalar(0, 0xff, 0), 2);
        cv::line(img_rgb, cv::Point(det.p[0].first, det.p[0].second), cv::Point(det.p[3].first, det.p[3].second), cv::Scalar(0, 0, 0xff), 2);
        cv::line(img_rgb, cv::Point(det.p[1].first, det.p[1].second), cv::Point(det.p[2].first, det.p[2].second), cv::Scalar(0xff, 0, 0), 2);
        cv::line(img_rgb, cv::Point(det.p[2].first, det.p[2].second), cv::Point(det.p[3].first, det.p[3].second), cv::Scalar(0xff, 0, 0), 2);
        std::stringstream ss;
        ss << det.id;
        cv::String text = ss.str();
        int baseline;
        cv::Size textsize = cv::getTextSize(text, cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, 2, &baseline);
        putText(img_rgb, text, cv::Point(det.p[0].first / 2 + det.p[2].first / 2 - textsize.width / 2, det.p[0].second / 2 + det.p[2].second / 2 + textsize.height / 2), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, cv::Scalar(0xff, 0x99, 0), 2);
    }

    // cv::namedWindow("img_rgb", cv::WINDOW_NORMAL);
    // cv::imshow("img_rgb", img_rgb);
    // cv::waitKey(0);

    cv::imwrite("img_rgb.jpg", img_rgb);

    return 0;
}