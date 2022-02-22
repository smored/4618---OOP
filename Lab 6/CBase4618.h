#pragma once

#include "CControl.h"

/** CBase4618.h
 *
 * @brief Implements a run method for updating superclasses implementing update() & draw()
 *
 *
 * @author Kurt Querengesser
 *
 * @version 1.0 -- 12 Feb 2022
 */
class CBase4618 {
private:
	bool _thread_exit = false; ///< condition for multiple threads to be able to exit at the same time 
	void update_thread(); ///< method for multi-threading update() by looping a single thread
	void draw_thread(); ///< method for multi-threading draw() by looping a single thread
	double framerate; ///< framerate of the draw method 
	cv::Scalar RGB = cv::Scalar(0, 0, 0);
protected:
	CControl control; ///< control object for handling all communications with uC
	cv::Mat _canvas;  ///< Mat object for drawing on and updating to screen
	const cv::Scalar WHITE = cv::Scalar(255, 255, 255); ///< Default white colour scalar
	const cv::Scalar RED = cv::Scalar(255, 0, 0); ///< Red colour scalar
	const cv::Scalar GREEN = cv::Scalar(0, 255, 0); ///< Green colour scalar
	const cv::Scalar BLUE = cv::Scalar(0, 0, 255); ///< Blue colour scalar
public:
	
	/** @brief Class Constructor
	* @param no parameters
	* @return no returns
	**/
	CBase4618();

	/** @brief Class Deconstructor
	* @param no parameters
	* @return no returns
	**/
	~CBase4618();

	/** @brief virtual update method template
	* @param no parameters
	* @return void 
	**/
	virtual void update();

	/** @brief virtual draw method template
	* @param no parameters
	* @return void
	**/
	virtual void draw();

	/** @brief run method that calls update() and draw() until user exits
	* @param no parameters
	* @return void
	**/
	void run();

	/** @brief method called in run loop to get current fps and set target fps
	* @return void
	**/
	void fps();

	/** @brief method called in run loop to get current fps and set target fps
	* @return void
	**/
	void ups();

	/** @brief getter for framerate member
	* 
	**/
	double getfps();

	static void clamp(int& val, int upper, int lower);
	static void clamp(cv::Point2f& val, int upper, int lower);
	static cv::Point2f CBase4618::normalizeVec(cv::Point2f vector);
	static double CBase4618::magnitudeVec(cv::Point2f vector);
};