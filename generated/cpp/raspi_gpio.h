//
// SplashKit Generated Raspi Gpio C++ Code
// DO NOT MODIFY
//

#ifndef __raspi_gpio_h
#define __raspi_gpio_h

#include "networking.h"
#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

/**
* Converts an ASCII character to a binary value to be used with the Quad 14-segment display module (HT16K33 backpack).
* @param ascii_char The ascii character to be converted to a 16-bit binary value.
* @return The binary value used to display a character on the 14-segment display.
*/
unsigned short get_alpha_font_14_seg(char ascii_char);
/**
* Converts the specified pin value to an integer, to use in calculations.
* @param value The pin to read the value from.
* @return The pin value as an integer.
*/
int gpio_pin_to_int(gpio_pin_value value);
/**
* Checks if the system has GPIO capabilities.

* @return true if the system has GPIO capabilities, false otherwise.
*/
bool has_gpio();
/**
* This function should be called when you are finished using the GPIO library. It sets all pin modes to INPUT and values to LOW.

*
*/
void raspi_cleanup();
/**
* This function retrieves the mode of the specified pin.
* @param pin The pin to get the mode for.
* @return The mode of the pin.
*/
gpio_pin_mode raspi_get_mode(gpio_pin pin);
/**
* This function retrieves the pulse width for the specified pin.
* @param pin The pin to get the pulse width for.
* @return The pulse width of the pin.
*/
int raspi_get_servo_pulsewidth(gpio_pin pin);
/**
* Opens I2C communication on selected address. It will return -1 if not using Raspberry Pi.
* @param bus The bus of the I2C device.
* @param address The address of the I2C device.
* @return The handle referencing this particular connection.
*/
int raspi_i2c_open(int bus, int address);
/**
* Writes data to specified I2C connection.
* @param handle The reference for a specific I2C connection.
* @param data The data to send.
*
*/
void raspi_i2c_write(int handle, int data);
/**
* Writes 8-bit (1 byte) or 16-bit (2 bytes) data to specified I2C connection.
* @param handle The reference for a specific I2C connection.
* @param reg The register to send the data to
* @param data The data to send.
* @param bytes The number of bytes to be transferred.
*
*/
void raspi_i2c_write(int handle, int reg, int data, int bytes);
/**
* This function initializes the GPIO library for use. It should be called before any other GPIO functions.

*
*/
void raspi_init();
/**
* This function reads the value from the specified pin.
* @param pin The pin to read the value from.
* @return The value read from the pin.
*/
gpio_pin_value raspi_read(gpio_pin pin);
/**
* This function sets the mode of the specified pin to the specified mode.
* @param pin The pin to set the mode for.
* @param mode The mode to set for the pin.
*
*/
void raspi_set_mode(gpio_pin pin, gpio_pin_mode mode);
/**
* This function sets the pull-up/down mode for the specified pin.
* @param pin The pin to set the pull up/down mode for.
* @param pud The pull up/down mode to set for the pin.
*
*/
void raspi_set_pull_up_down(gpio_pin pin, pull_up_down pud);
/**
* This function sets the PWM duty cycle for the specified pin.
* @param pin The pin to set the PWM duty cycle for.
* @param dutycycle The PWM duty cycle to set for the pin.
*
*/
void raspi_set_pwm_dutycycle(gpio_pin pin, int dutycycle);
/**
* This function sets the PWM frequency for the specified pin.
* @param pin The pin to set the PWM frequency for.
* @param frequency The PWM frequency to set for the pin.
*
*/
void raspi_set_pwm_frequency(gpio_pin pin, int frequency);
/**
* This function sets the PWM range for the specified pin.
* Valid values for the range are 25 - 40000
* @param pin The pin to set the PWM range for.
* @param range The PWM range to set for the pin.
*
*/
void raspi_set_pwm_range(gpio_pin pin, int range);
/**
* This function sets the pulse width for the specified pin.
* @param pin The pin to set the pulse width for.
* @param pulsewidth The pulse width to set for the pin.
*
*/
void raspi_set_servo_pulsewidth(gpio_pin pin, int pulsewidth);
/**
* This function closes SPI communication on a particular channel.
* @param handle A reference to the specific SPI connection to close.
* @return A value indicating success or failure.
*/
int raspi_spi_close(int handle);
/**
* This function opens SPI communication on a particular channel. It will return -1 if not using Raspberry Pi.
* @param channel The SPI channel to use.
* @param speed The speed of data transfer (in baud).
* @param spi_flags Optional flags for the SPI modes and settings.
* @return The handle referencing this particular connection.
*/
int raspi_spi_open(int channel, int speed, int spi_flags);
/**
* This function transfers data through SPI, it sends data from sendBuf and receives it into recvBuf.
* @param handle The reference for a specific SPI connection.
* @param send The data to send.
* @param count The number of bytes to be transferred.
* @param bytes_transfered The number of bytes transferred (output)
* @return The data returned from the spi transfer
*/
string raspi_spi_transfer(int handle, const string &send, int count, int &bytes_transfered);
/**
* This function writes the specified value to the specified pin.
* @param pin The pin to write the value to.
* @param value The value to write to the pin.
*
*/
void raspi_write(gpio_pin pin, gpio_pin_value value);
/**
* This function closes the connection to the remote Raspberry Pi and releases any resources associated with it.
* @param pi The connection object to the remote Raspberry Pi.
* @return true if the cleanup was successful, false otherwise.
*/
bool remote_raspi_cleanup(connection pi);
/**
* This function retrieves the mode of a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to get the mode for.
* @return The mode of the pin.
*/
gpio_pin_mode remote_raspi_get_mode(connection pi, gpio_pin pin);
/**
* This function initialises a connection to a remote Raspberry Pi using the specified name, host, and port.
* @param name The name of the connection.
* @param host The host address of the Raspberry Pi.
* @param port The port to use for the connection.
* @return The connection object used to communicate with the remote Raspberry Pi.
*/
connection remote_raspi_init(const string &name, const string &host, unsigned short port);
/**
* This function reads the value from a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to read the value from.
* @return The value read from the pin.
*/
gpio_pin_value remote_raspi_read(connection pi, gpio_pin pin);
/**
* This function sets the mode of a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to set the mode for.
* @param mode The mode to set for the pin.
*
*/
void remote_raspi_set_mode(connection pi, gpio_pin pin, gpio_pin_mode mode);
/**
* This function sets the pull-up/down mode of a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to set the pull up/down mode for.
* @param pud The pull up/down mode to set for the pin.
*
*/
void remote_raspi_set_pull_up_down(connection pi, gpio_pin pin, pull_up_down pud);
/**
* This function sets the PWM duty cycle for a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to set the PWM duty cycle for.
* @param dutycycle The PWM duty cycle to set for the pin.
*
*/
void remote_raspi_set_pwm_dutycycle(connection pi, gpio_pin pin, int dutycycle);
/**
* This function sets the PWM frequency for a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to set the PWM frequency for.
* @param frequency The PWM frequency to set for the pin.
*
*/
void remote_raspi_set_pwm_frequency(connection pi, gpio_pin pin, int frequency);
/**
* This function sets the PWM range for a specific pin on a remote Raspberry Pi.
* Valid values for the range are 25 - 40000
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to set the PWM range for.
* @param range The PWM range to set for the pin.
*
*/
void remote_raspi_set_pwm_range(connection pi, gpio_pin pin, int range);
/**
* This function writes a specified value to a specific pin on a remote Raspberry Pi.
* @param pi The connection object to the remote Raspberry Pi.
* @param pin The pin to write the value to.
* @param value The value to write to the pin.
*
*/
void remote_raspi_write(connection pi, gpio_pin pin, gpio_pin_value value);

#endif /* __raspi_gpio_h */
