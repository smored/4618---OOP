#include "stdafx.h"
#include "CControl.h"
#include "Serial.h"
#include <string>

Serial _com;
using namespace std;

void init_com(int comport) {
	_com.open("COM4");
}

bool get_data(int type, int channel, int& result) {
	string tx_str = "G ", rx_str = "";
	char eol = '\n', buff[2];
	buff[0] = 0;
	tx_str += to_string(type) + " " + to_string(channel) + "\n";

	_com.write(tx_str.c_str(), tx_str.length());

	while (buff[0] != eol) { // go until \n character
		if (_com.read(buff, 1) > 0) { // if stuff available
			rx_str += buff[0]; // append buffer to string
		}
	}

	cout << rx_str;
	return true;
}

bool set_data(int type, int channel, int val) {

}

bool get_button(int channel) {

}

// Return as a percentage of full range
// Todo: how many bits?
float get_analog(int channel) {
	int result;
	const int resolution = 2^12;
	while (!get_data(1, channel, result)); // wait until success
	return result/resolution;
}

