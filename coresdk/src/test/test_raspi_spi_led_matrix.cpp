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

#define SPI_CHANNEL 0     // Define SPI channel (0 or 1)
#define SPI_SPEED 1000000 // SPI speed set to 1 MHz

// Write data to a MAX7219 register
void max7219_write(unsigned char address, unsigned char data)
{
    int bytes_trans = 0;
    unsigned char buffer[2];
    buffer[0] = address; // Register address to write to
    buffer[1] = data;    // Data to write into the register
    // wiringPiSPIDataRW(SPI_CHANNEL, buffer, 2); // Send data via SPI
    string buffer_str(reinterpret_cast<char *>(buffer), 2); // Specify length
    raspi_spi_transfer(SPI_CHANNEL, buffer_str, 2, bytes_trans);
}

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

void run_pattern_max7219_led_matrix_test()
{
    cout << "Testing SPI transfer by displaying pattern to \"MAX7219\" LED matrix:\n"
         << endl;

    // Set up button on pin 11 to end program
    raspi_set_mode(PIN_11, GPIO_INPUT);
    raspi_set_pull_up_down(PIN_11, PUD_UP);

    int handle = raspi_spi_open(SPI_CHANNEL, SPI_SPEED, 0);

    // Initialising MAX7219
    max7219_write(0x09, 0x00); // Decode Mode: No decoding for digits (useful for 7-segment displays)
    max7219_write(0x0A, 0x03); // Intensity: Set brightness level (0x00 to 0x0F)
    max7219_write(0x0B, 0x07); // Scan Limit: Display digits 0-7 (all 8 digits)
    max7219_write(0x0C, 0x01); // Shutdown Register: Normal operation (not in shutdown mode)
    max7219_write(0x0F, 0x00); // Display Test: Normal operation (no test mode)

    // Clear all digits on the display
    for (int i = 1; i <= 8; i++)
    {
        max7219_write(i, 0x00); // Write 0 to each digit register
    }

    cout << "Attempting to display patterns on 8x8 LED matrix ..." << endl;

    for (int i = 0; i < 12; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            // Display patterns
            max7219_write(j, patterns[i][j - 1]);
        }
        delay(1000);
    }
    
    max7219_write(0x0C, 0x00); // Shutdown Register: Normal operation (not in shutdown mode)
    raspi_spi_close(handle);
}

// Display a dot on the LED matrix using the passed in x and y values (1 to 8)
void display_led_board(int x, int y)
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

    for (int i = 0; i < 8; i++)
    {
        max7219_write(i + 1, board[i]);
    }
}

void run_joystick_max7219_led_matrix_test()
{
    cout << "Testing Joystick (with ADC) to move \"dot\" on \"MAX7219\" SPI LED matrix...\n\n";
    cout << "MAX7219 LED matrix connections:\n";
    cout << "  DIN pin connected to GPIO pin 19 (GPIO10/MOSI)\n";
    cout << "  CS pin connected to GPIO pin 24 (GPIO8/CE0)\n";
    cout << "  CLK pin connected to GPIO pin 23 (GPIO11/SCLK)\n";
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

    // Set up SPI
    int handle = raspi_spi_open(SPI_CHANNEL, SPI_SPEED, 0);

    // Initialising MAX7219
    max7219_write(0x09, 0x00); // Decode Mode: No decoding for digits (useful for 7-segment displays)
    max7219_write(0x0A, 0x03); // Intensity: Set brightness level (0x00 to 0x0F)
    max7219_write(0x0B, 0x07); // Scan Limit: Display digits 0-7 (all 8 digits)
    max7219_write(0x0C, 0x01); // Shutdown Register: Normal operation (not in shutdown mode)
    max7219_write(0x0F, 0x00); // Display Test: Normal operation (no test mode)

    // Clear all digits on the display
    for (int i = 1; i <= 8; i++)
    {
        max7219_write(i, 0x00); // Write 0 to each digit register
    }

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

        display_led_board((int)x, (int)y);

        // Debugging
        // dx = read_adc(dev, x_channel);
        // dy = read_adc(dev, y_channel);
        // cout << "x,y = " << dx << "," << dy << endl;
    }

    max7219_write(0x0C, 0x00); // Shutdown Register: Normal operation (not in shutdown mode)
    close_adc(dev);
    raspi_spi_close(handle);
}

void run_gpio_spi_led_matrix_tests()
{
    raspi_init();

    run_pattern_max7219_led_matrix_test();
    // run_joystick_max7219_led_matrix_test();

    // Clean up the GPIO
    raspi_cleanup();
}