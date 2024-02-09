/***********************************************
* XQuestCode || Aditya Parmar
* Code with Creativity 
* 🚀 © 2024 Aditya Parmar. All Rights Reserved.
***********************************************/
#include <iostream>
#include "raspi_gpio.h"
using namespace std;
using namespace splashkit_lib;

// Function to run GPIO tests
void run_gpio_tests()
{
    // Initialize the GPIO
    cout << "Initializing GPIO" << endl;
    raspi_init();

    // Set GPIO pin 11 as an output
    cout << "Setting GPIO pin 11 as an output" << endl;
    raspi_set_mode(PIN_11, GPIO_OUTPUT);

    // Read the initial value of GPIO pin 11
    int defaultValue = raspi_read(PIN_11);
    cout << "Value of Pin 11: " << defaultValue << endl;

    // Write HIGH to GPIO pin 11
    cout << "Writing HIGH to GPIO pin 11" << endl;
    raspi_write(PIN_11, GPIO_HIGH);

    // Read the value of GPIO pin 11
    int value = raspi_read(PIN_11);
    cout << "GPIO 11 value: " << value << endl;

    // Write HIGH to GPIO pin 17
    cout << "Writing HIGH to GPIO pin 17" << endl;
    raspi_write(PIN_17, GPIO_HIGH);

    // Write HIGH to Ground PIN
    cout << "Writing HIGH to Ground PIN" << endl;
    raspi_write(PIN_6, GPIO_HIGH);

    // Clean up the GPIO
    raspi_cleanup();
}