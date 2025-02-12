#include "DFGasSensor.h"

/// @brief Creates a gas sensor
/// @param I2CAddress The I2C address of the sensor
DFGasSensor::DFGasSensor(int I2CAddress) : Gas_Sensor(&Wire, I2CAddress) {
	GAS_I2C_ADDRESS = I2CAddress;
}

/// @brief Starts a gas sensor
/// @return True on success
bool DFGasSensor::begin() {
	Description.parameterQuantity = 1;
	Description.type = "Environmental Sensor";
	Description.name = "Gas Sensor";
	Description.parameters = {"Gas"};
	Description.units = {"ppm"};
	values.resize(Description.parameterQuantity);
	// Start the sensor
	if (Gas_Sensor.begin()) {
		if (Gas_Sensor.changeAcquireMode(Gas_Sensor.PASSIVITY)) {
			Gas_Sensor.setTempCompensation(Gas_Sensor.ON);
			String GasType = Gas_Sensor.queryGasType();
			Description.name = GasType + " Sensor";
			Description.parameters = {GasType};
			return true;
		}
	}
	return false;
}

/// @brief Take a gas measurement and stores it in an internal variable
/// @return True on success
bool DFGasSensor::takeMeasurement() {
	values[0] = Gas_Sensor.readGasConcentrationPPM();
	return values[0] != 0.0;
}	