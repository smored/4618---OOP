#include "stdafx.h"
#include "CBase4618.h"

void CBase4618::run() {
	do {
		draw();
		update();
	} while (!cv::waitKey('q'));
	return;
}