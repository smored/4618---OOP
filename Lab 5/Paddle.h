#pragma once

enum {PLAYER, AI};

/** Paddle.h
 *
 * @brief paddle object which is defined by an opencv Rect that has a position and size. can be made to move based on velocity/position
 *
 *
 * @author Kurt Querengesser
 *
 * @version 1.0 -- 17 Feb 2022
 */
class Paddle
{
private:
	cv::Point canvasSize = cv::Point(0, 0); ///< size of the canvas using x y coordinates
	cv::Rect paddleSize; ///< size of the paddle using cv::Rect points
	bool type = AI; ///< bool that defines whether this is a player or computer controlled paddle
public:
	/* @brief parameterized constructor for creating the paddle
	* @param type: type of paddle this is (player or ai)
	* @param paddleSize: opencv Rect for size and posistion of rectangle
	*/
	Paddle(bool type, cv::Rect paddleSize);

	/* @brief default deconstructor
	*/
	~Paddle();

	/* @brief deprecated method, do not use
	*/
	void setSize(cv::Point canvasSize, cv::Rect paddleSize);

	/* @brief method for setting the size of the canvas. paddle must know this for collision
	* @param canvasSize: x y size of the canvas
	* @return void
	*/
	void setSize(cv::Point canvasSize);

	/* @brief method which must be called every tick in order to update the position of the paddle
	* @param velocity: velocity/position inputted for position calcs
	* @return void
	*/
	void updatePaddle(int velocity);

	/* @brief method to reset the position of the paddle
	* @return void
	*/
	void resetPaddle();

	/* @brief getter for rectangle position of centre of ball)
	* @return returns a cv::Rect which contains the size and position of the rectangle
	*/
	cv::Rect Paddle::getRect();
};
