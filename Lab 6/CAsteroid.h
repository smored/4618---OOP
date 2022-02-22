#pragma once
#include "CGameObject.h"
#include "CBase4618.h"
#include "CShip.h"
#include "CMissile.h"

/** CAsteroid.h
*
* @brief Inherits from CGameobject for making asteroid objects
*
* @author Kurt Querengesser
* @version 1.0 -- 21 Feb 2022
**/
class CAsteroid : public CGameObject {
public:
	CAsteroid();
	~CAsteroid();
	void set_random(cv::Size canvasSize);
};