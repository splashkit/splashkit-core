//
// SplashKit Generated Raspi Adc C++ Code
// DO NOT MODIFY
//

#ifndef __raspi_adc_h
#define __raspi_adc_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _adc_device_data;
typedef struct _adc_device_data *adc_device;
/**
* Retrieve an ADC device that has been loaded.
* @param name The name of the ADC device.
* @return The adc_device pointer if found; otherwise, nullptr.
*/
adc_device adc_device_named(const string &name);
/**
* Closes an ADC device given its pointer.
* @param adc The ADC device to close.
*
*/
void close_adc(adc_device adc);
/**
* Closes an ADC device given its name.
* @param name The name of the ADC device to close.
*
*/
void close_adc(const string &name);
/**
* Closes all ADC devices that have been opened.

*
*/
void close_all_adc();
/**
* Checks if an ADC device with the given name has been loaded.
* @param name The name used to identify the ADC device.
* @return true if an ADC device with the supplied name exists.
*/
bool has_adc_device(const string &name);
/**
* Opens an ADC device with the specified name and type. Defaults to bus 1 and address 0x48.
* @param name The name of the ADC device to open.
* @param type_of_adc The type of ADC device (e.g., ADS7830, PCF8591).
* @return A valid adc_device on success, or nullptr on failure.
*/
adc_device open_adc(const string &name, adc_type type_of_adc);
/**
* Loads an ADC device on the specified I2C bus at a given address.
* @param name The name to assign this ADC device.
* @param bus The I2C bus number.
* @param address The I2C address of the ADC device.
* @param type_of_adc The type of ADC device (e.g., ADS7830, PCF8591).
* @return A valid adc_device on success, or nullptr on failure.
*/
adc_device open_adc(const string &name, int bus, int address, adc_type type_of_adc);
/**
* Reads an 8-bit value from the specified ADC channel on the device.
* @param adc The ADC device to read from.
* @param channel The channel number to read (range depends on ADC type).
* @return The ADC conversion value (0–255), or -1 on error.
*/
int read_adc(adc_device adc, adc_pin channel);
/**
* Reads an 8-bit value from the specified ADC channel on the device using its name.
* @param name The ADC name string to close.
* @param channel The channel number to read (range depends on ADC type).
* @return The ADC conversion value (0–255), or -1 on error.
*/
int read_adc(const string &name, adc_pin channel);

#endif /* __raspi_adc_h */
