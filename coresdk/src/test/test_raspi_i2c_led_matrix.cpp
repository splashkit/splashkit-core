//
//  test_raspi_i2c_led_matrix.cpp
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

/** ===== 8x8 LED matrix ===== **/

// Array of patterns to display
const unsigned char patterns[][8] = {
    // Square pattern
    {
        0b11111111, // Row 1
        0b10000001, // Row 2
        0b10000001, // Row 3
        0b10000001, // Row 4
        0b10000001, // Row 5
        0b10000001, // Row 6
        0b10000001, // Row 7
        0b11111111  // Row 8
    },
    // Heart pattern
    {
        0b01100110, // Row 1
        0b11111111, // Row 2
        0b11111111, // Row 3
        0b11111111, // Row 4
        0b01111110, // Row 5
        0b00111100, // Row 6
        0b00011000, // Row 7
        0b00000000  // Row 8
    },
    // Number 0
    {
        0b00111100, // Row 1
        0b01100110, // Row 2
        0b11000011, // Row 3
        0b11000011, // Row 4
        0b11000011, // Row 5
        0b11000011, // Row 6
        0b01100110, // Row 7
        0b00111100  // Row 8
    },
    // Number 1
    {
        0b00011000, // Row 1
        0b00111000, // Row 2
        0b01111000, // Row 3
        0b00011000, // Row 4
        0b00011000, // Row 5
        0b00011000, // Row 6
        0b01111110, // Row 7
        0b00000000  // Row 8
    },
    // Number 2
    {
        0b01111110, // Row 1
        0b11000011, // Row 2
        0b00000011, // Row 3
        0b00001110, // Row 4
        0b00110000, // Row 5
        0b11000000, // Row 6
        0b11111111, // Row 7
        0b00000000  // Row 8
    },
    // Number 3
    {
        0b01111110, // Row 1
        0b11000011, // Row 2
        0b00000011, // Row 3
        0b00111110, // Row 4
        0b00000011, // Row 5
        0b11000011, // Row 6
        0b01111110, // Row 7
        0b00000000  // Row 8
    },
    // Number 4
    {
        0b00001110, // Row 1
        0b00011110, // Row 2
        0b00110110, // Row 3
        0b01100110, // Row 4
        0b11111111, // Row 5
        0b00000110, // Row 6
        0b00000110, // Row 7
        0b00000000  // Row 8
    },
    // Number 5
    {
        0b11111111, // Row 1
        0b11000000, // Row 2
        0b11111110, // Row 3
        0b00000011, // Row 4
        0b00000011, // Row 5
        0b11000011, // Row 6
        0b01111110, // Row 7
        0b00000000  // Row 8
    },
    // Number 6
    {
        0b00111110, // Row 1
        0b01100000, // Row 2
        0b11000000, // Row 3
        0b11111110, // Row 4
        0b11000011, // Row 5
        0b11000011, // Row 6
        0b01111110, // Row 7
        0b00000000  // Row 8
    },
    // Number 7
    {
        0b11111111, // Row 1
        0b11000011, // Row 2
        0b00000110, // Row 3
        0b00001100, // Row 4
        0b00011000, // Row 5
        0b00110000, // Row 6
        0b00110000, // Row 7
        0b00000000  // Row 8
    },
    // Number 8
    {
        0b01111110, // Row 1
        0b11000011, // Row 2
        0b11000011, // Row 3
        0b01111110, // Row 4
        0b11000011, // Row 5
        0b11000011, // Row 6
        0b01111110, // Row 7
        0b00000000  // Row 8
    },
    // Number 9
    {
        0b01111110, // Row 1
        0b11000011, // Row 2
        0b11000011, // Row 3
        0b01111111, // Row 4
        0b00000011, // Row 5
        0b00000110, // Row 6
        0b01111100, // Row 7
        0b00000000  // Row 8
    },
};

