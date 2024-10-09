/**
 * @header raspi_gpio
 * @brief Splashkit allows you to read and write to the GPIO pins on the Raspberry Pi, as well as communicate using I2C and handle GPIO events.
 * @author Aditya Parmar
 * @attribute group raspberry
 * @attribute static raspberry
 */

#ifndef raspi_gpio_hpp
#define raspi_gpio_hpp

#include <stdint.h>
#include "gpio_driver.h"
#include "types.h"

namespace splashkit_lib
{
    /**
     * @brief Initializes the GPIO library.
     *
     * This function initializes the GPIO library for use. It should be called before any other GPIO functions.
     */
    void raspi_init();

    /**
     * Checks if the system has GPIO capabilities.
     *
     * @return true if the system has GPIO capabilities, false otherwise.
     */
    bool has_gpio();

    /**
     * @brief Sets the mode of the specified pin.
     *
     * This function sets the mode of the specified pin to the specified mode.
     *
     * @param pin   The pin to set the mode for.
     * @param mode  The mode to set for the pin.
     */
    void raspi_set_mode(pins pin, pin_modes mode);

    /**
     * @brief Gets the mode of the specified pin.
     *
     * This function retrieves the mode of the specified pin.
     *
     * @param pin   The pin to get the mode for.
     * @returns     The mode of the pin.
     */
    pin_modes raspi_get_mode(pins pin);

    /**
     * @brief Writes a value to the specified pin.
     *
     * This function writes the specified value to the specified pin.
     *
     * @param pin    The pin to write the value to.
     * @param value  The value to write to the pin.
     */
    void raspi_write(pins pin, pin_values value);

    /**
     * @brief Sets the pull up/down mode for the specified pin.
     *
     * This function sets the pull-up/down mode for the specified pin.
     *
     * @param pin   The pin to set the pull up/down mode for.
     * @param pud   The pull up/down mode to set for the pin.
     */
    void raspi_set_pull_up_down(pins pin, pull_up_down pud);

    /**
     * @brief Sets the PWM range for the specified pin.
     *
     * This function sets the PWM range for the specified pin.
     *
     * @param pin    The pin to set the PWM range for.
     * @param range  The PWM range to set for the pin.
     */
    void raspi_set_pwm_range(pins pin, int range);

    /**
     * @brief Sets the PWM frequency for the specified pin.
     *
     * This function sets the PWM frequency for the specified pin.
     *
     * @param pin         The pin to set the PWM frequency for.
     * @param frequency   The PWM frequency to set for the pin.
     */
    void raspi_set_pwm_frequency(pins pin, int frequency);

    /**
     * @brief Sets the PWM duty cycle for the specified pin.
     *
     * This function sets the PWM duty cycle for the specified pin.
     *
     * @param pin         The pin to set the PWM duty cycle for.
     * @param dutycycle   The PWM duty cycle to set for the pin.
     */
    void raspi_set_pwm_dutycycle(pins pin, int dutycycle);

    /**
     * @brief Reads the value from the specified pin.
     *
     * This function reads the value from the specified pin.
     *
     * @param pin  The pin to read the value from.
     * @returns    The value read from the pin.
     */
    pin_values raspi_read(pins pin);
    /**
     * @brief Triggers a pulse on the specified pin.
     * 
     * This function triggers a pulse on the specified pin for the specified pulse length and level.
     * 
     * @param pin       The pin to trigger
     * @param pulseLen  The length of the pulse
     * @param level     The level of the pulse
     * 
     */
    void raspi_trigger(pins pin, unsigned pulseLen, unsigned level);
    /**
     * @brief Opens an I2C bus and returns a handle for communication.
     *
     * This function opens an I2C bus at the specified bus and address.
     *
     * @param bus    The I2C bus number to use.
     * @param addr   The I2C address of the device.
     * @returns      The handle for the I2C device, or -1 on error.
     */
    int raspi_i2c_open(int bus, int addr);

    /**
     * @brief Closes the I2C bus for the specified handle.
     *
     * This function closes the I2C bus connection for the specified handle.
     *
     * @param handle The handle of the I2C bus to close.
     */
    void raspi_i2c_close(int handle);

    /**
     * @brief Writes data to the I2C device.
     *
     * This function writes the specified data to the I2C device.
     *
     * @param handle  The handle of the I2C device.
     * @param data    The data to write to the device.
     * @param len     The length of the data to write.
     */
    void raspi_i2c_write(int handle, const char *data, int len);

    /**
     * @brief Reads data from the I2C device.
     *
     * This function reads data from the specified I2C device.
     *
     * @param handle  The handle of the I2C device.
     * @param data    The buffer to store the data.
     * @param len     The number of bytes to read.
     */
    void raspi_i2c_read(int handle, char *data, int len);

    /**
     * @brief Sleep for the specified number of seconds.
     *
     * This function provides a delay for the specified number of seconds.
     *
     * @param seconds The number of seconds to sleep.
     */
    void raspi_sleep(double seconds);

    /**
     * @brief Cleans up and releases any resources used by the GPIO library.
     *
     * This function should be called when you are finished using the GPIO library. It sets all pin modes to INPUT and values to LOW.
     */
    void raspi_cleanup();
}

#endif /* raspi_gpio_hpp */
