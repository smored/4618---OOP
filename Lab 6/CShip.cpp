#include "stdafx.h"
#include "CShip.h"
#include "CBase4618.h"

CShip::CShip() {
	this->set_lives(10);
	this->_position = cv::Point2f(0, 0);
	this->_radius = 25;
	this->_draw_colour = cv::Scalar(255, 255, 255);
}

CShip::~CShip() {

}

#define MAXVEL 500.0f
#define DECELERATE 5.0f

void CShip::move(double deltaT) {

	// Clamp velocity
	CBase4618::clamp(_velocity, MAXVEL, -MAXVEL);

	// Decelerate ship
	if (_velocity.x > 0) {
		if (_velocity.x - DECELERATE <= 0) {
			_velocity.x = 0;
		}
		else {
			_velocity.x -= DECELERATE;
		}
	}
	if (_velocity.x < 0) {
		if (_velocity.x + DECELERATE >= 0) {
			_velocity.x = 0;
		}
		else {
			_velocity.x += DECELERATE;
		}
	}
	if (_velocity.y > 0) {
		if (_velocity.y - DECELERATE <= 0) {
			_velocity.y = 0;
		}
		else {
			_velocity.y -= DECELERATE;
		}
	}
	if (_velocity.y < 0) {
		if (_velocity.y + DECELERATE >= 0) {
			_velocity.y = 0;
		}
		else {
			_velocity.y += DECELERATE;
		}
	}

	//std::cout << "Acc: " << _acceleration << " Vel: " << _velocity << " Pos: " << _position << std::endl;
	_position += _velocity * deltaT;
}