unsigned char reverse(unsigned char b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void draw_pattern(int i2c_device, uint8_t pattern[8])
{
    unsigned char control_bits;

    for (uint8_t y = 0; y < 8; y++)
    {
        control_bits = reverse(pattern[y]);
        control_bits = (control_bits >> 1) | (control_bits << 7);
        raspi_i2c_write(i2c_device, y * 2, control_bits, 1);
    }
}

// Display a dot on the LED matrix using the passed in x and y values (1 to 8)
void display_led_board(int i2c_device, int x, int y)
{
    string binary_string[8] = {};
    unsigned char board[8] = {};

    for (int row = 0; row < 8; row++)
    {
        binary_string[row] = "";
        for (int col = 0; col < 8; col++)
        {
            if (x == col + 1 && y == row + 1)
            {
                binary_string[row] += "1";
            }
            else
            {
                binary_string[row] += "0";
            }
        }
        board[row] = bin_to_dec(binary_string[row]);
    }

    draw_pattern(i2c_device, board);
}

void ht16k33_init(int i2c_device)
{
    raspi_i2c_write(i2c_device, 0b00100001); // Turn on system oscillator
    raspi_i2c_write(i2c_device, 0b10000001); // no blink, display on
    // raspi_i2c_write(i2c_device, 0b11100011); // lower brightness

    // clear display
    for (uint8_t i = 0; i < 16; i++)
    {
        raspi_i2c_write(i2c_device, i, 0, 2);
    }
}

void run_i2c_led_matrix_test()
{
    cout << "Testing 8x8 LED matrix with HT16K33 I2C driver...\n";

    int i2c_device = raspi_i2c_open(1, 0x70);

    ht16k33_init(i2c_device);

    for (int i = 0; i < 12; i++)
    {
        draw_pattern(i2c_device, (uint8_t *)patterns[i]);
        delay(1000);
    }

    // Turn off LED device
    raspi_i2c_write(i2c_device, 0b00100000); // Turn off system oscillator
}

void run_joystick_i2c_led_matrix_test()
{
    cout << "Testing Joystick (with ADC) to move \"dot\" on \"HT16K33\" I2C LED matrix...\n\n";
    cout << "HT16K33 LED matrix connections:\n";
    cout << "  SDA pin connected to GPIO pin 3 (GPIO2/SDA)\n";
    cout << "  SCL pin connected to GPIO pin 5 (GPIO3/SCL)\n";
    cout << "Joystick connections:\n";
    cout << "  VRX pin connected to ADC pin 0 (channel 0)\n";
    cout << "  VRY pin connected to ADC pin 1 (channel 1)\n";
    cout << "  SW pin (joystick button) connected to GPIO pin 11 (GPIO17)\n";

    // Set up button on pin 11 to end program
    raspi_set_mode(PIN_11, GPIO_INPUT);
    raspi_set_pull_up_down(PIN_11, PUD_UP);

    // Set up ADC
    adc_device dev = open_adc("ADC1", 1, 0x48, ADS7830);
    adc_pin x_channel = ADC_PIN_0; // Change this to the desired channel
    adc_pin y_channel = ADC_PIN_1; // Change this to the desired channel

    int i2c_device = raspi_i2c_open(1, 0x70);

    ht16k33_init(i2c_device);

    float x = 1;
    float y = 1;
    float dx = 0;
    float dy = 0;
    float speed = 0.1;

    // Display single dot
    while (raspi_read(PIN_11) != GPIO_LOW)
    {
        // Direct mapping
        // x = ((read_adc(dev, x_channel) / 255.0) * 7) + 1;
        // y = ((read_adc(dev, y_channel) / 255.0) * 7) + 1;

        // Moves when joystick is moved
        dx = ((read_adc(dev, x_channel) - 127) / 255.0) * 7;
        dy = ((read_adc(dev, y_channel) - 127) / 255.0) * 7;
        if ((x < 8 && dx > 1) || (x >= 2 && dx < -1))
            x += dx * speed;
        if ((y < 8 && dy > 1) || (y >= 2 && dy < -1))
            y += dy * speed;

        display_led_board(i2c_device, (int)x, (int)y);

        // Debugging
        // dx = read_adc(dev, x_channel);
        // dy = read_adc(dev, y_channel);
        // cout << "x,y = " << dx << "," << dy << endl;
    }

    // Turn off LED device
    raspi_i2c_write(i2c_device, 0b00100000); // Turn off system oscillator

    close_adc(dev);
}

void run_gpio_i2c_led_matrix_tests()
{
    raspi_init();

    run_i2c_led_matrix_test();
    // run_joystick_i2c_led_matrix_test();

    // Clean up the GPIO
    raspi_cleanup();
}