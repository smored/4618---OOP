#pragma once

#include "CControl.h"

class CBase4618 {
protected:
	CControl control; ///< control object for handling all communications with uC
	cv::Mat _canvas;  ///<
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