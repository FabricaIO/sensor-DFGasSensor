#include "DFGasSensor.h"

/// @brief Creates a gas sensor
/// @param Name The device name
/// @param I2C_bus The I2C bus attached to the sensor
/// @param I2CAddress The I2C address of the sensor
DFGasSensor::DFGasSensor(String Name, TwoWire* I2C_bus, int I2CAddress) : Gas_Sensor(I2C_bus, I2CAddress), Sensor(Name) {
	i2c_bus = I2C_bus;
}

/// @brief Creates a gas sensor
/// @param Name The device name
/// @param sda SDA pin to use for I2C bus
/// @param scl SCL pin to use for I2C bus
/// @param I2C_bus The I2C bus attached to the sensor
/// @param I2CAddress The I2C address of the sensor
DFGasSensor::DFGasSensor(String Name, int sda, int scl, TwoWire* I2C_bus, int I2CAddress) : Gas_Sensor(I2C_bus, I2CAddress), Sensor(Name) {
	i2c_bus = I2C_bus;
	scl_pin = scl;
	sda_pin = sda;
}

/// @brief Starts a gas sensor
/// @return True on success
bool DFGasSensor::begin() {
	Description.parameterQuantity = 1;
	Description.type = "Environmental Sensor";
	Description.parameters = {"Gas"};
	Description.units = {"ppm"};
	values.resize(Description.parameterQuantity);
	// Start I2C bus if not started
	if (scl_pin > -1 && sda_pin > -1) {
		if (!i2c_bus->begin(sda_pin, scl_pin)) {
			return false;
		}
	} else {
		if (!i2c_bus->begin()) {
			return false;
		}
	}
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