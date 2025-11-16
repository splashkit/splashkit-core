//
//  raspi_gpio.cpp
//  splashkit
//
// Created by Aditya Parmar on 20/01/2024.
// Copyright © 2024 XQuestCode. All rights reserved.
//

#include "raspi_gpio.h"
#include "gpio_driver.h"
#include "raspi_adc.h"
#include "easylogging++.h"
#include "types.h"
#include "backend_types.h"
#include <iostream>
using namespace std;

namespace splashkit_lib
{
    // Each index points to PIN_1, PIN_2, PIN_3, etc.
    int BCMpinData[] = {
        -1, -1, 2, -1, 3, -2, 4, 14, -2, 15, 17, 18, 27, -2, 22, 23, -1, 24, 10, -2, 9, 25, 11, 8, -2, 7, 0, 1, 5, -2, 6, 12, 13, -2, 19, 16, 26, 20, -2, 21};

    int boardToBCM(gpio_pin pin)
    {
        int bcmPinResult = -1;
        if (pin >= PIN_1 && pin <= PIN_40)
        {
            bcmPinResult = BCMpinData[static_cast<int>(pin) - static_cast<int>(PIN_1)];
        }

        // Pins 0 and 1 are EEPROM pins and should not be written to
        // See Page 9. of Raspberry Pi 4B Datasheet:
        // https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf
        // Archive Link:
        // https://web.archive.org/web/20240901170108/https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf
        if (bcmPinResult < 2)
        {
            string extra_text = " Pin is a";
            extra_text += (bcmPinResult >= 0) ? "n EEPROM Pin, using this could corrupt the bootloader." : (bcmPinResult == -1) ? " POWER line."
                                                                                                       : (bcmPinResult == -2)   ? " GROUND line."
                                                                                                                                : "n Unknown Pin Type.";
            LOG(ERROR) << sk_gpio_error_message(PI_BAD_GPIO) + extra_text;
            return PI_BAD_GPIO;
        }
        else
        {
            return bcmPinResult;
        }
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
        LOG(ERROR) << "GPIO not supported on this platform";
#endif
    }

    // Set the mode of the given pin
    void raspi_set_mode(gpio_pin pin, gpio_pin_mode mode)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_gpio_set_mode(bcmPin, static_cast<int>(mode));
        }
#else
        LOG(ERROR) << "Unable to set mode - GPIO not supported on this platform";
#endif
    }

    gpio_pin raspi_get_pin(int boardPin)
    {
        gpio_pin pin = PIN_1;
        if (boardPin >= 1 && boardPin <= 40)
        {
            pin = static_cast<gpio_pin>(boardPin);
        }
        return pin;
    }
    // set pin to input
    void raspi_set_input(gpio_pin pin)
    {
        raspi_set_mode(pin, GPIO_INPUT);
    }
    // set pin to output
    void raspi_set_output(gpio_pin pin)
    {
        raspi_set_mode(pin, GPIO_OUTPUT);
    }

    gpio_pin_mode raspi_get_mode(gpio_pin pin)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            return static_cast<gpio_pin_mode>(sk_gpio_get_mode(bcmPin));
        }
        return GPIO_DEFAULT_MODE;
#else
        LOG(ERROR) << "Unable to get mode - GPIO not supported on this platform";
        return GPIO_DEFAULT_MODE;
#endif
    }

    // Write a value to the given pin
    void raspi_write(gpio_pin pin, gpio_pin_value value)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_gpio_write(bcmPin, static_cast<int>(value));
        }
#else
        LOG(ERROR) << "Unable to write pin - GPIO not supported on this platform";
#endif
    }

    // Read the value of the given pin
    gpio_pin_value raspi_read(gpio_pin pin)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            return static_cast<gpio_pin_value>(sk_gpio_read(bcmPin));
        }
        return GPIO_DEFAULT_VALUE;
#else
        LOG(ERROR) << "Unable to read pin - GPIO not supported on this platform";
        return GPIO_DEFAULT_VALUE;
