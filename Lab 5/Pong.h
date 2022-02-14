#pragma once

#include "CBase4618.h"

/** CSketch.h
 *
 * @brief Inherits & overrides methods from CBase4618.h for implementation in a game of pong
 *
 *
 * @author Kurt Querengesser
 *
 * @version 1.0 -- 13 Feb 2022
 */
class Pong : public CBase4618 {
private:
	cv::Point stickval; ///< variable used for storing the position of the joystick

	/* @brief inherits CBase4618's update method to update internal variables of CSketch
	* @param: no parameters
	* @return void
	*/
	void update() override;

	/* @brief inherits CBase4618's draw method to calculate and display images on the screen
	* @param: no parameters
	* @return void
	*/
	void draw() override;

public:
	/* @brief CSketch constructor initializes canvas size and serial port
	* @param size: a cv size object to specify how big to make the canvas
	* @param comport: a number specifying which comport to open
	* @return void
	*/
	Pong(cv::Size size, int comport);
	/* @brief default deconstructor
	*/
	~Pong();
};
