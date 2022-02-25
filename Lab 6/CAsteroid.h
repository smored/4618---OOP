#pragma once
#include "CGameObject.h"
#include "CBase4618.h"
#include "CShip.h"
#include "CMissile.h"

const float MAXVELOCITY = 250;

/** CAsteroid.h
*
* @brief Inherits from CGameobject for making asteroid objects
*
* @author Kurt Querengesser
* @version 1.0 -- 21 Feb 2022
**/
class CAsteroid : public CGameObject {
private:
	bool random_spawn; ///< should this object spawn in a random location or should it spawn from its previous location
public:
	/** @brief paramaterized constructor
	* @param location: where to spawn this asteroid from, set to (-1,-1) for random location
	* @param canvas_size: size of canvas so asteroids can randomly spawn on the edges of the screen
	* @param sizeLimit: the maximum size that an asteroid can be created, leave blank for default size of 15
	**/
	CAsteroid(cv::Point location, cv::Size canvas_size, int sizeLimit = -1);

	/** @brief default deconstructor
	**/
	~CAsteroid();

	/** @brief move() override from CGameobject class to handle going off screen and loop around
	* @param deltaT: pass in the time between the last frame and now
	* @return void
	**/
	void move(double deltaT);

	/** @brief method to set the asteroid velocities to a random number based on MAXVELOCITY
	* @return void
	**/
	void set_random();
};