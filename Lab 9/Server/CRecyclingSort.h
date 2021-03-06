#pragma once
#include "Server.h"
#include "CBase4618.h"

enum CMDS {
 TOGGLE = 't',
 LEFT = 'l',
 RIGHT = 'r'
 };

enum pins {
 BUTTON_LEFT = 23,
 BUTTON_MIDDLE = 24,
 BUTTON_RIGHT = 25,

 LED_LEFT = 8,
 LED_MIDDLE = 7,
 LED_RIGHT = 12,

 SERVO_LEFT = 16,
 SERVO_MIDDLE = 21,
 SERVO_RIGHT = 20
};

enum servoEnum {
 POS_MIDDLE = 1500,
 POS_LEFT = 2500,
 POS_RIGHT = 500,
 WAIT_TIME = 1000
 };

enum ballType {NOTHING, PINK, BLUE, GREEN, YELLOW};

class CRecyclingSort : public CBase4618 {
private:
	Server server;

    bool enabled = false;
    int manualsort = -1;

    cv::Scalar _bound_upper = cv::Scalar(179,255,255);
    cv::Scalar _bound_lower = cv::Scalar(0,0,0);
    double _erodeSize = 7;

    const cv::Scalar _pink_ball_upper = cv::Scalar(175.9, 255, 255);
    const cv::Scalar _pink_ball_lower = cv::Scalar(167.6, 109.7, 225.3);

    const cv::Scalar _blue_ball_upper = cv::Scalar(95.7, 255, 154.2);
    const cv::Scalar _blue_ball_lower = cv::Scalar(80.1, 155.7, 8.9);

    const cv::Scalar _green_ball_upper = cv::Scalar(59.3, 255, 255);
    const cv::Scalar _green_ball_lower = cv::Scalar(50, 131.9, 131.9);

    const cv::Scalar _yellow_ball_upper = cv::Scalar(39.5, 255, 255);
    const cv::Scalar _yellow_ball_lower = cv::Scalar(31.2, 207.6, 94.9);

    cv::VideoCapture _video;
    cv::Mat _settings, _mask;
    void update() override;
    void draw() override;

    void ui_elements();
    int segment_image();
    void sort_ball(int ball);
    void handleIO();
public:
    CRecyclingSort();
    ~CRecyclingSort();
};
