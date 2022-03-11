#pragma once
#include "CGameObject.h"
#include "CBase4618.h"
#include "CShip.h"
#include "CMissile.h"
#include "CAsteroid.h"

/** CAsteroidGame.h
*
* @brief Inherits from CBase4618 to override update() and draw() methods for implementation in a game of asteroids
*
* @author Kurt Querengesser
* @version 1.0 -- 20 Feb 2022
**/
class CAsteroidGame : public CBase4618 {
private:
	CShip _cship; ///< Ship class that the player controls in game
	std::vector<CAsteroid> _asteroid_list; ///< vector containing all asteroids
	std::vector<CMissile> _missile_list; ///< vector containing all missiles
	cv::Point2f directionVec; ///< unit vector representing the direction the CShip is travelling in
	std::string gameOverText; ///< text to write to the screen upon game over condition
	int score; ///< player's score

	/** @brief fire the missile on the ship
	* @return void
	**/
	void fire();

	/** @brief freezes the game and shows game over text
	* @param text: text to display upon gameover
	* @return void
	**/
	void gameOver(std::string text);

	/** @brief helper function for checking collision and removing objects if their life drops below 1
	* @return void
	**/
	void collision();

	/** @brief helper function for controlling all ship, asteroid and missile movement
	* @return void
	**/
	void movement();

	/** @brief helper function for spawning new asteroids
	* @param spawnlimit: the amount of asteroids to spawn
	* @param spawnsize: max size the asteroids can be
	* @param location: a cv::Point for where to place the asteroid, leave blank for random position
	* @return void
	**/
	void newAsteroid(int spawnlimit = 25, int spawnsize = 25, cv::Point location = cv::Point(-1, -1));

	/** @brief helper function for breaking an asteroid into smaller bits
	* @param astro: pass in a CAsteroid so it knows the location, size, etc.
	* @return void
	**/
	void splitAsteroid(CAsteroid astro);

	/** @brief setup the base conditions for the game
	* @return void
	**/
	void init_game();

	/** @brief overrides CBase4618 update method
	* @param: no parameters
	* @return void
	**/
	void update() override;

	/** @brief overrides CBase4618 draw method
	* @param: no parameters
	* @return void
	**/
	void draw() override;
public:
	/** @brief CSketch constructor initializes canvas size and serial port
	* @param size: a cv size object to specify how big to make the canvas
	* @param comport: a number specifying which comport to open
	* @return void
	**/
	CAsteroidGame(cv::Size size);

	/** @brief default deconstructor
	**/
	~CAsteroidGame();
};


