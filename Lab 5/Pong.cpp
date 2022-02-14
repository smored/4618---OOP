#include "stdafx.h"
#include "Pong.h"

Pong::Pong(cv::Size size, int comport) {
	control.init_com(7);
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	stickval = cv::Point(_canvas.size().width / 2, _canvas.size().height / 2);
}

Pong::~Pong() {

}

void Pong::update() {

}


void Pong::draw() {

}