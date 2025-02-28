// gpio_driver.h
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Aditya Parmar. All Rights Reserved.

#ifndef SPLASHKIT_GPIO_H
#define SPLASHKIT_GPIO_H

#include <stdint.h> // Include the appropriate header file for stdint.h
#ifdef RASPBERRY_PI
namespace splashkit_lib
{
    int sk_gpio_init();
    int sk_gpio_read(int pin);
    void sk_gpio_set_mode(int pin, int mode);
    int sk_gpio_get_mode(int pin);
    void sk_gpio_set_pull_up_down(int pin, int pud);
    void sk_gpio_write(int pin, int value);
    void sk_set_pwm_range(int pin, int range);
    void sk_set_pwm_frequency(int pin, int frequency);
    void sk_set_pwm_dutycycle(int pin, int dutycycle);
    void sk_clear_gpio_bank();
	int sk_spi_open(int channel, int speed, int spi_flags);
    int sk_spi_close(int handle);
    int sk_spi_transfer(int handle, char *sendBuf, char *recvBuf, int count);
    void sk_gpio_cleanup();
}
#endif
#endif /* defined(gpio_driver) */
