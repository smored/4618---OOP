#pragma once
#include "CBase4618.h"

class CRecyclingSort : public CBase4618 {
private:
    cv::Scalar _bound_upper = cv::Scalar(179,255,255);
    cv::Scalar _bound_lower = cv::Scalar(0,0,0);
    double _erodeSize = 7;

    const cv::Scalar _pink_ball_upper = cv::Scalar(175.9, 255, 255);
    const cv::Scalar _pink_ball_lower = cv::Scalar(167.6, 109.7, 225.3);

    const cv::Scalar _blue_ball_upper = cv::Scalar(95.7, 255, 154.2);
    const cv::Scalar _blue_ball_lower = cv::Scalar(80.1, 155.7, 8.9);

    const cv::Scalar _green_ball_upper = cv::Scalar(59.3, 255, 255);
    const cv::Scalar _green_ball_lower = cv::Scalar(50, 131.9, 131.9);

    const cv::Scalar _yellow_ball_upper = cv::Scalar(51, 164.6, 163.1);
    const cv::Scalar _yellow_ball_lower = cv::Scalar(37.5, 68.2, 108.2);

    cv::VideoCapture _video;
    cv::Mat _settings, _mask;
    void update() override;
    void draw() override;

    void ui_elements();
    void segment_image();
public:
    CRecyclingSort();
    ~CRecyclingSort();
};
