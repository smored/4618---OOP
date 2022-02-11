#include "stdafx.h"
#include "CSketch.h"
#include <iostream>

#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32

CSketch::CSketch(cv::Size size, int comport) {
	control.init_com();
	_canvas = cv::Mat::zeros(size, CV_8UC3);
}

CSketch::~CSketch() {

}

void CSketch::update() {
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}

	// Get stick vals
	stickval.x = control.get_analog(X_JOYSTICK)*(_canvas.size().width);
	stickval.y = _canvas.size().height - control.get_analog(Y_JOYSTICK)*(_canvas.size().height);
	static cv::Point prevStickval = stickval;
	
	// Get button press
	if (control.get_button(S1)) {
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

		//control.set_data(0, 37 + currIterator, 1);


	}
	else if (control.get_button(S2)) {
		// Empty current frame
		_canvas = cv::Mat::zeros(cv::Size(_canvas.size()), CV_8UC3);
	}

	//cv::circle(_canvas, stickval, 1, colour, 1, cv::LINE_AA);
	cv::line(_canvas, prevStickval, stickval, colour, 1);
	prevStickval = stickval;
}

void CSketch::draw() {
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}

	cv::imshow("Etch/Sketch", _canvas);
}