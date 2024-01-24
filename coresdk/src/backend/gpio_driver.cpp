/***********************************************
 * XQuestCode || Aditya Parmar
 * © 2024 Aditya Parmar. All Rights Reserved.
 * This file is part of the SplashKit Core Library.
 * Use https://abyz.me.uk/rpi/pigpio/pdif2.html for reference
 ***********************************************/

#include "gpio_driver.h"

#include <string>
#include <iostream>
#include <cstdlib> // Add this line to include the necessary header for the exit() function

#ifdef RASPBERRY_PI
#include "pigpiod_if2.h"
#endif

using namespace std;

namespace splashkit_lib
{
    int pi;

    // Check if pigpio_init() has been called before any other GPIO functions
    void check_pi()
    {
#ifdef RASPBERRY_PI
        if (pi < 0)
        {
            cout << "pigpio_init() must be called before any other GPIO functions" << endl;
            exit(1);
        }
#endif
    }

    // Initialize the GPIO library
    int sk_gpio_init()
    {
#ifdef RASPBERRY_PI
        pi = pigpio_start(0, 0);
        return pi;
#else
        return -1;
#endif
    }

    // Read the value of a GPIO pin
    int sk_gpio_read(int pin)
    {
#ifdef RASPBERRY_PI
        check_pi();
        return gpio_read(pi, pin);
#else
        cout << "gpio_read() called, but not on a Raspberry Pi" << endl;
        return -1;
#endif
    }

    // Write a value to a GPIO pin
    void sk_gpio_write(int pin, int value)
    {
#ifdef RASPBERRY_PI
        check_pi();
        gpio_write(pi, pin, value);
#else
        cout << "gpio_write() called, but not on a Raspberry Pi" << endl;
#endif
    }

    // Set the mode of a GPIO pin
    void sk_gpio_set_mode(int pin, int mode)
    {
#ifdef RASPBERRY_PI
        check_pi();
        set_mode(pi, pin, mode);
#else
        cout << "gpio_set_mode() called, but not on a Raspberry Pi" << endl;
#endif
    }
    int sk_gpio_get_mode(int pin)
    {
#ifdef RASPBERRY_PI
        check_pi();
        return get_mode(pi, pin);
#else
        cout << "gpio_get_mode() called, but not on a Raspberry Pi" << endl;
        return -1;
#endif
    }
    void sk_gpio_set_pull_up_down(int pin, int pud)
    {
#ifdef RASPBERRY_PI
        check_pi();
        set_pull_up_down(pi, pin, pud);
#else

        cout << "gpio_set_pull_up_down() called, but not on a Raspberry Pi" << endl;
#endif
    }
    void sk_set_pwm_range(int pin, int range)
    {
#ifdef RASPBERRY_PI
        check_pi();
        set_PWM_range(pi, pin, range);
#else
        cout << "set_PWM_range() called, but not on a Raspberry Pi" << endl;
#endif
    }
    void sk_set_pwm_frequency(int pin, int frequency)
    {
#ifdef RASPBERRY_PI
        check_pi();
        set_PWM_frequency(pi, pin, frequency);
#else
        cout << "set_PWM_frequency() called, but not on a Raspberry Pi" << endl;
#endif
    }
    void sk_set_pwm_dutycycle(int pin, int dutycycle)
    {
#ifdef RASPBERRY_PI
        check_pi();
        set_PWM_dutycycle(pi, pin, dutycycle);
#else
        cout << "set_PWM_dutycycle() called, but not on a Raspberry Pi" << endl;
#endif
    }
    

    // Cleanup the GPIO library
    void sk_gpio_cleanup()
    {
#ifdef RASPBERRY_PI
        check_pi();

        pigpio_stop(pi);
#else
        cout << "pigpio_cleanup() called, but not on a Raspberry Pi" << endl;
#endif
    }
}