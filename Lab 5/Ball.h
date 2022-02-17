#pragma once

/** Ball.h
 *
 * @brief ball object which has position and velocity. bounces around during a game of pong
 *
 *
 * @author Kurt Querengesser
 *
 * @version 1.0 -- 17 Feb 2022
 */
class Ball
{
private:
	cv::Point position = cv::Point(0, 0); ///< opencv point for position of ball
	cv::Point velocity = cv::Point(6*5, 6*5); ///< opencv point for velocity of ball
	cv::Point acceleration = cv::Point(0,0); ///< opencv point for acceleration of ball
	cv::Point canvasSize = cv::Point(0, 0); ///< opencv point for storing the size of the canvas
	int size = 0; ///< size (radius) of ball used for calculations and drawing
	std::vector<int> score = {0,0};
public:
	/* @brief paramaterized constructor for initializing the size of the ball
	*/
	Ball(int size);

	/* @brief default deconstructor
	*/
	~Ball();

	/* @brief method for setting the size of the canvas. ball must know this for collision
	* @param canvasSize: x y size of the canvas
	* @return void
	*/
	void setSize(cv::Point canvasSize);

	/* @brief method which must be called every tick in order to update the position and velocity of the ball
	* @param playerRect: an opencv Rect that refers to the Player paddle
	* @param aiRect: an opencv Rect that refers to the AI paddle
	* @return returns the score vector of type int, holds both sides scores
	*/
	std::vector<int> updateBall(cv::Rect playerRect, cv::Rect aiRect);

	/* @brief method to reset the position of the ball and randomize the direction
	* @return void
	*/
	void resetBall();

	/* @brief getter for ball position. needed for drawing ball
	* @return returns a cv::Point (x y position of centre of ball)
	*/
	cv::Point getPos();

	/* @brief method to flip the velocity of the ball
	* @param axis: which axis to flip about, x or y
	* @return void
	*/
	void reflect(bool axis);

	/* @brief set scores back to zero
	*/
	void resetScore();
};

