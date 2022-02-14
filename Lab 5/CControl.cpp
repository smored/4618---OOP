#include "stdafx.h"
#include "CControl.h"
#include "Serial.h"
#include <string>


#define MAX_VAL 1024.0f
#define DEBOUNCE_TIME 0
#define TIMEOUT 100


using namespace std;

CControl::CControl() {

}

CControl::~CControl() {

}

bool CControl::getPort(int portNum) {
	cout << "Opening COM: " << portNum;

	const string strport = "COM";
	Serial tempCom;
	tempCom.open(strport + to_string(portNum));

	if (tempCom.is_open()) {
		cout << "\nwaiting for ACK...\n";
		if (set_data(0, 37, 1, tempCom)) {
			cout << "COM Port is open: " << portNum << endl;
			//tempCom.~Serial();
			return true;
		}
		else {
			cout << "Error: No ACK on " << portNum << endl;
		}
	}
	else {
		cout << "\nError: could not open port\n";
	}
	//tempCom.~Serial();
	return false;
}

void CControl::init_com(int port) {
	const string strport = "COM";
	_com.open(strport + to_string(port));
	std::cout << "Opening Port " << strport + to_string(port) << endl;

}

void CControl::init_com() {
	// Loop through all comm posibilities, check if open and then list available ports to choose from
	const int MAX_PORTS = 50;
	int comport;
	for (comport = 0; comport < MAX_PORTS; comport++) {
		if (getPort(comport)) break;
	}

	if (comport >= MAX_PORTS) {
		cout << "Error: Could not find COM Port" << endl;
	}
	else {
		_com.open("COM" + to_string(comport));
	}
}

bool CControl::get_data(int type, int channel, int& result) {
	_com.flush();
	string tx_str = "G ";
	tx_str += to_string(type) + " " + to_string(channel) + '\n';

	//cout << "get_data writing: " << tx_str << endl;
	_com.write(tx_str.c_str(), tx_str.length());

	string rx_str = "";
	char buff[2]; buff[0] = 0;

	auto start = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	while (buff[0] != '\n') { // go until \n character
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= TIMEOUT) {
			cout << "Error: get_data() timeout..." << endl;
			return false;
		}
		if (_com.read(buff, 1) > 0) { // if stuff available
			rx_str += buff[0]; // append buffer to string
		}
		now = std::chrono::system_clock::now();
	}
	//cout << "get_data value returned: " << rx_str << endl;
	// Find and return the value of interest
	int delimitcount = 0;
	for (int i = 0; i < rx_str.length(); i++) {
		if (rx_str[i] == ' ') delimitcount++;
		if (delimitcount >= 3) {
			rx_str.erase(0, i); // erase everything except last number
			break;
		}
	}

	// Remove '\n' and ' ' characters so stoi() doesnt blow up
	if (rx_str[rx_str.length() - 1] == '\n') rx_str.erase(rx_str.length() - 1);
	if (rx_str[0] == ' ') rx_str.erase(0,0);

	result = stoi(rx_str);

	return true;
}

bool CControl::set_data(int type, int channel, int val) {
	_com.flush();
	string tx_str = "S ", rx_str;
	tx_str += to_string(type) + " " + to_string(channel) + " " + to_string(val) + '\n';
	//cout << "set_data writing: " << tx_str << endl;
	_com.write(tx_str.c_str(), tx_str.length());

	// Check if data is acknowledged
	auto start = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	char buff[2]; buff[0] = 0;

	while (buff[0] != '\n') { // go until \n character
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= TIMEOUT) {
			cout << "Error: get_data() timeout..." << endl;
			return false;
		}
		if (_com.read(buff, 1) > 0) { // if stuff available
			rx_str += buff[0]; // append buffer to string
		}
		now = std::chrono::system_clock::now();
	}

	if (rx_str.empty()) {
		return false;
	}
	else {
		return true;
	}
}

bool CControl::set_data(int type, int channel, int val, Serial &port) {
	string tx_str = "S ";
	tx_str += to_string(type) + " " + to_string(channel) + " " + to_string(val) + '\n';
	port.write(tx_str.c_str(), tx_str.length());

	// Check if data is acknowledged
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

	char buff[2]; buff[0] = 0;
	while (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() <= 50) {
		if (port.read(buff, 1) > 0) {
			return true;
		}
		now = std::chrono::system_clock::now();
	}
	return false;
}

bool CControl::get_button(int channel, int BID) {

	static bool reset[] = {0,0};
	int result;
	bool isPressed;

	get_data(0, channel, result); isPressed = result == 0;

	if (!reset[BID]) {
		if (isPressed) {
			reset[BID] = true;
			return true;
		}
	}
	else {
		if (!isPressed) {
			reset[BID] = false;
		}
	}

	return false;

	//int nPressed;
	//static bool wasPressed = false;
	///*float time1 = cv::getTickCount();
	//static float time2 = cv::getTickCount();*/

	//get_data(0, channel, nPressed);
	//bool bPressed = nPressed == 0;

	//	// changed
	//	if (bPressed && !wasPressed) {
	//		wasPressed = false;
	//		return true;
	//	}

	//if (bPressed) {
	//	wasPressed = true;
	//	//time2 = cv::getTickCount();
	//}

	//return false;

}

// Return as a percentage of full range
float CControl::get_analog(int channel) {
	int result;
	get_data(1, channel, result);
	return (float)result/1023.0f;
}

void CControl::set_servo(int setPos, int channel) {
	int getPos;
	//do {
		set_data(2, channel, setPos);
	//	get_data(3, channel, getPos);
	//} while (getPos != setPos);
		// ^ this freezes up code - very not good
}