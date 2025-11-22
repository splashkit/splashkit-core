//
//  test_raspi_i2c_led_quad_14segment.cpp
//  splashkit
//
//  Created by Olivia McKeon https://github.com/omckeon
//

#include <iostream>
#include "raspi_gpio.h"

#include "basics.h"
#include "utils.h"

using namespace std;
using namespace splashkit_lib;

/** ===== QUAD 7-segment ===== **/

void run_gpio_i2c_quad_14_seg_test()
{
    raspi_init();

    cout << "Testing Quad 14-segment alphanumeric display with HT16K33 I2C driver...\n";

    int i2c_device = raspi_i2c_open(1, 0x70);
    raspi_i2c_write(i2c_device, 0b00100001); // Turn on system oscillator
    raspi_i2c_write(i2c_device, 0b10000001); // no blink, display on
    raspi_i2c_write(i2c_device, 0b11100011); // lower brightness

    // clear display
    for (uint8_t i = 0; i < 16; i++)
    {
        raspi_i2c_write(i2c_device, i, 0, 2);
    }

    string message = "HELLO WORLD FROM SPLASHKIT!";
    string text = "    " + message + "    ";

    cout << "Starting text scrolling...\n";
    delay(500);

    for (int i = 0; i < text.length() - 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            raspi_i2c_write(i2c_device, j * 2, get_alpha_font_14_seg(text[i + j]), 2);
        }
        delay(200);
    }

    // Turn off LED device
    raspi_i2c_write(i2c_device, 0b00100000); // Turn off system oscillator

    // Clean up the GPIO
    raspi_cleanup();
}