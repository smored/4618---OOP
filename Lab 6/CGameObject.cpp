#include "stdafx.h"
#include "CGameObject.h"


void CGameObject::move(double deltaT) {
	_position += _velocity * deltaT;
}

bool CGameObject::collide(CGameObject& obj) {
	cv::Point2f difference = this->_position - obj._position;
	float distance = sqrt((difference.x * difference.x) + (difference.y * difference.y));
	if (distance <= (this->_radius + obj._radius)) return true;
	return false;
	this->_velocity;
	obj._velocity;
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
	cv::circle(im, _position, _radius, _draw_colour, 1, cv::LINE_AA);
}