#include "stdafx.h"
#include "CSketch.h"
#include <iostream>

#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32
#define RADIUS 5
#define DEADZONE 4

CSketch::CSketch(cv::Size size, int comport) {
	control.init_com();
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	stickval = cv::Point(_canvas.size().width/2, _canvas.size().height/2);
}

CSketch::~CSketch() {

}

void CSketch::update() {
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}

	// Get stick vals
	cv::Point tempPoint = cv::Point((control.get_analog(X_JOYSTICK) * 100) - 50, (control.get_analog(Y_JOYSTICK) * -100) + 50);
	
	if (tempPoint.x > -DEADZONE && tempPoint.x < DEADZONE) {
		tempPoint.x = 0;
	}
	if (tempPoint.y > -DEADZONE && tempPoint.y < DEADZONE) {
		tempPoint.y = 0;
	}

	stickval += tempPoint/5;

	if (stickval.x >= _canvas.size().width) {
		stickval.x = _canvas.size().width - RADIUS;
	}
	else if (stickval.x <= 0) {
		stickval.x = RADIUS;
	}
	if (stickval.y >= _canvas.size().height) {
		stickval.y = _canvas.size().height - RADIUS;
	}
	else if (stickval.y <= 0) {
		stickval.y = RADIUS;
	}

	static cv::Point prevStickval = stickval;
	
	// Get button press
	if (control.get_button(S1, 0)) {
		// Change colour
		const int maxIterator = (sizeof(colourArr) / sizeof(colourArr[0])) - 1;
		static int currIterator = 0;
		if (currIterator < maxIterator) {
			currIterator++;
		}
		else {
			currIterator = 0;
		}

		colour = colourArr[currIterator];

		control.set_data(0, 37, 0);
		control.set_data(0, 38, 0);
		control.set_data(0, 39, 0);
		control.set_data(0, 37 + currIterator, 1);

	}
	else if (control.get_button(S2, 1)) {
		// Empty current frame
		_canvas = cv::Mat::zeros(cv::Size(_canvas.size()), CV_8UC3);
	}

	//cv::circle(_canvas, stickval, 1, colour, 1, cv::LINE_AA);
	cv::line(_canvas, prevStickval, stickval, colour, RADIUS);
	prevStickval = stickval;
}

void CSketch::draw() {
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}

	cv::imshow("Etch/Sketch", _canvas);
}