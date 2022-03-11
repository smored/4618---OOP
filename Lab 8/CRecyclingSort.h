#pragma once
#include "CBase4618.h"

class CRecyclingSort : public CBase4618 {
private:
    int h_upper, h_lower, s_upper, s_lower, v_upper, v_lower;
    cv::VideoCapture _video;
    cv::Mat _mask, _settings;
    void update() override;
    void draw() override;
public:
    CRecyclingSort();
    ~CRecyclingSort();
};
