#include "stdafx.h"
#include "CGameObject.h"


void CGameObject::move() {
	_position += _velocity;
}

bool CGameObject::collide(CGameObject& obj) {
	cv::Point2f difference = this->_position - obj._position;
	float distance = sqrt((difference.x * difference.x) + (difference.y * difference.y));
	if (distance <= (this->_radius + obj._radius)) return true;
	return false;
}

bool CGameObject::collide_wall(cv::Size board) {
	if (this->_position.x + this->_radius >= board.width) return true;
	if (this->_position.x - this->_radius <= 0) return true;
	if (this->_position.y + this->_radius >= board.height) return true;
	if (this->_position.y - this->_radius <= 0) return true;
	return false;
}

void CGameObject::hit() {
	this->_lives -= 1;
}

void CGameObject::draw(cv::Mat& im) {
	cv::circle(im, _position, _radius, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);
	cv::imshow("Asteroids", im);
}