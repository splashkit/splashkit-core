//
//  test_raspi_spi_led_matrix.cpp
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

    int i2c_device = raspi_i2c_open(0, 0x70);

    ht16k33_init(i2c_device);

    for (int i = 0; i < 2; i++)
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

    int i2c_device = raspi_i2c_open(0, 0x70);

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

/** ===== QUAD 7-segment ===== **

    Segment names for 14-segment alphanumeric displays.

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
*/

// #define ALPHANUM_SEG_A 0b0000000000000001  ///< Alphanumeric segment A
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

const uint8_t sevensegfonttable[] = {
    0b00000000, // (space)
    0b10000110, // !
    0b00100010, // "
    0b01111110, // #
    0b01101101, // $
    0b11010010, // %
    0b01000110, // &
    0b00100000, // '
    0b00101001, // (
    0b00001011, // )
    0b00100001, // *
    0b01110000, // +
    0b00010000, // ,
    0b01000000, // -
    0b10000000, // .
    0b01010010, // /
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b00001001, // :
    0b00001101, // ;
    0b01100001, // <
    0b01001000, // =
    0b01000011, // >
    0b11010011, // ?
    0b01011111, // @
    0b01110111, // A
    0b01111100, // B
    0b00111001, // C
    0b01011110, // D
    0b01111001, // E
    0b01110001, // F
    0b00111101, // G
    0b01110110, // H
    0b00110000, // I
    0b00011110, // J
    0b01110101, // K
    0b00111000, // L
    0b00010101, // M
    0b00110111, // N
    0b00111111, // O
    0b01110011, // P
    0b01101011, // Q
    0b00110011, // R
    0b01101101, // S
    0b01111000, // T
    0b00111110, // U
    0b00111110, // V
    0b00101010, // W
    0b01110110, // X
    0b01101110, // Y
    0b01011011, // Z
    0b00111001, // [
    0b01100100, //
    0b00001111, // ]
    0b00100011, // ^
    0b00001000, // _
    0b00000010, // `
    0b01011111, // a
    0b01111100, // b
    0b01011000, // c
    0b01011110, // d
    0b01111011, // e
    0b01110001, // f
    0b01101111, // g
    0b01110100, // h
    0b00010000, // i
    0b00001100, // j
    0b01110101, // k
    0b00110000, // l
    0b00010100, // m
    0b01010100, // n
    0b01011100, // o
    0b01110011, // p
    0b01100111, // q
    0b01010000, // r
    0b01101101, // s
    0b01111000, // t
    0b00011100, // u
    0b00011100, // v
    0b00010100, // w
    0b01110110, // x
    0b01101110, // y
    0b01011011, // z
    0b01000110, // {
    0b00110000, // |
    0b01110000, // }
    0b00000001, // ~
    0b00000000, // del
};

const uint16_t alphafonttable[] = {
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
    0b0000000000000110, // !
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

void run_i2c_quad_14_seg_test()
{
    cout << "Testing Quad 14-segment alphanumeric display with HT16K33 I2C driver...\n";

    int i2c_device = raspi_i2c_open(0, 0x70);

    ht16k33_init(i2c_device);

    raspi_i2c_write(i2c_device, 0, alphafonttable[(int)'Y'], 2);
    delay(2000);

    // Turn off LED device
    raspi_i2c_write(i2c_device, 0b00100000); // Turn off system oscillator
}

void run_gpio_i2c_led_matrix_tests()
{
    raspi_init();

    // run_i2c_led_matrix_test();
    // run_joystick_i2c_led_matrix_test();
    // run_i2c_quad_14_seg_test();

    // Clean up the GPIO
    raspi_cleanup();
}