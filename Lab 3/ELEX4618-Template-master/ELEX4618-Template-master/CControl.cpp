#include "stdafx.h"
#include "CControl.h"
#include "Serial.h"
#include <string>


#define MAX_VAL 1024.0f
#define DEBOUNCE_TIME 0

Serial _com;
using namespace std;

CControl::CControl() {

}

CControl::~CControl() {

}

void CControl::init_com(int comport) {
	string strport = "COM";
	strport += to_string(comport);
	_com.open(strport);
	std::cout << "Opening Port " << strport << endl;
}

bool CControl::get_data(int type, int channel, int& result) {
	string tx_str = "G ";
	tx_str += to_string(type) + " " + to_string(channel) + "\n";

	_com.write(tx_str.c_str(), tx_str.length());

	string rx_str = "";
	char buff[2]; buff[0] = 0;
	while (buff[0] != '\n') { // go until \n character
		if (_com.read(buff, 1) > 0) { // if stuff available
			rx_str += buff[0]; // append buffer to string
		}
	}

	// Find and return the value of interest
	int delimitcount = 0;
	for (int i = 0; i < rx_str.length(); i++) {
		if (rx_str[i] == ' ') delimitcount++;
		if (delimitcount >= 3) {
			rx_str.erase(0, i); // erase everything except last number
			break;
		}
	}

	result = stoi(rx_str);
	
	return true;
}

bool CControl::set_data(int type, int channel, int val) {
	string tx_str = "S ";
	tx_str += to_string(type) + " " + to_string(channel) + " " + to_string(val) + "\n";
	_com.write(tx_str.c_str(), tx_str.length());
	return false;
}

bool CControl::get_button(int channel) {
	int nPressed;
	time_t clock;
	static bool wasPressed = false;

	get_data(0, channel, nPressed);
	bool bPressed = nPressed == 0;

	if (wasPressed && !bPressed) {
		wasPressed = false;
		return true;
	}

	if (bPressed) {
		wasPressed = true;
	}

	return false;
}

// Return as a percentage of full range
int CControl::get_analog(int channel) {
	int result;
	get_data(1, channel, result);
	return result;
}

void CControl::set_servo(int setPos, int channel) {
	int getPos;
	//do {
		set_data(2, channel, setPos);
	//	get_data(3, channel, getPos);
	//} while (getPos != setPos);
		// ^ this freezes up code - very not good
}