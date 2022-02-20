#include "stdafx.h"
#include "Ball.h"

enum {X_AXIS, Y_AXIS};

Ball::Ball(int size) {
	this->size = size;
}

Ball::~Ball() {

}

void Ball::setSize(cv::Point canvasSize) {
	this->canvasSize = canvasSize;
}

std::vector<int> Ball::updateBall(cv::Rect playerRect, cv::Rect aiRect) {
	// Check if going to collide with paddle
	// Left side
	cv::Point nextPos = position;
	if (nextPos.x - size <= playerRect.x + playerRect.width) {
		if (nextPos.y + size >= playerRect.y && nextPos.y - size <= playerRect.y + playerRect.height) {
			reflect(X_AXIS);
		}
	}
	// Right side
	if (nextPos.x + size >= aiRect.x) {
		if (nextPos.y + size >= aiRect.y && nextPos.y - size <= aiRect.y + aiRect.height) {
			reflect(X_AXIS);
		}
	}


	// Check if going to collide with wall
	if (velocity.y + position.y - this->size <= 0 || velocity.y + position.y + this->size >= canvasSize.y) {
		this->reflect(Y_AXIS);
	}
	if (position.x - this->size <= 0) {
		// Left side, so increment AI score
		this->score.at(1)++;
		this->reflect(X_AXIS);
	}
	else if (position.x + this->size >= canvasSize.x) {
		// Right side, so increment player score
		this->score.at(0)++;
		this->reflect(X_AXIS);
	}

	velocity += acceleration;
	position += velocity;

	return score;
}

void Ball::resetBall() {
	position = canvasSize / 2;
	if (cv::getTickCount() % 2) velocity *= -1;
}

cv::Point Ball::getPos() {
	return position;
}

void Ball::reflect(bool axis) {
	if (axis == X_AXIS) {
		velocity.x *= -1;
	}
	else {
		velocity.y *= -1;
	}
}

void Ball::resetScore() {
	this->score = { 0,0 };
}