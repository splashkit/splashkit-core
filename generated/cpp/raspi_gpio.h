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

bool has_gpio();
void raspi_cleanup();
gpio_pin_mode raspi_get_mode(gpio_pin pin);
int raspi_get_servo_pulsewidth(gpio_pin pin);
void raspi_init();
gpio_pin_value raspi_read(gpio_pin pin);
void raspi_set_mode(gpio_pin pin, gpio_pin_mode mode);
void raspi_set_pull_up_down(gpio_pin pin, pull_up_down pud);
void raspi_set_pwm_dutycycle(gpio_pin pin, int dutycycle);
void raspi_set_pwm_frequency(gpio_pin pin, int frequency);
void raspi_set_pwm_range(gpio_pin pin, int range);
void raspi_set_servo_pulsewidth(gpio_pin pin, int pulsewidth);
int raspi_spi_close(int handle);
int raspi_spi_open(int channel, int speed, int spi_flags);
string raspi_spi_transfer(int handle, const string &send, int count, int &bytes_transfered);
void raspi_write(gpio_pin pin, gpio_pin_value value);
bool remote_raspi_cleanup(connection pi);
gpio_pin_mode remote_raspi_get_mode(connection pi, gpio_pin pin);
connection remote_raspi_init(const string &name, const string &host, unsigned short port);
gpio_pin_value remote_raspi_read(connection pi, gpio_pin pin);
void remote_raspi_set_mode(connection pi, gpio_pin pin, gpio_pin_mode mode);
void remote_raspi_set_pull_up_down(connection pi, gpio_pin pin, pull_up_down pud);
void remote_raspi_set_pwm_dutycycle(connection pi, gpio_pin pin, int dutycycle);
void remote_raspi_set_pwm_frequency(connection pi, gpio_pin pin, int frequency);
void remote_raspi_set_pwm_range(connection pi, gpio_pin pin, int range);
void remote_raspi_write(connection pi, gpio_pin pin, gpio_pin_value value);
int to_int(gpio_pin_value value);

#endif /* __raspi_gpio_h */
