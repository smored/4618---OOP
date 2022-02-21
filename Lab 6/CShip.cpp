#include "stdafx.h"
#include "CShip.h"

CShip::CShip() {
	this->set_lives(10);
	this->_position = cv::Point2f(0, 0);
	this->_radius = 25;
}

CShip::~CShip() {

}