/**
 * @header raspi_gpio
 * @brief Splashkit allows you to read and write to the GPIO pins on the Raspberry Pi.
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
     * @brief Opens SPI communication on selected channel.
     *
     * This function opens SPI communication on a particular channel. It will return -1 if not using Raspberry Pi.
     *
     * @param channel    The SPI channel to use.
     * @param speed      The speed of data transfer (in baud).
     * @param spi_flags  Optional flags for the SPI modes and settings.
     * @returns          The handle referencing this particular connection.
     */
    int raspi_spi_open(int channel, int speed, int spi_flags);

    /**
     * @brief Closes SPI communication on selected channel. It will return -1 if not using Raspberry Pi.
     *
     * This function closes SPI communication on a particular channel.
     *
     * @param handle  A reference to the specific SPI connection to close.
     * @returns       A value indicating success or failure.
     */
    int raspi_spi_close(int handle);

    /**
     * @brief Transfers data on specified SPI connection. It will return -1 if not using Raspberry Pi.
     *
     * This function transfers data through SPI, it sends data from sendBuf and receives it into recvBuf.
     *
     * @param handle   The reference for a specific SPI connection.
     * @param sendBuf  The memory buffer for sending data.
     * @param recvBuf  The memory buffer for receiving data.
     * @param count    The number of bytes to be transferred.
     * @returns        The number of bytes that have actually been transfered.
     */
    int raspi_spi_transfer(int handle, string sendBuf, string recvBuf, int count);
	
    /**
     * @brief Cleans up and releases any resources used by the GPIO library.
     *
     * This function should be called when you are finished using the GPIO library. It sets all pin modes to INPUT and values to LOW.
     */
    void raspi_cleanup();
}
#endif /* raspi_gpio_hpp */
