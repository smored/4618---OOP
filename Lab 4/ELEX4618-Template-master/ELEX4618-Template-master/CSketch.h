#pragma once

#include "CBase4618.h"

class CSketch : public CBase4618 {
private:
	/* @brief inherits CBase4618's update method to update internal variables of CSketch
	* @param: no parameters
	* @return void
	*/
	void update();

	/* @brief inherits CBase4618's draw method to calculate and display images on the screen
	* @param: no parameters
	* @return void
	*/
	void draw();
public:
	/* @brief CSketch constructor initializes canvas size and serial port
	* @param size: a cv size object to specify how big to make the canvas
	* @param comport: a number specifying which comport to open
	* @return void
	*/
	CSketch(cv::Size size, int comport);


};

