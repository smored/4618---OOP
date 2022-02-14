#include "stdafx.h"
#include "Paddle.h"

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
		//this->paddleSize.y = velocity; // Non-winnable game
		if (paddleSize.y > velocity) {

				paddleSize.y -= 4;
	
		}
		else if (paddleSize.y < velocity) {

				paddleSize.y += 4;

		}
	}
	else if (this->type == PLAYER) {
		if (paddleSize.y + velocity + paddleSize.height >= canvasSize.y || paddleSize.y + velocity <= 0) {

		}
		else {
			paddleSize.y += velocity;
		}
	}
}

void Paddle::resetPaddle() {
	paddleSize.y = canvasSize.y / 2 + paddleSize.y / 2;
}

cv::Rect Paddle::getRect() {
	return this->paddleSize;
}