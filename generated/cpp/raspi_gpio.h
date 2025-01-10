//
// SplashKit Generated Raspi Gpio C++ Code
// DO NOT MODIFY
//

#ifndef __raspi_gpio_h
#define __raspi_gpio_h

#include "types.h"
#include <string>
#include <vector>
#include <cstdint>
using std::string;
using std::vector;

bool has_gpio();
void raspi_cleanup();
pin_modes raspi_get_mode(pins pin);
void raspi_init();
pin_values raspi_read(pins pin);
void raspi_set_mode(pins pin, pin_modes mode);
void raspi_set_pull_up_down(pins pin, pull_up_down pud);
void raspi_set_pwm_dutycycle(pins pin, int dutycycle);
void raspi_set_pwm_frequency(pins pin, int frequency);
void raspi_set_pwm_range(pins pin, int range);
void raspi_write(pins pin, pin_values value);

#endif /* __raspi_gpio_h */
