#pragma once

#include "Serial.h"

/** Serial.h
 *
 * @brief Methods for communcations with the MSP432
 *
 * This class uses a com port to emulate serial communcation with the MSP432
 * using the Serial.h library with the OOP 4618 serial protocol
 * 
 * @author Kurt Querengesser
 *
 * @version 1.0 -- 28 Jan 2022
 */
class CControl
{
private:
	Serial _com;									    ///< private com object for use in serial communication
public:

	/** @brief Class Constructor
	* @param no parameters
	* @return no returns
	**/
	CControl();						
	/** @brief Class Deconstructor
	* @param no parameters
	* @return no returns
	**/
	~CControl();							

	/** @brief initializes the com port
	* @param comport: What com port to initialize
	* @return no returns
	**/
	void init_com(int default_port = -1);
	/** @brief reads data from serial port
	* @param type: what mode to operate
	* @param channel: which channel to use
	* @param result: a pointer to the result to which the value will be assigned
	* @return returns true if successful
	**/
	bool get_data(int type, int channel, int& result); 
	/** @brief sends data across serial port
	* @param type: what mode to operate
	* @param channel: which channel to use
	* @param val: what value to set 
	* @return returns true if successful
	**/
	bool set_data(int type, int channel, int val);
	/** @brief debounces a button on specified channel
	* @param specify channel button is on
	* @return returns debounced digital button
	**/
	bool get_button(int channel);
	/** @brief Gets analog over serial
	* @param channel: what pin to use
	* @return returns an analog float value as a percentage of maximum
	**/
	float get_analog(int channel);
	/** @brief Method for setting servo and making my life easier
	* @param channel: [0-4] Select which servo channel to use
	* @param val: the angle to which the servo will approach
	* @return no returns
	**/
	void set_servo(int setPos, int channel = 0);
};