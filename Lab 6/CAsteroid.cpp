#include "stdafx.h"
#include "CAsteroid.h"

CAsteroid::CAsteroid() {
	this->_velocity = cv::Point2f(0, 0);
	this->set_lives(1);
	this->_position = cv::Point2f(0, 0);
	this->_radius = 15;
	this->_draw_colour = cv::Scalar(128 * (float)rand() / (float)RAND_MAX + 127, 128 * (float)rand() / (float)RAND_MAX + 127, 128 * (float)rand() / (float)RAND_MAX + 127);
}

CAsteroid::~CAsteroid() {

}

void CAsteroid::set_random(cv::Size canvasSize) {
	const float MAXVELOCITY = 250;
	// choose which side of screen to spawn on
	cv::Point spawnPoint = cv::Point(0, 0);
	cv::Point2f velocity = cv::Point2f(0, 0);
	int side = 4 * (float)rand() / (float)RAND_MAX;
	int circleSize = this->_radius + 1;

	if (side == 0) { // left
		spawnPoint.x = circleSize;
		spawnPoint.y = canvasSize.height * (float)rand() / (float)RAND_MAX;
		velocity.x = MAXVELOCITY * (float)rand() / (float)RAND_MAX + 1;
		velocity.y = MAXVELOCITY * (float)rand() / (float)RAND_MAX + 1;
	}
	else if (side == 1) { // top
		spawnPoint.x = canvasSize.width * (float)rand() / (float)RAND_MAX;
		spawnPoint.y = circleSize;
		velocity.x = MAXVELOCITY * (float)rand() / (float)RAND_MAX + 1;
		velocity.y = MAXVELOCITY * (float)rand() / (float)RAND_MAX + 1;
	}
	else if (side == 2) { // right
		spawnPoint.x = canvasSize.width - circleSize;
		spawnPoint.y = canvasSize.height * (float)rand() / (float)RAND_MAX;
		velocity.x = -MAXVELOCITY * (float)rand() / (float)RAND_MAX - 1;
		velocity.y = MAXVELOCITY * (float)rand() / (float)RAND_MAX + 1;
	}
	else if (side == 3) { // bottom
		spawnPoint.x = canvasSize.width * (float)rand() / (float)RAND_MAX;
		spawnPoint.y = canvasSize.height - circleSize;
		velocity.x = MAXVELOCITY * (float)rand() / (float)RAND_MAX + 1;
		velocity.y = -MAXVELOCITY * (float)rand() / (float)RAND_MAX - 1;
	}
	this->_position = spawnPoint;
	this->_velocity = velocity;
}