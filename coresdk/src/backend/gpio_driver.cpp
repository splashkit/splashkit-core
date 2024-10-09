// gpio_driver.cpp
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Aditya Parmar. All Rights Reserved.

#include "gpio_driver.h"

#include <string>
#include <iostream>
#include <cstdlib>

#ifdef RASPBERRY_PI
#include "pigpiod_if2.h"

using namespace std;
// Use https://abyz.me.uk/rpi/pigpio/pdif2.html for reference
namespace splashkit_lib
{
    int pi = -1; // Initialize pi to -1 to indicate not started

    // Check if pigpio_start() has been called before any other GPIO functions
    bool check_pi()
    {
        if (pi < 0)
        {
            cout << "gpio_init() must be called before any other GPIO functions" << endl;
            return false;
        }
        else
            return true;
    }

    // Initialize the GPIO library
    int sk_gpio_init()
    {
        pi = pigpio_start(0, 0);
        if (pi < 0)
        {
            cout << "Failed to initialize pigpio" << endl;
        }
        return pi;
    }

    // Read the value of a GPIO pin
    int sk_gpio_read(int pin)
    {
        if (check_pi())
        {
            return gpio_read(pi, pin);
        }
        return -1; // Return error code if pi not initialized
    }

    // Write a value to a GPIO pin
    void sk_gpio_write(int pin, int value)
    {
        if (check_pi())
        {
            gpio_write(pi, pin, value);
        }
    }

    // Set the mode of a GPIO pin
    void sk_gpio_set_mode(int pin, int mode)
    {
        if (check_pi())
        {
            set_mode(pi, pin, mode);
        }
    }

    // Get the mode of a GPIO pin
    int sk_gpio_get_mode(int pin)
    {
        if (check_pi())
        {
            return get_mode(pi, pin);
        }
        return -1;
    }

    // Set pull-up/down resistor on a GPIO pin
    void sk_gpio_set_pull_up_down(int pin, int pud)
    {
        if (check_pi())
        {
            set_pull_up_down(pi, pin, pud);
        }
    }

    // Set PWM range on a GPIO pin
    void sk_set_pwm_range(int pin, int range)
    {
        if (check_pi())
        {
            set_PWM_range(pi, pin, range);
        }
    }

    // Set PWM frequency on a GPIO pin
    void sk_set_pwm_frequency(int pin, int frequency)
    {
        if (check_pi())
        {
            set_PWM_frequency(pi, pin, frequency);
        }
    }

    // Set PWM duty cycle on a GPIO pin
    void sk_set_pwm_dutycycle(int pin, int dutycycle)
    {
        if (check_pi())
        {
            set_PWM_dutycycle(pi, pin, dutycycle);
        }
    }

    // Sleep for a specified time in seconds
    void sk_time_sleep(double seconds)
    {
        time_sleep(seconds);
    }

 

    // Trigger a pulse on a GPIO pin
    void sk_gpio_trigger(int pin, unsigned pulseLen, unsigned level)
    {
        if (check_pi())
        {
            gpio_trigger(pi, pin, pulseLen, level);
        }
    }

    // Open an I2C device
    int sk_i2c_open(unsigned bus, unsigned addr, unsigned flags)
    {
        if (check_pi())
        {
            int handle = i2c_open(pi, bus, addr, flags);
            if (handle < 0)
            {
                cout << "Failed to open I2C device on bus " << bus << " at address 0x" << hex << addr << dec << endl;
            }
            return handle;
        }
        return -1;
    }

    // Close an I2C device
    void sk_i2c_close(unsigned handle)
    {
        if (check_pi())
        {
            i2c_close(pi, handle);
        }
    }

    // Write data to an I2C device
    int sk_i2c_write_device(unsigned handle, char *data, unsigned count)
    {
        if (check_pi())
        {
            int status = i2c_write_device(pi, handle, data, count);
            if (status < 0)
            {
                cout << "Failed to write to I2C device with handle " << handle << endl;
            }
            return status;
        }
        return -1;
    }

    // Read data from an I2C device
    int sk_i2c_read_device(unsigned handle, char *data, unsigned count)
    {
        if (check_pi())
        {
            int status = i2c_read_device(pi, handle, data, count);
            if (status < 0)
            {
                cout << "Failed to read from I2C device with handle " << handle << endl;
            }
            return status;
        }
        return -1;
    }

    // Cleanup the GPIO library
    void sk_gpio_cleanup()
    {
        if (check_pi())
        {
            pigpio_stop(pi);
            pi = -1; // Reset pi to indicate it's stopped
        }
    }
}
#endif