#endif
    }

    void raspi_set_pull_up_down(gpio_pin pin, pull_up_down pud)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_gpio_set_pull_up_down(bcmPin, static_cast<int>(pud));
        }
#else
        LOG(ERROR) << "Unable to set pull up/down - GPIO not supported on this platform";
#endif
    }

    void raspi_set_pwm_range(gpio_pin pin, int range)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_set_pwm_range(bcmPin, range);
        }
#else
        LOG(ERROR) << "Unable to set pwm range - GPIO not supported on this platform";
#endif
    }

    void raspi_set_pwm_frequency(gpio_pin pin, int frequency)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_set_pwm_frequency(bcmPin, frequency);
        }
#else
        LOG(ERROR) << "Unable to set pwm frequency - GPIO not supported on this platform";
#endif
    }

    void raspi_set_pwm_dutycycle(gpio_pin pin, int dutycycle)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_set_pwm_dutycycle(bcmPin, dutycycle);
        }
#else
        LOG(ERROR) << "Unable to set pwm dutycycle - GPIO not supported on this platform";
#endif
    }

    int raspi_spi_open(int channel, int speed)
    {
#ifdef RASPBERRY_PI
        int handle = -1;
        handle = sk_spi_open(channel, speed);
        return handle;
#else
        LOG(ERROR) << "Unable to open SPI interface - GPIO not supported on this platform";
        return -1;
#endif
    }

    int raspi_spi_close(int handle)
    {
#ifdef RASPBERRY_PI
        return sk_spi_close(handle);
#else
        LOG(ERROR) << "Unable to close SPI interface - GPIO not supported on this platform";
        return -1;
#endif
    }

    string raspi_spi_transfer(int handle, const string &send, int count, int &bytes_transfered)
    {
#ifdef RASPBERRY_PI
        // Get an array (vector) of characters from send to make buffer
        vector<char> buf(send.begin(), send.end());

        // The buf variable is the data within the buf vector
        bytes_transfered = sk_spi_transfer(handle, buf.data(), count);

        // The response is a combination of the data & size
        string response(buf.data(), buf.size());
        return response;
#else
        LOG(ERROR) << "Unable to transfer through SPI - GPIO not supported on this platform";
        return "";
#endif
    }

    int raspi_i2c_open(int address)
    {
#ifdef RASPBERRY_PI
        int handle = -1;
        handle = sk_i2c_open(address);
        return handle;
#else
        LOG(ERROR) << "Unable to open SPI interface - GPIO not supported on this platform";
        return -1;
#endif
    }

    void raspi_i2c_write(int handle, int data)
    {
#ifdef RASPBERRY_PI
        sk_i2c_write_byte(handle, data);
#else
        LOG(ERROR) << "Unable to write to I2C device - GPIO not supported on this platform";
#endif
    }

    void raspi_i2c_write(int handle, int reg, int data, int bytes)
    {
#ifdef RASPBERRY_PI
        switch (bytes)
        {
        case 1:
            sk_i2c_write_byte_data(handle, reg, data);
            break;
        case 2:
            sk_i2c_write_word_data(handle, reg, data);
            break;
        default:
            LOG(ERROR) << "Unable to write to I2C device - count must be 1 or 2.";
            break;
        }
#else
        LOG(ERROR) << "Unable to write to I2C device - GPIO not supported on this platform";
#endif
    }

