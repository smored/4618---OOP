#pragma once
#include "CGameObject.h"

/** CMissile.h
*
* @brief Inherits from CGameobject for making missile objects
*
* @author Kurt Querengesser
* @version 1.0 -- 21 Feb 2022
**/
class CMissile : public CGameObject {
public:
	CMissile(cv::Point2f velocity, cv::Point2f position);
	~CMissile();
	//bool collide(CGameObject& obj);
};

