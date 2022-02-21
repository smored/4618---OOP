#include "stdafx.h"
#include "CAsteroid.h"

#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32

//TODO : add missles and asteroids instantiation
CAsteroid::CAsteroid(cv::Size size) {
	// Open Com port
	control.init_com();

	// Open canvas
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	cv::imshow("Asteroids", _canvas);

	// Instantiate important objects
	_cship = CShip();
	init_game();
}

CAsteroid::~CAsteroid() {

}

void CAsteroid::init_game() {
	_cship.set_pos(cv::Point2f(_canvas.size().width / 2.0f, _canvas.size().height / 2.0f));
	
}

void CAsteroid::update() {
	// TODO: make acceleration-based movement
	_canvas = cv::Mat::zeros(_canvas.size(), CV_8UC3);
	cv::Point joystickPos = cv::Point((control.get_analog(X_JOYSTICK) * 100) - 50, (control.get_analog(Y_JOYSTICK) * -100) + 50);
	_cship.set_vel(joystickPos);
	_cship.move();

	if (control.get_button(S1, 0)) {
		// Fire Missile
	}
	else if (control.get_button(S2, 1)) {
		// Reset Button
	}
}

void CAsteroid::draw() {
	_cship.draw(_canvas);
}