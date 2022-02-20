#include "stdafx.h"
#include "Paddle.h"

#define PADDLESPEED 18

Paddle::Paddle() {
	this->type = AI;
	this->paddleSize = cv::Rect(50, 50, 50, 50);
}

Paddle::Paddle(bool type, cv::Rect paddleSize) {
	this->type = type;
	this->paddleSize = paddleSize;
}

Paddle::~Paddle() {

}

void Paddle::setSize(cv::Point canvasSize) {
	this->canvasSize = canvasSize;
	if (this->type == AI) {
		this->paddleSize.x = canvasSize.x - paddleSize.width;
	}
	else if (this->type == PLAYER) {
		this->paddleSize.x = 0;
	}
}

//void Paddle::setSize(cv::Point canvasSize, cv::Point paddleSize) {
//	this->canvasSize = canvasSize;
//	this->paddleSize = paddleSize;
//}


void Paddle::updatePaddle(int velocity) {
	if (this->type == AI) {
		int paddleCenter = paddleSize.y + paddleSize.height / 2;
		//this->paddleSize.y = velocity; // Non-winnable game
		if (paddleCenter > velocity) {

			paddleSize.y -= PADDLESPEED;

		}
		else if (paddleCenter < velocity) {

			paddleSize.y += PADDLESPEED;

		}

	}
	else if (this->type == PLAYER) {
		if (!(paddleSize.y + velocity + paddleSize.height >= canvasSize.y)) {
			paddleSize.y += velocity;
		}
		else {
			paddleSize.y = canvasSize.y - velocity - paddleSize.height;
		}
		if (!(paddleSize.y + velocity <= 0)) {
			paddleSize.y += velocity;
		}
		else {
			paddleSize.y = 0;
		}
	}
}

void Paddle::resetPaddle() {
	paddleSize.y = canvasSize.y / 2;
}

cv::Rect Paddle::getRect() {
	return this->paddleSize;
}