/**
 * @header raspi_adc
 * @brief Provides support for using an ADC device with the GPIO pins on the Raspberry Pi.
 * @author Aditya Parmar
 * 
 * @attribute group  raspberry
 * @attribute static raspberry
 */

#ifndef raspi_adc_hpp
#define raspi_adc_hpp

#include "types.h"
#include <string>

#ifndef RASPI_ADC_HPP
#define RASPI_ADC_HPP

#include <string>

namespace splashkit_lib
{
    // Forward declare adc_device as a pointer to internal struct _adc_data
    typedef struct _adc_data* adc_device;

    /**
     * Checks if an ADC device with the given name has been loaded.
     *
     * @param name The name used to identify the ADC device.
     * @returns True if an ADC device with the supplied name exists.
     */
    bool has_adc_device(const std::string &name);

    /**
     * Retrieve an ADC device that has been loaded.
     *
     * @param name The name of the ADC device.
     * @returns The adc_device pointer if found; otherwise, nullptr.
     */
    adc_device adc_device_named(const std::string &name);

    /**
     * Loads an ADC device on the specified I2C bus at a given address.
     *
     * @param name The name to assign this ADC device.
     * @param bus The I2C bus number.
     * @param address The I2C address of the ADC device.
     * @param type The type of ADC device (e.g., ADS7830, PCF8591).
     * @returns A valid adc_device on success, or nullptr on failure.
     */
    adc_device open_adc(const std::string &name, int bus, int address, adc_type type);

    /**
     * Opens an ADC device with the specified name and type.
     * Defaults to bus 1 and address 0x48.
     *
     * @param name The name of the ADC device to open.
     * @param type The type of ADC device (e.g., ADS7830, PCF8591).
     * @returns A valid adc_device on success, or nullptr on failure.
     */
    adc_device open_adc(const std::string &name, adc_type type);

    /**
     * Reads an 8-bit value from the specified ADC channel on the device.
     *
     * @param adc The ADC device to read from.
     * @param channel The channel number to read (range depends on ADC type).
     * @returns The ADC conversion value (0–255), or -1 on error.
     */
    int read_adc(adc_device adc, adc_pin channel);

    /**
     * Reads an 8-bit value from the specified ADC channel on the device using its name.
     *
     * @param name The ADC device name.
     * @param channel The channel number to read (range depends on ADC type).
     * @returns The ADC conversion value (0–255), or -1 on error.
     */
    int read_adc(const std::string &name, adc_pin channel);

    /**
     * Closes an ADC device given its pointer.
     *
     * @param adc The ADC device to close.
     */
    void close_adc(adc_device adc);

    /**
     * Closes an ADC device given its name.
     *
     * @param name The name of the ADC device to close.
     */
    void close_adc(const std::string &name);

    /**
     * Closes all ADC devices that have been opened.
     */
    void close_all_adc();
}
#endif /* raspi_adc_hpp */
#endif /* RASPI_ADC_HPP */