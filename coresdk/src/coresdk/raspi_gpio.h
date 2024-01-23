/**
 * @header  raspberry
 * @author  Aditya Parmar
 * @brief   Splashkit allows you to read and write to the GPIO pins on the Raspberry Pi.
 *
 * @attribute group  raspberry
 * @attribute static raspberry
 */
#ifndef raspi_gpio_h
#define raspi_gpio_h


#include <stdint.h> // Include the appropriate header file for stdint.h
#include "gpio_driver.h"
#include "types.h"

namespace splashkit_lib
{
    /**
     * @brief Initializes the GPIO library.
     */
    void raspi_init();

    /**
     * @brief Sets the mode of the specified pin.
     *
     * @param pin   The pin to set the mode for.
     * @param mode  The mode to set for the pin.
     */
    void raspi_set_mode(pins pin, pin_modes mode);

    /**
     * @brief Gets the mode of the specified pin.
     *
     * @param pin   The pin to get the mode for.
     * @returns     The mode of the pin.
     */
    pin_modes raspi_get_mode(pins pin);

    /**
     * @brief Writes a value to the specified pin.
     *
     * @param pin    The pin to write the value to.
     * @param value  The value to write to the pin.
     */
    void raspi_write(pins pin, pin_values value);

    /**
     * @brief Sets the pull up/down mode for the specified pin.
     *
     * @param pin   The pin to set the pull up/down mode for.
     * @param pud   The pull up/down mode to set for the pin.
     */
    void raspi_set_pull_up_down(pins pin, pull_up_down pud);

    /**
     * Sets the PWM range for the specified pin.
     *
     * @param pin    The pin to set the PWM range for.
     * @param range  The PWM range to set for the pin.
     */
    void raspi_set_pwm_range(pins pin, int range);

    /**
     * Sets the PWM frequency for the specified pin.
     *
     * @param pin         The pin to set the PWM frequency for.
     * @param frequency   The PWM frequency to set for the pin.
     */
    void raspi_set_pwm_frequency(pins pin, int frequency);

    /**
     * Sets the PWM duty cycle for the specified pin.
     *
     * @param pin         The pin to set the PWM duty cycle for.
     * @param dutycycle   The PWM duty cycle to set for the pin.
     */
    void raspi_set_pwm_dutycycle(pins pin, int dutycycle);

    /**
     * Reads the value from the specified pin.
     *
     * @param pin  The pin to read the value from.
     * @returns    The value read from the pin.
     */
    pin_values raspi_read(pins pin);



    /**
     * Cleans up and releases any resources used by the GPIO library ( sets all pin modes to INPUT and values to LOW ). This should be called when you are finished using the GPIO library.
     */
    void raspi_cleanup();
}
#endif // RASPI_GPIO_H