#include "stdafx.h"
#include "CMissile.h"

CMissile::CMissile(cv::Point2f velocity, cv::Point2f position) {
	this->set_lives(1);
	this->_position = position;
	this->_radius = 2;
	this->_draw_colour = cv::Scalar(0, 0, 255);
	this->_velocity = velocity;
}

CMissile::~CMissile() {

}

//bool CMissile::collide(CGameObject& obj) {
//	cv::Rect projectileVector = cv::Rect(this->_position.x, this->_position.y, 100, 100);
//	if (obj.get_pos().inside(projectileVector)) return true;
//	return false;
//}