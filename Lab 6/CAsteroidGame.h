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
	std::vector<CAsteroid> _asteroid_list;
	std::vector<CMissile> _missile_list;
	std::mutex gameLock;
	cv::Point2f directionVec;
	void fire();
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
	void newAsteroid();
};


