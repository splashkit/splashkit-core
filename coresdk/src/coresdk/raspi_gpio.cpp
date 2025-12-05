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

    int raspi_spi_open(int channel, int speed, int spi_flags)
    {
#ifdef RASPBERRY_PI
        int handle = -1;
        handle = sk_spi_open(channel, speed, spi_flags);
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
        int len = send.size() > count ? count : send.size();
        char send_buf[len + 1]{};
        for (int i = 0; i < len; i++)
        {
            send_buf[i] = send[i];
        }

        char recv_buf[len + 1]{};

        bytes_transfered = sk_spi_transfer(handle, send_buf, recv_buf, len);

        string response(recv_buf);
        return response;
#else
        LOG(ERROR) << "Unable to transfer through SPI - GPIO not supported on this platform";
        return "";
#endif
    }

    int raspi_i2c_open(int bus, int address)
    {
#ifdef RASPBERRY_PI
        int handle = -1;
        handle = sk_i2c_open(bus, address);
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

    unsigned short get_alpha_font_14_seg(char ascii_char)
    {
        /* Segment names for 14-segment alphanumeric displays.

        See https://learn.adafruit.com/14-segment-alpha-numeric-led-featherwing/usage

        -------A-------
        |\     |     /|
        | \    J    / |
        |   H  |  K   |
        F    \ | /    B
        |     \|/     |
        |--G1--|--G2--|
        |     /|\     |
        E    / | \    C
        |   L  |   N  |
        | /    M    \ |
        |/     |     \|
        -------D-------  DP

        0b0  0   0  0  0  0  0  0  0   0   0  0  0  0  0  0,
        0b0  1   1  1  1  1  1  1  1   1   1  1  1  1  1  1,
             ↑   ↑  ↑  ↑  ↑  ↑  ↑  ↑   ↑   ↑  ↑  ↑  ↑  ↑  ↑
        0b0  DP  N  M  L  K  J  H  G2  G1  F  E  D  C  B  A,

        // #define ALPHANUM_SEG_A 0b0000000000000001  ///< Alphanumeric segment A
        // #define ALPHANUM_SEG_B 0b0000000000000010  ///< Alphanumeric segment B
        // #define ALPHANUM_SEG_C 0b0000000000000100  ///< Alphanumeric segment C
        // #define ALPHANUM_SEG_D 0b0000000000001000  ///< Alphanumeric segment D
        // #define ALPHANUM_SEG_E 0b0000000000010000  ///< Alphanumeric segment E
        // #define ALPHANUM_SEG_F 0b0000000000100000  ///< Alphanumeric segment F
        // #define ALPHANUM_SEG_G1 0b0000000001000000 ///< Alphanumeric segment G1
        // #define ALPHANUM_SEG_G2 0b0000000010000000 ///< Alphanumeric segment G2
        // #define ALPHANUM_SEG_H 0b0000000100000000  ///< Alphanumeric segment H
        // #define ALPHANUM_SEG_J 0b0000001000000000  ///< Alphanumeric segment J
        // #define ALPHANUM_SEG_K 0b0000010000000000  ///< Alphanumeric segment K
        // #define ALPHANUM_SEG_L 0b0000100000000000  ///< Alphanumeric segment L
        // #define ALPHANUM_SEG_M 0b0001000000000000  ///< Alphanumeric segment M
        // #define ALPHANUM_SEG_N 0b0010000000000000  ///< Alphanumeric segment N
        // #define ALPHANUM_SEG_DP 0b0100000000000000 ///< Alphanumeric segment DP

        */

        const unsigned short alpha_font_table[] = {
            0b0000000000000001,
            0b0000000000000010,
            0b0000000000000100,
            0b0000000000001000,
            0b0000000000010000,
            0b0000000000100000,
            0b0000000001000000,
            0b0000000010000000,
            0b0000000100000000,
            0b0000001000000000,
            0b0000010000000000,
            0b0000100000000000,
            0b0001000000000000,
            0b0010000000000000,
            0b0100000000000000,
            0b1000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0000000000000000,
            0b0001001011001001,
            0b0001010111000000,
            0b0001001011111001,
            0b0000000011100011,
            0b0000010100110000,
            0b0001001011001000,
            0b0011101000000000,
            0b0001011100000000,
            0b0000000000000000, //
            0b0100000000000010, // !
            0b0000001000100000, // "
            0b0001001011001110, // #
            0b0001001011101101, // $
            0b0000110000100100, // %
            0b0010001101011101, // &
            0b0000010000000000, // '
            0b0010010000000000, // (
            0b0000100100000000, // )
            0b0011111111000000, // *
            0b0001001011000000, // +
            0b0000100000000000, // ,
            0b0000000011000000, // -
            0b0100000000000000, // .
            0b0000110000000000, // /
            0b0000110000111111, // 0
            0b0000000000000110, // 1
            0b0000000011011011, // 2
            0b0000000010001111, // 3
            0b0000000011100110, // 4
            0b0010000001101001, // 5
            0b0000000011111101, // 6
            0b0000000000000111, // 7
            0b0000000011111111, // 8
            0b0000000011101111, // 9
            0b0001001000000000, // :
            0b0000101000000000, // ;
            0b0010010000000000, // <
            0b0000000011001000, // =
            0b0000100100000000, // >
            0b0001000010000011, // ?
            0b0000001010111011, // @
            0b0000000011110111, // A
            0b0001001010001111, // B
            0b0000000000111001, // C
            0b0001001000001111, // D
            0b0000000011111001, // E
            0b0000000001110001, // F
            0b0000000010111101, // G
            0b0000000011110110, // H
            0b0001001000001001, // I
            0b0000000000011110, // J
            0b0010010001110000, // K
            0b0000000000111000, // L
            0b0000010100110110, // M
            0b0010000100110110, // N
            0b0000000000111111, // O
            0b0000000011110011, // P
            0b0010000000111111, // Q
            0b0010000011110011, // R
            0b0000000011101101, // S
            0b0001001000000001, // T
            0b0000000000111110, // U
            0b0000110000110000, // V
            0b0010100000110110, // W
            0b0010110100000000, // X
            0b0001010100000000, // Y
            0b0000110000001001, // Z
            0b0000000000111001, // [
            0b0010000100000000, //
            0b0000000000001111, // ]
            0b0000110000000011, // ^
            0b0000000000001000, // _
            0b0000000100000000, // `
            0b0001000001011000, // a
            0b0010000001111000, // b
            0b0000000011011000, // c
            0b0000100010001110, // d
            0b0000100001011000, // e
            0b0000000001110001, // f
            0b0000010010001110, // g
            0b0001000001110000, // h
            0b0001000000000000, // i
            0b0000000000001110, // j
            0b0011011000000000, // k
            0b0000000000110000, // l
            0b0001000011010100, // m
            0b0001000001010000, // n
            0b0000000011011100, // o
            0b0000000101110000, // p
            0b0000010010000110, // q
            0b0000000001010000, // r
            0b0010000010001000, // s
            0b0000000001111000, // t
            0b0000000000011100, // u
            0b0010000000000100, // v
            0b0010100000010100, // w
            0b0010100011000000, // x
            0b0010000000001100, // y
            0b0000100001001000, // z
            0b0000100101001001, // {
            0b0001001000000000, // |
            0b0010010010001001, // }
            0b0000010100100000, // ~
            0b0011111111111111,
        };

        return alpha_font_table[ascii_char];
    }

    int raspi_get_servo_pulsewidth(gpio_pin pin)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            return sk_get_servo_pulsewidth(bcmPin);
        }
        else
        {
            LOG(ERROR) << "Pin " << pin << " is not a PWM pin";
            return -1;
        }
#else
        LOG(ERROR) << "Servo driver not supported on this platform";
        return -1;
#endif
    }
    
    void raspi_set_servo_pulsewidth(gpio_pin pin, int pulsewidth)
    {
#ifdef RASPBERRY_PI
        int bcmPin = boardToBCM(pin);
        if (bcmPin >= 2)
        {
            sk_set_servo_pulsewidth(bcmPin, pulsewidth);
        }
#else
        LOG(ERROR) << "Servo driver not supported on this platform";
#endif
    }

    // Cleanup GPIO resources
    void raspi_cleanup()
    {
#ifdef RASPBERRY_PI
        LOG(INFO) << "Cleaning GPIO pins";
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
