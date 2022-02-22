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
	CShip();
	~CShip();
	void move(double deltaT);
};

