#pragma once

class Ball
{
private:
	cv::Point position = cv::Point(0, 0); ///< opencv point for position of ball
	cv::Point velocity = cv::Point(6*5, 6*5); ///< opencv point for velocity of ball
	cv::Point acceleration = cv::Point(0,0); ///< opencv point for acceleration of ball
	cv::Point canvasSize = cv::Point(0, 0); ///< opencv point for storing the size of the canvas
	int size = 0; 
	std::vector<int> score = {0,0};
public:

	Ball(int size);

	~Ball();

	void setSize(cv::Point canvasSize);

	std::vector<int> updateBall(cv::Rect playerRect, cv::Rect aiRec);

	void resetBall();

	cv::Point getPos();

	void reflect(bool axis);
};

