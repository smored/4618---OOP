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
	if (velocity.x + position.x <= playerRect.x + playerRect.width + size) {
		if (velocity.y + position.y >= playerRect.y && velocity.y + position.y <= playerRect.y + playerRect.height) {
			reflect(X_AXIS);
		}
	}

	if (velocity.x + position.x >= aiRect.x - size) {
		if (velocity.y + position.y >= aiRect.y && velocity.y + position.y <= aiRect.y + aiRect.height) {
			reflect(X_AXIS);
		}
	}

	// Check if going to collide with wall
	if (velocity.y + position.y - this->size <= 0 || velocity.y + position.y + this->size >= canvasSize.y) {
		this->reflect(Y_AXIS);
	}
	if (velocity.x + position.x - this->size <= 0) {
		// Left side, so increment AI score
		this->score[1]++;
		this->reflect(X_AXIS);
	}
	else if (velocity.x + position.x + this->size >= canvasSize.x) {
		// Right side, so increment player score
		this->score[0]++;
		this->reflect(X_AXIS);
	}

	velocity += acceleration;
	position += velocity;

	return score;
}

void Ball::resetBall() {
	position = canvasSize / 2;
}

cv::Point Ball::getPos() {
	return position;
}

void Ball::reflect(bool axis) {
	if (axis == X_AXIS) {
		velocity.x = -velocity.x;
	}
	else {
		velocity.y = -velocity.y;
	}
}