//     int raspi_get_servo_pulsewidth(gpio_pin pin)
//     {
// #ifdef RASPBERRY_PI
//         if (has_gpio())
//         {
//             gpio_pin pwmPins[] = {PIN_12, PIN_32, PIN_33, PIN_35};
//             // if the pin is not a PWM pin, return
//             if (find(begin(pwmPins), end(pwmPins), pin) == end(pwmPins))
//             {
//                 LOG(ERROR) << "Pin " << pin << " is not a PWM pin";
//                 return -1;
//             }
//             int bcmPin = boardToBCM(pin);
//             // if the pin is not a PWM pin, return
//             if (bcmPin < 2)
//             {
//                 LOG(ERROR) << "Pin " << pin << " is not a PWM pin";
//                 return -1;
//             }
//             return sk_get_servo_pulsewidth(bcmPin);
//         }
//         else
//         {
//             LOG(ERROR) << "Servo driver not supported on this platform";
//             return -1;
//         }
// #else
//         LOG(ERROR) << "Servo driver not supported on this platform";
//         return -1;
// #endif
//     }
//     void raspi_set_servo_pulsewidth(gpio_pin pin, int pulsewidth)
//     {
// #ifdef RASPBERRY_PI
//         if (has_gpio())
//         {
//             gpio_pin pwmPins[] = {PIN_12, PIN_32, PIN_33, PIN_35};
//             // if the pin is not a PWM pin, return
//             if (find(begin(pwmPins), end(pwmPins), pin) == end(pwmPins))
//             {
//                 LOG(ERROR) << "Pin " << pin << " is not a PWM pin";
//                 return; // ← early return so we don’t drive an unsupported pin
//             }
//             int bcmPin = boardToBCM(pin);
//             sk_set_servo_pulsewidth(bcmPin, pulsewidth);
//         }
//         else
//         {
//             LOG(ERROR) << "Servo driver not supported on this platform";
//         }
// #else
//         LOG(ERROR) << "Servo driver not supported on this platform";
// #endif
//     }

    // Cleanup GPIO resources
    void raspi_cleanup()
    {
#ifdef RASPBERRY_PI
        LOG(INFO) << "Cleaning GPIO pins";
        // for (int i = 0; i < 40; i++)
        // {
        //     if (BCMpinData[i] > 2)
        //     {
        //         raspi_write(raspi_get_pin(i+1), GPIO_LOW);
        //     }
        // }
        sk_gpio_clear_bank_1();
        sk_gpio_cleanup();
#else
        LOG(ERROR) << "Unable to set cleanup - GPIO not supported on this platform";
#endif
    }

    connection remote_raspi_init(const string &name, const string &host, unsigned short int port)
    {
        return sk_remote_gpio_init(name, host, port);
    }

    void remote_raspi_set_mode(connection pi, gpio_pin pin, gpio_pin_mode mode)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            sk_remote_gpio_set_mode(pi, bcmPin, mode);
    }

    gpio_pin_mode remote_raspi_get_mode(connection pi, gpio_pin pin)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            return static_cast<gpio_pin_mode>(sk_remote_gpio_get_mode(pi, bcmPin));
        else
            return GPIO_DEFAULT_MODE;
    }

    void remote_raspi_set_pull_up_down(connection pi, gpio_pin pin, pull_up_down pud)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            sk_remote_gpio_set_pull_up_down(pi, bcmPin, pud);
    }

    void remote_raspi_write(connection pi, gpio_pin pin, gpio_pin_value value)
    {
        int bcmPin = boardToBCM(pin);

        if (bcmPin >= 2)
            sk_remote_gpio_write(pi, bcmPin, value);
    }

    gpio_pin_value remote_raspi_read(connection pi, gpio_pin pin)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            return static_cast<gpio_pin_value>(sk_remote_gpio_read(pi, bcmPin));
        else
            return GPIO_DEFAULT_VALUE;
    }

    void remote_raspi_set_pwm_range(connection pi, gpio_pin pin, int range)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            sk_remote_set_pwm_range(pi, bcmPin, range);
    }

    void remote_raspi_set_pwm_frequency(connection pi, gpio_pin pin, int frequency)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            sk_remote_set_pwm_frequency(pi, bcmPin, frequency);
    }

    void remote_raspi_set_pwm_dutycycle(connection pi, gpio_pin pin, int dutycycle)
    {
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
            sk_remote_set_pwm_dutycycle(pi, bcmPin, dutycycle);
    }

    bool remote_raspi_cleanup(connection pi)
    {
        return sk_remote_gpio_cleanup(pi);
    }

    int gpio_pin_to_int(gpio_pin_value value)
    {
        return static_cast<int>(value);
    }
}
