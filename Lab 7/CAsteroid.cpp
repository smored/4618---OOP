#include "CAsteroid.h"

CAsteroid::CAsteroid(cv::Point location, cv::Size canvas_size, int sizeLimit) {
	if (sizeLimit == -1) {
		this->_radius = 15;
	}
	else {
		// minimum size of 10, maximum size of sizeLimit + 10
		this->_radius = sizeLimit * (float)rand() / (float)RAND_MAX + 10;
	}
	if (location == cv::Point(-1, -1)) {
		this->_position = cv::Point2f(0, 0);
		random_spawn = true;
	}
	else {
		this->_position = location;
		random_spawn = false;
	}
	this->_velocity = cv::Point2f(0, 0);
	this->set_lives(1);
	this->_draw_colour = cv::Scalar(128 * (float)rand() / (float)RAND_MAX + 127, 128 * (float)rand() / (float)RAND_MAX + 127, 128 * (float)rand() / (float)RAND_MAX + 127);
	this->_canvas_size = canvas_size;
}

CAsteroid::~CAsteroid() {

}

void CAsteroid::move(double deltaT) {
	_position += _velocity * deltaT;

	if (_position.x + _radius > _canvas_size.width) _position.x = _radius;
	if (_position.y + _radius > _canvas_size.height) _position.y = _radius;
	if (_position.x - _radius < 0) _position.x = _canvas_size.width - _radius;
	if (_position.y - _radius < 0) _position.y = _canvas_size.height - _radius;
}

void CAsteroid::set_random() {
	// choose which side of screen to spawn on
	cv::Point spawnPoint = cv::Point(0, 0);
	cv::Point2f velocity = cv::Point2f(0, 0);
	int side = 1 * (float)rand() / (float)RAND_MAX;
	int circleSize = this->_radius + 1;

	velocity.x = (MAXVELOCITY * (float)rand() / (float)RAND_MAX - (MAXVELOCITY / 2)) + 1;
	velocity.y = (MAXVELOCITY * (float)rand() / (float)RAND_MAX - (MAXVELOCITY / 2)) + 1;
	if (random_spawn) {
		if (side) {
			spawnPoint.x = circleSize;
			spawnPoint.y = _canvas_size.height * (float)rand() / (float)RAND_MAX;
		}
		else {
			spawnPoint.x = _canvas_size.width * (float)rand() / (float)RAND_MAX;
			spawnPoint.y = circleSize;
		}
		this->_position = spawnPoint;
	}
	this->_velocity = velocity;
}
