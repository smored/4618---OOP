#include "stdafx.h"
#include "CBase4618.h"

#define FPS 30

CBase4618::CBase4618() {

}

CBase4618::~CBase4618() {

}

//Single-threaded implementation
void CBase4618::run() {
	do {
		fps();
		update();
		draw();
	} while (cv::waitKey(1) != 'q');
	return;
}

void CBase4618::update() {

}

void CBase4618::draw() {

}


// Multi-thread implementation
//void CBase4618::run() {
//	using namespace std;
//	_thread_exit = false;
//	thread t1(&CBase4618::update_thread, this);
//	thread t2(&CBase4618::draw_thread, this);
//
//	while (cv::waitKey(1) != 'q');
//
//	_thread_exit = true;
//	t1.join();
//	t2.join();
//}

void CBase4618::update_thread() {
	while (!_thread_exit) {
		update();
	}
}

void CBase4618::draw_thread() {
	while (!_thread_exit) {
		draw();
		//fps();
	}
}

void CBase4618::fps() {
	const int iterations = 30;
	static double avgFPS = 0;
	static int i = 0;
	static double time1 = 1, time2 = 1;

	// Get FPS
	time2 = cv::getTickCount();
	double fps = 1.0f / ((time2 - time1) / cv::getTickFrequency());
	time1 = cv::getTickCount();

	// Get Average
	avgFPS += fps;
	i++;
	if (i >= iterations) {
		i = 0;
		avgFPS /= iterations;
		std::cout << "AVG FPS: " << avgFPS << std::endl;
	}

	// Set Target FPS
	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(1000 / FPS);
	std::this_thread::sleep_until(end_time);
}