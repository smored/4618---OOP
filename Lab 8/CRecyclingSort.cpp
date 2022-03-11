#include "CRecyclingSort.h"
#define FRAME_HEIGHT 180 // for video capture resolution

CRecyclingSort::CRecyclingSort(cv::Size settingsSize) {
// open video capture
_video.open(0, cv::CAP_V4L2);

// set camera resolution
const cv::Size canvasSize = cv::Size(FRAME_HEIGHT*16/9, FRAME_HEIGHT);
_video.set(cv::CAP_PROP_FRAME_WIDTH, canvasSize.x);
_video.set(cv::CAP_PROP_FRAME_HEIGHT, canvasSize.y);

// initialize cvui
cvui::init();

// associate & init canvases
_canvas = cv::Mat::zeros(canvasSize, CV_8UC3);
cv::imshow(_canvas, "RGB");

_mask = cv::Mat::zeros(canvasSize, CV_8UC3);
cv::imshow(_mask, "HSV Mask");

_settings = cv::Mat::zeros(settingsSize, CV_8UC3);
cv::imshow(_settings, "CVUI");
}

CRecyclingSort::~CRecyclingSort() {
//close video capture
_video.release();
}

CRecyclingSort::draw() {
    drawUI();
    cv::imshow();
}

CRecyclingSort::update() {

}

CRecyclingSort::drawUI() {
    // draw trackbars and ui elements
    //cvui::trackbar();
}
