#pragma once

enum {PLAYER, AI};

class Paddle
{
private:
	//cv::Point position = cv::Point(0, 0);
	cv::Point canvasSize = cv::Point(0, 0);
	cv::Rect paddleSize;
	bool type = AI;
public:

	Paddle(bool type, cv::Rect paddleSize);

	~Paddle();

	void setSize(cv::Point canvasSize, cv::Rect paddleSize);
	void setSize(cv::Point canvasSize);

	void updatePaddle(int velocity);

	void resetPaddle();

	cv::Rect Paddle::getRect();
};
