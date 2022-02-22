#pragma once


/* @brief Base object for all game pieces to inherit from
* Handles all movement, collision and rendering
* 
* @author Kurt Querengesser
* @version 1.0 -- 20 Feb 2022
*/
class CGameObject {
protected:
	cv::Scalar _draw_colour;
	cv::Point2f _position; ///< Object's current position
	cv::Point2f _velocity; ///< Object's current velocity
	cv::Point2f _acceleration; ///< Object's current acceleration
	int _radius; ///< Size to make object's hitbox/rendering size
	int _lives; ///< How many lives this object has
public:
	/** @brief method for handling movement of object
	* @return void
	**/
	void move(double deltaT);

	/** @brief method for returning if object has collided
	* @param obj: pass in a referece to the object that you are interested in colliding with
	* @return returns a boolean if there was a collision
	**/
	bool collide(CGameObject& obj);

	/** @brief method for returning if object collided with walls 
	* @param board: a size parameter that contains two points in space for size of gameboard
	* @return returns a boolean if there was a collision
	**/
	bool collide_wall(cv::Size board);

	/** @brief method for removing a life from this object
	* @return void
	**/
	void hit(); 

	/** @brief getter for lives 
	* @return returns an int for lives
	**/
	int get_lives() { return _lives; } 

	/** @brief setter for lives 
	* @param lives: how many lives to give this object
	* @return void
	**/
	void set_lives(int lives) { _lives = lives; }

	/** @brief setter for position of this object
	* @param pos: a Point2f representing the x,y position of this object
	* @ return void
	**/
	void set_pos(cv::Point2f pos) { _position = pos; }

	/** @brief getter for position of this object
	* @return returns a Point2f representing the x,y position of this object
	**/
	cv::Point2f get_pos() { return _position; }

	/** @brief the rendering component of this object 
	* @param im: pass in the Mat object to draw on
	**/
	void draw(cv::Mat& im);

	/** @brief setter for velocity of this object
	* @param vel: a Point2f representing the x,y velocity of this object
	* @ return void
	**/
	void set_vel(cv::Point2f vel) { _velocity += vel; }
	void set_acc(cv::Point2f acc) { _acceleration += acc; }
	cv::Point2f get_acc() { return _acceleration; }
	cv::Point2f get_vel() { return _velocity; }
};