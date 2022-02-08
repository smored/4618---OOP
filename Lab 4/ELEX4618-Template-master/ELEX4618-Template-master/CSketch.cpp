#include "stdafx.h"
#include "CSketch.h"

CControl control;

CSketch::CSketch(cv::Size size, int comport) {
	CControl::init_com(comport);
	cv::Mat::zeros(size, CV_8UC3);
}

void CSketchupdate() {
	CControl::get_analog(1);
}