#include "stdafx.h"
#include "Pong.h"
#include "Ball.h"
#include "Paddle.h"

#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32

Pong::Pong(cv::Size size, int comport) {
	AIpaddle = Paddle(AI, cv::Rect(100, 100, PADDLEX, PADDLEY));
	Playerpaddle = Paddle(PLAYER, cv::Rect(0, 0, PADDLEX, PADDLEY));
	score = { 0,0 };
	gameOverText = "";
	control.init_com();
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	cv::imshow("Pong", _canvas);
	ball.setSize(_canvas.size());
	ball.resetBall();
	AIpaddle.setSize(_canvas.size());
	AIpaddle.resetPaddle();
	Playerpaddle.setSize(_canvas.size());
	Playerpaddle.resetPaddle();
	resetGame();
}

Pong::~Pong() {

}

void Pong::update() {
	if (control.get_button(33, 0)) gameOver();

	// Player Paddle controlled by joystick
	Playerpaddle.updatePaddle((control.get_analog(Y_JOYSTICK)*-100 + 50));
	cv::Rect playerRect = Playerpaddle.getRect();

	// AI chases ball y position
	AIpaddle.updatePaddle(ball.getPos().y);
	cv::Rect aiRect = AIpaddle.getRect();

	// Update ball position
	static std::vector<int> prevScore = score;
	score = ball.updateBall(playerRect, aiRect);
	if (prevScore != score) {
		ball.resetBall();
		if (score.at(0) >= 5 || score.at(1) >= 5) {
			std::cout << "Game Over\nPress S1 to continue\n";
			gameOverText = "Game Over!";
			while (!(control.get_button(33, 0)));
			gameOverText = "";
			gameOver();
		}
		prevScore = score;
	}
}

void Pong::draw() {
	_canvas = cv::Mat::zeros(cv::Size(_canvas.size()), CV_8UC3); // Refresh screen
	if (score.size() > 0) { // if score has been initialized...
		cv::putText(_canvas, std::to_string(score.at(0)), cv::Point(_canvas.size().width / 3, 60), 1, 5, WHITE); // Player Score
		cv::putText(_canvas, std::to_string(score.at(1)), cv::Point(_canvas.size().width * (2.0f / 3.0f), 60), 1, 5, WHITE); // AI Score
		cv::putText(_canvas, "FPS: " + std::to_string(getfps()), cv::Point(0, 10), 1, 1, WHITE); // Put FPS on screen
		cv::putText(_canvas, gameOverText, cv::Point(0, 250), 1, 10, RED); // Put FPS on screen
	}
	cv::line(_canvas, cv::Point(_canvas.size().width / 2, 0), cv::Point(_canvas.size().width / 2, _canvas.size().height), WHITE/5); // Draw centre line
	cv::rectangle(_canvas, Playerpaddle.getRect(), WHITE); // Draw player paddle
	cv::rectangle(_canvas, AIpaddle.getRect(), WHITE); // Draw AI paddle
	cv::circle(_canvas, ball.getPos(), BALLRADIUS, WHITE, 1, cv::LINE_AA); // Draw ball
	cv::imshow("Pong", _canvas);
}

void Pong::resetGame() {
	ball.resetBall();
	ball.resetScore();
	Playerpaddle.resetPaddle();
	AIpaddle.resetPaddle();
}

void Pong::gameOver() {
	score.at(0) = 0; score.at(1) = 0;
	resetGame();
}

//void Pong::start() {
//	using namespace std;
//	_thread_exit = false;
//	thread t1(&Pong::update_thread, this);
//	thread t2(&Pong::draw_thread, this);
//	/*t1.detach();
//	t2.detach();*/
//
//	while (cv::waitKey(1) != 'q');
//
//	_thread_exit = true;
//	t1.join();
//	t2.join();
//}
//
//void Pong::update_thread() {
//	while (!_thread_exit) {
//		update();
//	}
//}
//
//void Pong::draw_thread() {
//	while (!_thread_exit) {
//		draw();
//	}
//}