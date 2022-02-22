#include "stdafx.h"
#include "CAsteroidGame.h"

#define X_JOYSTICK 2
#define Y_JOYSTICK 26
#define S1 33
#define S2 32
#define DEADZONE 5

CAsteroidGame::CAsteroidGame(cv::Size size) {
	// Open Com port
	control.init_com();

	// Open canvas
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	cv::imshow("Asteroids", _canvas);

	// Initialize game
	_cship = CShip();
	init_game();
}

CAsteroidGame::~CAsteroidGame() {

}

void CAsteroidGame::init_game() {
	_cship.set_acc(cv::Point2f(0, 0));
	_cship.set_vel(cv::Point2f(0, 0));
	_cship.set_pos(cv::Point2f(_canvas.size().width / 2.0f, _canvas.size().height / 2.0f));
	_cship.set_lives(10);
	_asteroid_list.clear();
	_missile_list.clear();
}

void CAsteroidGame::update() {
	if (_isnan(_cship.get_pos().x)) {
		init_game();
	}

	double deltaT = 1.0f / getfps(); // not 100% sure on this one, might change later
	newAsteroid();

	for (int i = 0; i < _asteroid_list.size(); i++) {
		// missile collision logic
		for (int j = 0; j < _missile_list.size(); j++) {
			if (_missile_list.at(j).collide_wall(_canvas.size())) {
				_missile_list.erase(_missile_list.begin() + j); // theres probably a better way than vector::erase 
			}
			else if (_missile_list.at(j).collide(_asteroid_list.at(i))) {
				_missile_list.erase(_missile_list.begin() + j);
				_asteroid_list.erase(_asteroid_list.begin() + i);
			}
		}
	}

	// check if player collides with asteroid
	for (int i = 0; i < _asteroid_list.size(); i++) {
		if (_asteroid_list.at(i).collide(_cship)) {
			_asteroid_list.erase(_asteroid_list.begin() + i);
			_cship.hit();
			continue;
		}
		// check if asteroid hits wall
		if (_asteroid_list.at(i).collide_wall(_canvas.size())) {
			_asteroid_list.erase(_asteroid_list.begin() + i);
		}
	}

	// asteroid movement
	for (int i = 0; i < _asteroid_list.size(); i++) {
		_asteroid_list.at(i).move(deltaT);
	}
	// missile movement
	for (int i = 0; i < _missile_list.size(); i++) {
		_missile_list.at(i).move(deltaT);
	}

	// ship logic
	cv::Point2f joystickPos = cv::Point2f((float)(control.get_analog(X_JOYSTICK) * 100.0f) - 50.0f, ((float)control.get_analog(Y_JOYSTICK) * -100.0f) + 50.0f);
	if (joystickPos.x > -DEADZONE && joystickPos.x < DEADZONE) {
		joystickPos.x = 0;
	}
	if (joystickPos.y > -DEADZONE && joystickPos.y < DEADZONE) {
		joystickPos.y = 0;
	}
	//joystickPos = normalizeVec(joystickPos) * 100;
	_cship.set_vel(joystickPos);
	_cship.move(deltaT);
	if (magnitudeVec(_cship.get_vel()) > 0) {
		directionVec = normalizeVec(_cship.get_vel());
	}

	// button logic
	if (control.get_button(S1, 0)) {
		// Fire Missile
		fire();
	}
	else if (control.get_button(S2, 1)) {
		// Reset Button
		init_game();
	}
}

void CAsteroidGame::draw() {
	_canvas = cv::Mat::zeros(_canvas.size(), CV_8UC3);
	cv::circle(_canvas, _cship.get_pos() + 25 * directionVec, 5, WHITE);
	_cship.draw(_canvas);
	for (int i = 0; i < _asteroid_list.size(); i++) {
		_asteroid_list.at(i).draw(_canvas);
	}
	for (int i = 0; i < _missile_list.size(); i++) {
		_missile_list.at(i).draw(_canvas);
	}
	cv::putText(_canvas, "Lives: " + std::to_string(_cship.get_lives()), cv::Point(20, 20), 1, 1, WHITE);
	cv::putText(_canvas, "Missiles: " + std::to_string(_missile_list.size()), cv::Point(500, 20), 1, 1, WHITE);
	cv::putText(_canvas, "Asteroids: " + std::to_string(_asteroid_list.size()), cv::Point(700, 20), 1, 1, WHITE);
	cv::imshow("Asteroids", _canvas);
}

void CAsteroidGame::newAsteroid() {
	static auto time = std::chrono::system_clock::now();
	if (std::chrono::system_clock::now() - time >= std::chrono::milliseconds(250)) {
		CAsteroid astro;
		astro.set_random(_canvas.size());
		_asteroid_list.push_back(astro);
		time = std::chrono::system_clock::now();
	}
}

void CAsteroidGame::fire() {
	const float speed = 1000;
	CMissile missile = CMissile(directionVec * (speed + magnitudeVec(_cship.get_vel())), _cship.get_pos());
	_missile_list.push_back(missile);
}