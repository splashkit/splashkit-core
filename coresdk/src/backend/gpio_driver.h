/***********************************************
 * XQuestCode || Aditya Parmar
 * 🚀 © 2024 Aditya Parmar. All Rights Reserved.
 * This file is part of the SplashKit Core Library.
 * Use https://abyz.me.uk/rpi/pigpio/pdif2.html for reference
 ***********************************************/
#ifndef SPLASHKIT_GPIO_H
#define SPLASHKIT_GPIO_H

#include <stdint.h> // Include the appropriate header file for stdint.h
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
    void sk_gpio_cleanup();
}
#endif // SPLASHKIT_sk_gpio_H