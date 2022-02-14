#include "stdafx.h"
#include "Pong.h"
#include "Ball.h"

const cv::Rect RECTANGLE = cv::Rect(0, 0, 100, 100);
#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32

Pong::Pong(cv::Size size, int comport) {
	control.init_com(comport);
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	ball.setSize(_canvas.size());
	ball.resetBall();
	AIpaddle.setSize(_canvas.size());
	AIpaddle.resetPaddle();
	Playerpaddle.setSize(_canvas.size());
	Playerpaddle.resetPaddle();
}

Pong::~Pong() {

}

void Pong::update() {
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}

	// Player Paddle controlled by joystick
	Playerpaddle.updatePaddle((control.get_analog(Y_JOYSTICK)*-100 + 50)/5);
	cv::Rect playerRect = Playerpaddle.getRect();

	// AI chases ball y position
	AIpaddle.updatePaddle(ball.getPos().y);
	cv::Rect aiRect = AIpaddle.getRect();

	// Update ball position
	std::vector<int> score;
	score = ball.updateBall(playerRect, aiRect);

	static std::vector<int> oogabooga = score;

	//if (oogabooga[0] < score[0] || oogabooga[1] < score[1]) resetGame();
	//oogabooga = score;


	// Rendering
	_canvas = cv::Mat::zeros(cv::Size(_canvas.size()), CV_8UC3); // Refresh screen
	cv::putText(_canvas, std::to_string(score[0]), cv::Point(_canvas.size().width / 3, 60), 1, 5, WHITE); // Player Score
	cv::putText(_canvas, std::to_string(score[1]), cv::Point(_canvas.size().width * (2.0f / 3.0f), 60), 1, 5, WHITE); // AI Score
	cv::line(_canvas, cv::Point(_canvas.size().width/2, 0), cv::Point(_canvas.size().width / 2, _canvas.size().height), WHITE); // Draw centre line
	cv::rectangle(_canvas, Playerpaddle.getRect(), WHITE); // Draw player paddle
	cv::rectangle(_canvas, AIpaddle.getRect(), WHITE); // Draw AI paddle
	cv::circle(_canvas, ball.getPos(), BALLRADIUS, WHITE, 1, cv::LINE_AA); // Draw ball
}

void Pong::draw() {
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}
	cv::imshow("Pong", _canvas);
}

void Pong::resetGame() {
	ball.resetBall();
	Playerpaddle.resetPaddle();
	AIpaddle.resetPaddle();
	int then = cv::getTickCount();
	Sleep(1000);
	while (1) {
		if (cv::getTickCount() - then >= 1000) {
			break;
		}
	}
}