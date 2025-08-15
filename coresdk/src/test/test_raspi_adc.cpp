//
//  test_raspi_adc.cpp
//  splashkit
//

#include <iostream>
#include "raspi_gpio.h"
#include "input.h"
#include "utils.h"
#include "input_driver.h"

using namespace std;
using namespace splashkit_lib;

void run_gpio_adc_tests()
{
    const int NUMBER_OF_ADC_DEVICES = 2; // Update this if more devices are added

    cout << endl;
    cout << "ADC Test:" << endl;
    cout << endl;
    cout << "Note: The following ADC test require a button to wired to pin 11 to allow the analog pin to be changed (quick press), and to allow the test to be stopped cleanly (long press)." << endl;
    cout << endl;

    int adc_device_input = 0;
    while (adc_device_input < 1 || adc_device_input > NUMBER_OF_ADC_DEVICES)
    {
        cout << "ADC devices available:" << endl;
        cout << "1: ADS7830" << endl;
        cout << "2: PCF8591" << endl;
        cout << "------------------------" << endl;
        cout << "Select ADC device to test: ";
        cin >> adc_device_input;
        cin.ignore();
    }
    adc_type type = (adc_type)(adc_device_input - 1);

    // Initialise GPIO & I2C
    raspi_init();

    // Set up button for ending the program
    gpio_pin end_button_pin = PIN_11;
    raspi_set_mode(end_button_pin, GPIO_INPUT);
    raspi_set_pull_up_down(end_button_pin, PUD_DOWN);

    adc_device dev = open_adc("ADC1", 1, 0x48, type);
    if (dev == nullptr)
    {
        cout << "Failed to open ADC device." << endl;
        return;
    }

    // Press and hold button to quit
    while (raspi_read(end_button_pin) != GPIO_HIGH)
    {
        int adc_channel_input = -1;
        int max_channels = 0;
        switch (type)
        {
        case ADS7830:
            max_channels = 7;
            break;
        case PCF8591:
            max_channels = 4;
            break;
        default:
            break;
        }
        while (adc_channel_input < 0 || adc_channel_input > max_channels)
        {
            cout << "ADC analog input channels:" << endl;
            cout << "0: Analog channel 0" << endl;
            cout << "1: Analog channel 1" << endl;
            cout << "2: Analog channel 2" << endl;
            cout << "3: Analog channel 3" << endl;
            if (type == ADS7830)
            {
                cout << "4: Analog channel 4" << endl;
                cout << "5: Analog channel 5" << endl;
                cout << "6: Analog channel 6" << endl;
                cout << "7: Analog channel 7" << endl;
            }
            cout << "------------------------" << endl;
            cout << "Select Analog channel to use: ";
            cin >> adc_channel_input;
            cin.ignore();
        }
        adc_pin channel = (adc_pin)adc_channel_input;

        int value = 0;

        // Press button once briefly to change analog pin
        while (raspi_read(end_button_pin) != GPIO_HIGH)
        {
            value = read_adc(dev, channel);

            cout << "\033[2J\033[1;1H";
            cout << "Note:" << endl;
            cout << "- Press button to select another analog channel." << endl;
            cout << "- Press and hold button to end test." << endl;
            cout << endl;
            switch (type)
            {
            case ADS7830:
                cout << "ADC device: ADS7830" << endl;
                break;
            case PCF8591:
                cout << "ADC device: PCF8591" << endl;
                break;
            }
            cout << "Testing ADC channel: " << channel << endl;
            cout << endl;
            cout << "ADC value: " << value << endl;
        }
        if (raspi_read(end_button_pin) == GPIO_HIGH)
        {
            delay(500);
            cout << "\033[2J\033[1;1H";
        }
    }

    // Clean up
    close_adc(dev);
    raspi_cleanup();
    cout << "ADC test complete." << endl;
}