//
//  test_raspi_spi.cpp
//  splashkit
//
//  Created by Jonathan Tynan https://github.com/Liquidscroll
//

#include <iostream>
#include "raspi_gpio.h"

using namespace std;
using namespace splashkit_lib;


void run_gpio_spi_tests()
{
    cout << "Initializing GPIO" << endl;
    raspi_init();

    cout << "Attempting to open SPI..." << endl;
    int handle = raspi_spi_open(0, 1000000, 0);
    if(handle >= 0)
    {
        cout << "SPI Connection Opened" << endl;
    }
    else
    {
        cout << "SPI failed to open." << endl;
        return;
    }

    char buffer[3];

    cout << "Attempting transfer..." << endl;
    int bytes_trans = raspi_spi_transfer(handle, buffer, buffer, 3);
    if(bytes_trans != 3)
    {
        cout << "Transfer error, wrong number of bytes transferred." << endl;     
    }

    cout << "Attempting to close SPI..." << endl;
    int close_result = raspi_spi_close(handle);
    if(close_result < 0)
    {
        cout << "SPI failed to close." << endl;
    }
    else
    {
        cout << "SPI closed successfully" << endl;
    }

    // Clean up the GPIO
    raspi_cleanup();
}