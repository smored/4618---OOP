#pragma once

#include "CBase4618.h"
#include "Ball.h"
#include "Paddle.h"

#define BALLRADIUS 25
#define PADDLEX 25
#define PADDLEY 100

/** Pong.h
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
	std::string gameOverText;
	Ball ball = Ball(BALLRADIUS); ///< Ball object instantiated with paramaterized size constructor
	Paddle AIpaddle; ///< instantiating AI paddle
	Paddle Playerpaddle; ///< instantiating player paddle
	std::vector<int> score; ///< score used for reset logic and drawing to screen
	std::mutex canvaslock;
	/** @brief inherits CBase4618's update method to update internal variables of CSketch
	* @param: no parameters
	* @return void
	**/
	void update() override;

	/** @brief inherits CBase4618's draw method to calculate and display images on the screen
	* @param: no parameters
	* @return void
	**/
	void draw() override;

	/** @brief resets the positions of all game objects to their default states but preserves the score. used for respawning the ball mainly
	* @return void
	**/
	void resetGame();

	/** @brief completely hard resets the game to its base state
	* @return void
	**/
	void gameOver();
public:
	/** @brief CSketch constructor initializes canvas size and serial port
	* @param size: a cv size object to specify how big to make the canvas
	* @param comport: a number specifying which comport to open
	* @return void
	**/
	Pong(cv::Size size, int comport);

	/** @brief default deconstructor
	**/
	~Pong();
};
