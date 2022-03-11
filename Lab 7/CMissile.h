#pragma once
#include "CGameObject.h"
#include <opencv2/opencv.hpp>

/** CMissile.h
*
* @brief Inherits from CGameobject for making missile objects
*
* @author Kurt Querengesser
* @version 1.0 -- 21 Feb 2022
**/
class CMissile : public CGameObject {
public:
	/** @brief paramaterized constructor
	**/
	CMissile(cv::Point2f velocity, cv::Point2f position, int missile_size = 2);

	/** @brief default deconstructor
	**/
	~CMissile();

	/** @brief draw() method overload from CGameobject
	* @param im: reference to the canvas to draw on
	* @return void
	**/
	void draw(cv::Mat& im);
};

