#pragma once

class Ball
{
private:
	cv::Point position = cv::Point(0, 0);
	cv::Point velocity = cv::Point(5, 5);
	cv::Point acceleration = cv::Point(0,0);
	cv::Point canvasSize = cv::Point(0, 0);
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

