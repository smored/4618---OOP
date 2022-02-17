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
	bool _thread_exit = false;
	void update_thread();
	void draw_thread();
protected:
	CControl control; ///< control object for handling all communications with uC
	cv::Mat _canvas;  ///< Mat object for drawing on and updating to screen
	const cv::Scalar WHITE = cv::Scalar(255, 255, 255); ///< Default white colour scalar
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

	/* @brief method called in run loop to get current fps and set target fps
	* @return void
	*/
	void fps();
};