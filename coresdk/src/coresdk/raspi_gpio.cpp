// raspi_gpio.cpp
//  splashkit
// Created by Aditya Parmar on 20/01/2024.
// Copyright © 2024 XQuestCode. All rights reserved.
#include "raspi_gpio.h"
#include "gpio_driver.h"
#include <iostream>
using namespace std;

namespace splashkit_lib
{
    // Each index points to PIN_1, PIN_2, PIN_3, etc.
    int BCMpinData[] = {
        -1, -1, 2, -1, 3, -2, 4, 14, -2, 15, 17, 18, 27, -2, 22, 23, -1, 24, 10, -2, 9, 25, 11, 8, -2, 7, 0, 1, 5, -2, -6, 12, 13, -2, 19, 16, 26, 20, -2, 21};

    int boardToBCM(pins pin)
    {
        if (pin >= PIN_1 && pin <= PIN_40)
        {
            return BCMpinData[static_cast<int>(pin) - static_cast<int>(PIN_1)];
        }
        cout << "Invalid board pin" << endl;
        return -1;
    }
    bool has_gpio()
    {
#ifdef RASPBERRY_PI
        return true;
#else
        return false;
#endif
    }

    // Initialize GPIO resources
    void raspi_init()
    {
#ifdef RASPBERRY_PI
        sk_gpio_init();
#else
        cout << "GPIO not supported on this platform" << endl;
#endif
    }

    // Set the mode of the given pin
    void raspi_set_mode(pins pin, pin_modes mode)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant modify a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant modify a Ground pin" << endl;
        }
        else
        {
            sk_gpio_set_mode(bcmPin, static_cast<int>(mode));
        }
#else
        cout << "Unable to set mode - GPIO not supported on this platform" << endl;
#endif
    }
    pin_modes raspi_get_mode(pins pin)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant modify a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant modify a Ground pin" << endl;
        }
        else
        {
            return static_cast<pin_modes>(sk_gpio_get_mode(bcmPin));
        }
        return GPIO_DEFAULT_MODE;
#else
        return GPIO_DEFAULT_MODE;
        cout << "Unable to get mode - GPIO not supported on this platform" << endl;
#endif
    }

    // Write a value to the given pin
    void raspi_write(pins pin, pin_values value)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant write a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant write a Ground pin" << endl;
        }
        else
        {
            sk_gpio_write(bcmPin, static_cast<int>(value));
        }
#else
        cout << "Unable to write pin - GPIO not supported on this platform" << endl;
#endif
    }

    // Read the value of the given pin
    pin_values raspi_read(pins pin)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Reading of PIN: " << pin << " would always be HIGH" << endl;
            return GPIO_HIGH;
        }
        else if (bcmPin == -2)
        {

            cout << "Reading of PIN: " << pin << " would always be LOW" << endl;
            return GPIO_LOW;
        }
        return static_cast<pin_values>(sk_gpio_read(bcmPin));
#else
        cout << "Unable to read pin - GPIO not supported on this platform" << endl;
        return GPIO_DEFAULT_VALUE;
#endif
    }
    void raspi_set_pull_up_down(pins pin, pull_up_down pud)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant modify a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant modify a Ground pin" << endl;
        }
        else
        {
            sk_gpio_set_pull_up_down(bcmPin, static_cast<int>(pud));
        }
#else
        cout << "Unable to set pull up/down - GPIO not supported on this platform" << endl;
#endif
    }
    void raspi_set_pwm_range(pins pin, int range)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant modify a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant modify a Ground pin" << endl;
        }
        else
        {
            sk_set_pwm_range(bcmPin, range);
        }
#else
        cout << "Unable to set pwm range - GPIO not supported on this platform" << endl;
#endif
    }
    void raspi_set_pwm_frequency(pins pin, int frequency)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant modify a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant modify a Ground pin" << endl;
        }
        else
        {
            sk_set_pwm_frequency(bcmPin, frequency);
        }
#else
        cout << "Unable to set pwm frequency - GPIO not supported on this platform" << endl;
#endif
    }
    void raspi_set_pwm_dutycycle(pins pin, int dutycycle)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin == -1)
        {
            cout << "Cant modify a HIGH Pin" << endl;
        }
        else if (bcmPin == -2)
        {
            cout << "Cant modify a Ground pin" << endl;
        }
        else
        {
            sk_set_pwm_dutycycle(bcmPin, dutycycle);
        }
#else
        cout << "Unable to set pwm dutycycle - GPIO not supported on this platform" << endl;
#endif
    }
	
	int raspi_spi_open(int channel, int speed, int spi_flags)
    {
#ifdef RASPBERRY_PI
        int handle = -1;
	    handle = sk_spi_open(channel, speed, spi_flags);
        return handle;
#else
        cout << "Unable to open SPI interface - GPIO not supported on this platform" << endl;
        return -1;
#endif
    }

    int raspi_spi_close(int handle)
    {
#ifdef RASPBERRY_PI
        return sk_spi_close(handle);
#else
        cout << "Unable to close SPI interface - GPIO not supported on this platform" << endl;
        return -1;
#endif
    }

    int raspi_spi_transfer(int handle, string sendBuf, string recvBuf, int count)
    {
#ifdef RASPBERRY_PI
        return sk_spi_transfer(handle, sendBuf, recvBuf, count);
#else
        cout << "Unable to transfer through SPI - GPIO not supported on this platform" << endl;
        return -1;
#endif
    }

    // Cleanup GPIO resources
    void raspi_cleanup()
    {
#ifdef RASPBERRY_PI
        cout << "Cleaning GPIO pins" << endl;
        sk_clear_gpio_bank();
        sk_gpio_cleanup();
#else
        cout << "Unable to set cleanup - GPIO not supported on this platform" << endl;
#endif
    }
}
