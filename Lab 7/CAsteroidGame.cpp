#include "CAsteroidGame.h"

#define X_JOYSTICK 1
#define Y_JOYSTICK 0
#define S1 27
#define S2 22
#define DEADZONE 5

#define ASTEROID_NUMBER 1
#define ASTEROID_SIZE 25
#define SHIP_SIZE 25
#define MISSILE_SIZE 5

CAsteroidGame::CAsteroidGame(cv::Size size) {
	// Open canvas
	_canvas = cv::Mat::zeros(size, CV_8UC3);
	cv::imshow("Asteroids", _canvas);

	// Initialize game
	_cship = CShip(_canvas.size(), SHIP_SIZE);
	directionVec = cv::Point2f(0,1);
	init_game();
}

CAsteroidGame::~CAsteroidGame() {

}

void CAsteroidGame::init_game() {
	score = 0;
	gameOverText = "";
	_cship.set_vel(cv::Point2f(0, 0));
	_cship.set_pos(cv::Point2f(_canvas.size().width / 2.0f, _canvas.size().height / 2.0f));
	_cship.set_lives(10);
	_asteroid_list.clear();
	_missile_list.clear();
	newAsteroid(ASTEROID_NUMBER, ASTEROID_SIZE);
}
void CAsteroidGame::update() {
	if (__isnan(_cship.get_pos().x)) {
		init_game();
	}

	movement();
	collision();

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
	_canvas = cv::Mat::zeros(_canvas.size(), CV_8UC3); // Clear frame

	cv::circle(_canvas, _cship.get_pos() + SHIP_SIZE * directionVec, 5, WHITE, cv::FILLED); // draw direction vector
	_cship.draw(_canvas, WHITE);

	// draw all asteroids
	for (int i = 0; i < _asteroid_list.size(); i++) {
		if (_asteroid_list.size()-1 < i) continue;
		_asteroid_list.at(i).draw(_canvas);
	}
	// draw all missiles
	for (int i = 0; i < _missile_list.size(); i++) {
		if (_missile_list.size()-1 < i) continue;
		_missile_list.at(i).draw(_canvas);
	}

	// show info to player on screen
	std::string printout = "Missiles: " + std::to_string(_missile_list.size()) +
		"  Asteroids: " + std::to_string(_asteroid_list.size()) +
		"  Lives: " + std::to_string(_cship.get_lives()) +
		"  Score: " + std::to_string(score);

	cv::putText(_canvas, printout, cv::Point(20, 20), 1, 2, WHITE); // Print out text for player
	if (!gameOverText.empty()) {
		cv::putText(_canvas, gameOverText, cv::Point(0, 250), 1, 10, RED); // Show game over text
	}
	cv::imshow("Asteroids", _canvas);
}
void CAsteroidGame::newAsteroid(int spawnlimit, int spawnsize, cv::Point location) {
	for (int i = 0; i < spawnlimit; i++) {
		CAsteroid astro = CAsteroid(location, _canvas.size(), spawnsize);
		astro.set_random();
		_asteroid_list.push_back(astro);
	}
}
void CAsteroidGame::fire() {
	const float speed = 1000;
	CMissile missile = CMissile(directionVec * (speed + magnitudeVec(_cship.get_vel())), _cship.get_pos(), MISSILE_SIZE);

	_missile_list.push_back(missile);
}
void CAsteroidGame::gameOver(std::string text) {
	_asteroid_list.clear();
	_missile_list.clear();
	gameOverText = text;
	while (!control.get_button(S2, 1));
	init_game();
}
void CAsteroidGame::splitAsteroid(CAsteroid astro) {
	// split asteroid if larger than half the maximum size
	if (astro.get_size() > ASTEROID_SIZE * 2 / 3) {
		newAsteroid(2, ASTEROID_SIZE / 4, astro.get_pos());
	}
}
void CAsteroidGame::collision() {
	for (int i = 0; i < _asteroid_list.size(); i++) {
		// missile collision logic
		for (int j = 0; j < _missile_list.size(); j++) {
			// missile collides with wall
			if (_missile_list.at(j).collide_wall(_canvas.size())) {
				_missile_list.at(j).hit();
			}
			// missile collides with asteroid
			else if (_missile_list.at(j).collide(_asteroid_list.at(i))) {
				_missile_list.at(j).hit();
				splitAsteroid(_asteroid_list.at(i));
				_asteroid_list.at(i).hit();
				score += 10;
			}
		}
	}

	// check if player collides with asteroid
	for (int i = 0; i < _asteroid_list.size(); i++) {
		if (_asteroid_list.at(i).collide(_cship)) {
			//splitAsteroid(_asteroid_list.at(i));
			_asteroid_list.at(i).hit();
			_cship.hit();
		}
	}

	// remove objects if their life is <= 0
	if (_cship.get_lives() <= 0) {
		gameOver("Game Over!");
	}
	else if (_asteroid_list.size() <= 0) {
		gameOver("You Win!");
	}
	for (int i = 0; i < _asteroid_list.size(); i++) {
		if (_asteroid_list.at(i).get_lives() <= 0) _asteroid_list.erase(_asteroid_list.begin() + i);
	}
	for (int i = 0; i < _missile_list.size(); i++) {
		if (_missile_list.at(i).get_lives() <= 0) _missile_list.erase(_missile_list.begin() + i);
	}

}
void CAsteroidGame::movement() {
	// Update time delta for movement calcs
	double deltaT = 1.0f / getfps();

	// asteroid movement
	for (int i = 0; i < _asteroid_list.size(); i++) {
		_asteroid_list.at(i).move(deltaT);
	}
	// missile movement
	for (int i = 0; i < _missile_list.size(); i++) {
		_missile_list.at(i).move(deltaT);
	}

	// ship movement
	cv::Point2f joystickPos = cv::Point2f((float)(control.get_analog(X_JOYSTICK) * 100.0f) - 50.0f, ((float)control.get_analog(Y_JOYSTICK) * -100.0f) + 50.0f);
	if (joystickPos.x > -DEADZONE && joystickPos.x < DEADZONE) {
		joystickPos.x = 0;
	}
	if (joystickPos.y > -DEADZONE && joystickPos.y < DEADZONE) {
		joystickPos.y = 0;
	}
	_cship.add_vel(joystickPos);
	_cship.move(deltaT);
	// what direction to shoot missiles in
	if (magnitudeVec(_cship.get_vel()) > 0) {
		directionVec = normalizeVec(_cship.get_vel());
	}
}
