// gpio_driver.h
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Aditya Parmar. All Rights Reserved.

#ifndef SPLASHKIT_GPIO_H
#define SPLASHKIT_GPIO_H

#include <stdint.h> // For stdint types
#ifdef RASPBERRY_PI
#include "pigpiod_if2.h" // For pigpio functions and types

namespace splashkit_lib
{
    // GPIO initialization and cleanup
    int sk_gpio_init();
    void sk_gpio_cleanup();

    // GPIO read/write and mode functions
    int sk_gpio_read(int pin);
    void sk_gpio_write(int pin, int value);
    void sk_gpio_set_mode(int pin, int mode);
    int sk_gpio_get_mode(int pin);
    void sk_gpio_set_pull_up_down(int pin, int pud);

    // PWM functions
    void sk_set_pwm_range(int pin, int range);
    void sk_set_pwm_frequency(int pin, int frequency);
    void sk_set_pwm_dutycycle(int pin, int dutycycle);

    // Sleep function (time delay)
    void sk_time_sleep(double seconds);

    // GPIO trigger function
    void sk_gpio_trigger(int pin, unsigned pulseLen, unsigned level);

    // I2C functions
    int sk_i2c_open(unsigned bus, unsigned addr, unsigned flags);
    void sk_i2c_close(unsigned handle);
    int sk_i2c_write_device(unsigned handle, char *data, unsigned count);
    int sk_i2c_read_device(unsigned handle, char *data, unsigned count);
}
#endif
#endif /* SPLASHKIT_GPIO_H */
