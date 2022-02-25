#include "stdafx.h"
#include "CMissile.h"

CMissile::CMissile(cv::Point2f velocity, cv::Point2f position, int missile_size) {
	this->set_lives(1);
	this->_position = position;
	this->_radius = missile_size;
	this->_draw_colour = cv::Scalar(0, 0, 255);
	this->_velocity = velocity;
}

CMissile::~CMissile() {

}

void CMissile::draw(cv::Mat& im) {
	cv::circle(im, _position, _radius, _draw_colour, cv::FILLED, cv::LINE_AA);
}