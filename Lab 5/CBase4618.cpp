#include "stdafx.h"
#include "CBase4618.h"

#define FPS 30
#define UPS 30

CBase4618::CBase4618() {

}

CBase4618::~CBase4618() {

}

//Single-threaded implementation
//void CBase4618::run() {
//	do {
//		fps();
//		update();
//		draw();
//	} while (cv::waitKey(1) != 'q');
//	return;
//}

void CBase4618::update() {

}

void CBase4618::draw() {

}


// Multi-thread implementation
void CBase4618::run() {
	using namespace std;
	_thread_exit = false;
	thread t1(&CBase4618::update_thread, this);
	thread t2(&CBase4618::draw_thread, this);
	//thread t3(&CBase4618::cycleRGB, this);

	while (cv::waitKey(10) != 'q');

	_thread_exit = true;
	t1.join();
	t2.join();
	//t3.join();
}

void CBase4618::update_thread() {
	while (!_thread_exit) {
		update();
		ups();
	}
}

void CBase4618::draw_thread() {
	while (!_thread_exit) {
		draw();
		fps();
	}
}

void CBase4618::fps() {
	const int iterations = FPS;
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
		this->framerate = avgFPS;
		std::cout << "AVG FPS: " << avgFPS << std::endl;
	}

	// Set Target FPS
	static auto end_time = std::chrono::system_clock::now();
	std::this_thread::sleep_until(end_time);
	end_time = std::chrono::system_clock::now() + std::chrono::milliseconds((1000 / FPS)); // Take time now, then loop back around to find total processing time
}


// TODO: Make this one method
void CBase4618::ups() {
	const int iterations = UPS;
	static double avgUPS = 0;
	static int i = 0;
	static double time1 = 1, time2 = 1;

	// Get UPS
	time2 = cv::getTickCount();
	double ups = 1.0f / ((time2 - time1) / cv::getTickFrequency());
	time1 = cv::getTickCount();

	// Get Average
	avgUPS += ups;
	i++;
	if (i >= iterations) {
		i = 0;
		avgUPS /= iterations;
		std::cout << "\tAVG UPS: " << avgUPS << std::endl;
	}

	// Set updates per second (UPS)
	static auto end_time = std::chrono::system_clock::now();
	std::this_thread::sleep_until(end_time);
	end_time = std::chrono::system_clock::now() + std::chrono::milliseconds((1000 / UPS)); // Take time now, then loop back around to find total processing time
}

double CBase4618::getfps() {
	if (framerate < 0) {
		return 0;
	}
	return framerate;
}



//void CBase4618::cycleRGB() {
//	while (!_thread_exit) {
//		static uint_fast8_t i = 0, j = 0, k = 255;
//		for (i = 0; i <= 255; i++) {
//			RGB = cv::Scalar(i, j, k);
//		}
//		for (k = 255; k >= 0; k--) {
//			RGB = cv::Scalar(i, j, k);
//		}
//		for (j = 0; j <= 255; j++) {
//			RGB = cv::Scalar(i, j, k);
//		}
//		for (i = 255; i >= 0; i--) {
//			RGB = cv::Scalar(i, j, k);
//		}
//		for (k = 0; k <= 255; k++) {
//			RGB = cv::Scalar(i, j, k);
//		}
//		for (j = 0; j <= 255; j++) {
//			RGB = cv::Scalar(i, j, k);
//		}
//	}
//}

cv::Scalar CBase4618::getRGB() {
	return RGB;
}