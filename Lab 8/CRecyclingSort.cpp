#include "CRecyclingSort.h"
#define FRAME_HEIGHT 300 // for video capture resolution
#define RECT_AREA_POSITIVE 10000
#include "cvui.h"

CRecyclingSort::CRecyclingSort() {
    // open video capture
    _video.open(-1, cv::CAP_ANY);

    // set camera resolution
    const cv::Size canvasSize = cv::Size(FRAME_HEIGHT*16/9, FRAME_HEIGHT);
    _video.set(cv::CAP_PROP_FRAME_WIDTH, canvasSize.width);
    _video.set(cv::CAP_PROP_FRAME_HEIGHT, canvasSize.height);

    // associate & init canvases
    _canvas = cv::Mat::zeros(canvasSize, CV_8UC3);
    cv::imshow("RGB", _canvas);
    _mask = cv::Mat::zeros(canvasSize, CV_8UC3);
    cv::imshow("MASK", _mask);
    _settings = cv::Mat::zeros(canvasSize, CV_8UC3);
    cv::imshow("SETTINGS", _settings);

    // init cvui
    cvui::init("SETTINGS");
}

CRecyclingSort::~CRecyclingSort() {
//close video capture
_video.release();
cv::destroyAllWindows();
}

void CRecyclingSort::draw() {
    _video >> _canvas;
    if (_canvas.empty()) {
        std::cerr << "ERROR; blank frame\n";
    }

    ui_elements();
    segment_image();

    cv::imshow("RGB", _canvas);
    cv::imshow("MASK", _mask);
    cv::imshow("SETTINGS", _settings);
}

void CRecyclingSort::update() {
// not implemented atm
}

void CRecyclingSort::ui_elements() {
    _settings = cv::Mat::zeros(_settings.size(), CV_8UC3);
    cvui::text(_settings, 20, 20, "HSV Lower");
    cvui::trackbar(_settings, 0, 40, 200, &_bound_lower[0], (double) 0, (double) 179); // upper hue
    cvui::trackbar(_settings, 0, 85, 200, &_bound_lower[1], (double) 0, (double) 255);// upper saturation
    cvui::trackbar(_settings, 0, 130, 200, &_bound_lower[2], (double) 0, (double) 255);// upper value

    cvui::text(_settings, 270, 20, "HSV Upper");
    cvui::trackbar(_settings, 250, 40, 200, &_bound_upper[0], (double) 0, (double) 179);// lower hue
    cvui::trackbar(_settings, 250, 85, 200, &_bound_upper[1], (double) 0, (double) 255);// lower saturation
    cvui::trackbar(_settings, 250, 130, 200, &_bound_upper[2], (double) 0, (double) 255);// lower value

    cvui::text(_settings, 20, 200, "ERODE SIZE");
    cvui::trackbar(_settings, 0, 220, 200, &_erodeSize, (double) 1, (double) 10);// erosion size diameter
}

void CRecyclingSort::segment_image() {
    // segment into hsv
    cv::Mat hsv;
    cv::cvtColor(_canvas, hsv, cv::COLOR_BGR2HSV);
    cv::imshow("HSV", hsv);
    //cv::inRange(hsv, _bound_lower, _bound_upper, _mask);

    // check bounding rects
    //cv::contourArea(_mask);
    cv::inRange(hsv, _pink_ball_lower, _pink_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect pink_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, pink_rect, RED);

    cv::inRange(hsv, _blue_ball_lower, _blue_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect blue_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, blue_rect, BLUE);

    cv::inRange(hsv, _green_ball_lower, _green_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect green_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, green_rect, cv::Scalar(0,255,0));

    cv::inRange(hsv, _yellow_ball_lower, _yellow_ball_upper, _mask);
    cv::erode(_mask, _mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7,7)));
    cv::Rect yellow_rect = cv::boundingRect(_mask);
    cv::rectangle(_canvas, yellow_rect, cv::Scalar(0,255,255));



    if (pink_rect.area() > RECT_AREA_POSITIVE) {
    std::cout << "PINK BALL DETECTED" << std::endl;
    } else if (blue_rect.area() > RECT_AREA_POSITIVE) {
    std::cout << "BLUE BALL DETECTED" << std::endl;
    } else if (green_rect.area() > RECT_AREA_POSITIVE) {
    std::cout << "GREEN BALL DETECTED" << std::endl;
    } else if (yellow_rect.area() > RECT_AREA_POSITIVE) {
    std::cout << "YELLOW BALL DETECTED" << std::endl;
    } else {
    std::cout << "NOTHING DETECTED" << std::endl;
    }
}
