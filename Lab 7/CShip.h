#pragma once
#include "CGameObject.h"
#include "CMissile.h"

/** CShip.h
*
* @brief Inherits from CGameobject for making a ship object for the player to control
*
* @author Kurt Querengesser
* @version 1.0 -- 21 Feb 2022
**/
class CShip : public CGameObject{
private:

public:
	/** @brief default constructor
	**/
	CShip() { ; }

	/** @brief paramaterized constructor override
	* @param canvas_size: pass in canvas size so the ship object knows how to loop around when it goes off screen
	* @param ship_size: radius of the ship circle & hitbox, defaults to 25 if left blank
	**/
	CShip(cv::Size canvas_size, int ship_size = 25);

	/** @brief default deconstructor
	**/
	~CShip();

	/** @brief move() method override from CGameobject
	* @param deltaT: pass in delta time for movement calcs
	* @return void
	**/
	void move(double deltaT);

	/** @brief draw() method override from GCameobject
	* @param im: pass in canvas reference to draw on
	* @param draw_colour: what colour to draw ship in
	* @return void
	**/
	void draw(cv::Mat& im, cv::Scalar draw_colour);

	/** @brief hit() override from CGameobject. Freezes game to show when ship takes damage
	* @return void
	**/
	void hit();
};

