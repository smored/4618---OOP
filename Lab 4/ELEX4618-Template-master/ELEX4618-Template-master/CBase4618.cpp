#include "stdafx.h"
#include "CBase4618.h"

CBase4618::CBase4618() {

}

CBase4618::~CBase4618() {

}

void CBase4618::run() {
	do {
		update();
		draw();
	} while (cv::waitKey(1) != 'q');
	//control.~CControl();
	return;
}

void CBase4618::update() {

}

void CBase4618::draw() {

}