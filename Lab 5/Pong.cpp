#include "stdafx.h"
#include "Pong.h"
#include "Ball.h"

const cv::Rect RECTANGLE = cv::Rect(0, 0, 100, 100);
#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32
#define FPS 30

Pong::Pong(cv::Size size, int comport) {
	control.init_com();
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	ball.setSize(_canvas.size());
	AIpaddle.setSize(_canvas.size());
	AIpaddle.resetPaddle();
	Playerpaddle.setSize(_canvas.size());
	Playerpaddle.resetPaddle();
	resetGame();
}

Pong::~Pong() {

}

void Pong::update() {
	/*canvaslock.lock();
	if (_canvas.empty()) {
		std::cout << "Error: canvas not defined!";
		return;
	}
	canvaslock.unlock();*/

	// Set Target FPS
	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(1000/FPS);

	// Get FPS
	static int time1, time2;
	float fps = 1.0f/((time2 - time1) / cv::getTickFrequency());
	time1 = cv::getTickCount();
	std::cout << "FPS: " << fps << std::endl;

	// Player Paddle controlled by joystick
	Playerpaddle.updatePaddle((control.get_analog(Y_JOYSTICK)*-100 + 50));
	cv::Rect playerRect = Playerpaddle.getRect();

	// AI chases ball y position
	AIpaddle.updatePaddle(ball.getPos().y);
	cv::Rect aiRect = AIpaddle.getRect();

	// Update ball position
	score = ball.updateBall(playerRect, aiRect);

	static std::vector<int> oogabooga = score;

	if (oogabooga[0] < score[0] || oogabooga[1] < score[1]) resetGame();
	oogabooga = score;

	// Rendering
	canvaslock.lock();
	_canvas = cv::Mat::zeros(cv::Size(_canvas.size()), CV_8UC3); // Refresh screen
	cv::putText(_canvas, std::to_string(score[0]), cv::Point(_canvas.size().width / 3, 60), 1, 5, WHITE); // Player Score
	cv::putText(_canvas, std::to_string(score[1]), cv::Point(_canvas.size().width * (2.0f / 3.0f), 60), 1, 5, WHITE); // AI Score
	cv::line(_canvas, cv::Point(_canvas.size().width/2, 0), cv::Point(_canvas.size().width / 2, _canvas.size().height), WHITE); // Draw centre line
	cv::rectangle(_canvas, Playerpaddle.getRect(), WHITE); // Draw player paddle
	cv::rectangle(_canvas, AIpaddle.getRect(), WHITE); // Draw AI paddle
	cv::circle(_canvas, ball.getPos(), BALLRADIUS, WHITE, 1, cv::LINE_AA); // Draw ball
	canvaslock.unlock();
	

	// Wait if too fast for FPS control
	std::this_thread::sleep_until(end_time);
	time2 = cv::getTickCount();
}

void Pong::draw() {
	canvaslock.lock();
	cv::imshow("Pong", _canvas);
	canvaslock.unlock();
}

void Pong::resetGame() {
	//if (score[0] >= 5 || score[1] >= 5) {
	//	score[0] = 0; score[1] = 0;
	//}
	ball.resetBall();
	Playerpaddle.resetPaddle();
	AIpaddle.resetPaddle();
	int then = cv::getTickCount();
	while (1) {
		if ((cv::getTickCount() - then)/cv::getTickFrequency() >= 1000) {
			break;
		}
	}
}

void Pong::start() {
	using namespace std;
	thread t1(&Pong::update_thread, this);
	thread t2(&Pong::draw_thread, this);
	t1.detach();
	t2.detach();
}

void Pong::update_thread(Pong* ptr) {
	while (!ptr->_thread_exit) {
		ptr->update();
	}
}

void Pong::draw_thread(Pong* ptr) {
	while (!ptr->_thread_exit) {
		ptr->draw();
	}
}