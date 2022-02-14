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
protected:
	CControl control; ///< control object for handling all communications with uC
	cv::Mat _canvas;  ///< Mat object for drawing on and updating to screen
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
};