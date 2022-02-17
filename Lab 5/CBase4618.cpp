#include "stdafx.h"
#include "CBase4618.h"

CBase4618::CBase4618() {

}

CBase4618::~CBase4618() {

}

 //Single-threaded implementation
//void CBase4618::run() {
//	do {
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

	while (cv::waitKey(1) != 'q');

	_thread_exit = true;
	t1.join();
	t2.join();
}

void CBase4618::update_thread() {
	while (!_thread_exit) {
		update();
	}
}

void CBase4618::draw_thread() {
	while (!_thread_exit) {
		draw();
	}
}