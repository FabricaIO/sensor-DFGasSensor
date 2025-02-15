/*
* This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2024 Sam Groveman
* Contributors: Sam Groveman
* 
* External libraries needed:
* DFRobot_MultiGasSensor: https://github.com/DFRobot/DFRobot_MultiGasSensor
* 
* Gas sensors: https://www.dfrobot.com/product-2510.html
* 
* I2C address select via dip-switch, default to 0x74, A1 and A0 are grouped into 4 I2C addresses.
*             | A0 | A1 |
*             | 0  | 0  |    0x74 default I2C address  
*             | 0  | 1  |    0x75
*             | 1  | 0  |    0x76
*             | 1  | 1  |    0x77
*/

#pragma once
#include <Arduino.h>
#include <DFRobot_MultiGasSensor.h>
#include <Wire.h>
#include <Sensor.h>

class DFGasSensor: public Sensor {
	public:        
		DFGasSensor(int I2CAddress = 0x74);
		bool begin();
		bool takeMeasurement();

	protected:
		/// @brief I2C address of gas sensor sensor
		int GAS_I2C_ADDRESS;

		/// @brief Gas sensor object
		DFRobot_GAS_I2C Gas_Sensor;

};
