#pragma once

#include "CBase4618.h"

/** CSketch.h
 *
 * @brief Inherits & overrides methods from CBase4618.h for drawing shapes to the screen using openCV
 *
 *
 * @author Kurt Querengesser
 *
 * @version 1.0 -- 12 Feb 2022
 */
class CSketch : public CBase4618 {
private:
	cv::Point stickval; ///< variable used for storing the position of the joystick
	cv::Scalar colour = cv::Scalar(255, 255, 255); ///< variable used for storing current colour of cursor

	const cv::Scalar colourArr[3] = {cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255)}; ///< constant array stores all colour values to cycle through
	cv::Mat _canvas;  ///< Mat object for drawing on and updating to screen
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
	CSketch(cv::Size size, int comport);
	/* @brief default deconstructor
	*/
	~CSketch();
};

