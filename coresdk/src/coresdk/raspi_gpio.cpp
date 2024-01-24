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

    // Initialize GPIO resources
    void raspi_init()
    {
        sk_gpio_init();
    }

    // Set the mode of the given pin
    void raspi_set_mode(pins pin, pin_modes mode)
    {
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
    }
    pin_modes raspi_get_mode(pins pin)
    {
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
        return GPIO_INPUT;
    }

    // Write a value to the given pin
    void raspi_write(pins pin, pin_values value)
    {
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
    }

    // Read the value of the given pin
    pin_values raspi_read(pins pin)
    {
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
    }
    void raspi_set_pull_up_down(pins pin, pull_up_down pud)
    {
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
    }
    void raspi_set_pwm_range(pins pin, int range)
    {
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
    }
    void raspi_set_pwm_frequency(pins pin, int frequency)
    {
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
    }
    void raspi_set_pwm_dutycycle(pins pin, int dutycycle)
    {
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
    }

    // Cleanup GPIO resources
    void raspi_cleanup()
    {
        cout << "Cleaning GPIO pins" << endl;
        for (int i = 1; i <= 40; i++)
        {
            int bcmPin = boardToBCM(static_cast<pins>(i));
            if (bcmPin > 0)
            {
                raspi_set_mode(static_cast<pins>(bcmPin), GPIO_INPUT);
                raspi_write(static_cast<pins>(bcmPin), GPIO_LOW);
            }
        }
        sk_gpio_cleanup();
    }
}
