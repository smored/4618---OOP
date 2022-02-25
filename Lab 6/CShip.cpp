#include "stdafx.h"
#include "CShip.h"
#include "CBase4618.h"

CShip::CShip(cv::Size canvas_size, int ship_size) {
	this->set_lives(10);
	this->_position = cv::Point2f(0, 0);
	this->_radius = ship_size;
	this->_draw_colour = cv::Scalar(255, 255, 255);
	this->_canvas_size = canvas_size;
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

	_position += _velocity * deltaT;

	if (_position.x + _radius > _canvas_size.width) _position.x = _radius;
	if (_position.y + _radius > _canvas_size.height) _position.y = _radius;
	if (_position.x - _radius < 0) _position.x = _canvas_size.width - _radius;
	if (_position.y - _radius < 0) _position.y = _canvas_size.height - _radius;
}

void CShip::draw(cv::Mat& im, cv::Scalar draw_colour) {
	cv::circle(im, _position, _radius, _draw_colour, 3, cv::LINE_AA);
	this->_draw_colour = draw_colour;
}

void CShip::hit() {
	this->_lives -= 1;

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	this->_draw_colour = cv::Scalar(0, 0, 128);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	this->_draw_colour = cv::Scalar(0, 0, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	this->_draw_colour = cv::Scalar(0, 0, 128);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	this->_draw_colour = cv::Scalar(255, 255, 255);
}