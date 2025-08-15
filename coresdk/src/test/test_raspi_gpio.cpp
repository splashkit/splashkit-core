// created by XQuestCode || Aditya Parmar
#include <iostream>
#include "networking.h"
#include "raspi_gpio.h"
using namespace std;
using namespace splashkit_lib;

// Function to run GPIO tests

void local_gpio_valid_tests()
{
    cout << "\n-- Testing valid GPIO calls --\n" << endl;
     
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
}

void local_gpio_invalid_tests()
{
    cout << "\n-- Testing invalid GPIO calls --\n" << endl;

    // --- ERROR TEST: Invalid GPIO pin number ---
    cout << "Testing invalid GPIO pin number (PIN_60)" << endl;
    raspi_set_mode(static_cast<gpio_pin>(60), GPIO_OUTPUT);  

    // --- ERROR TEST: Invalid GPIO pin number (EEPROM pin) ---
    cout << "Testing invalid GPIO pin number (EEPROM pin)" << endl;
    raspi_set_mode(PIN_27, GPIO_OUTPUT); 
    
    // --- ERROR TEST: Invalid GPIO pin number (POWER line) ---
    cout << "Testing invalid GPIO pin number (PIN_17, POWER line)" << endl;
    raspi_set_mode(PIN_17, GPIO_OUTPUT);  

    // --- ERROR TEST: Invalid GPIO pin number (GROUND line) ---
    cout << "Testing invalid GPIO pin number (PIN_6, GROUND line)" << endl;
    raspi_set_mode(PIN_6, GPIO_OUTPUT);  

    // --- ERROR TEST: Invalid GPIO mode ---
    cout << "Testing invalid GPIO mode (mode 10)" << endl;
    raspi_set_mode(PIN_11, static_cast<gpio_pin_mode>(10));  

    // --- ERROR TEST: Invalid GPIO write value ---
    cout << "Testing invalid GPIO value (writing 5)" << endl;
    raspi_write(PIN_11, static_cast<gpio_pin_value>(5));  

    // --- ERROR TEST: Invalid pull-up/down configuration ---
    cout << "Testing invalid pull-up/down configuration (PUD value 3)" << endl;
    raspi_set_pull_up_down(PIN_11, static_cast<pull_up_down>(3));  
    
    // --- ERROR TEST: Invalid PWM Duty Cycle
    cout << "Testing invalid PWM duty cycle configuration (Duty Cycle value 300)" << endl;
    raspi_set_pwm_dutycycle(PIN_11, 300);

    // --- ERROR TEST: Invalid PWM Range
    cout << "Testing invalid PWM range configuration (Range value 40001)" << endl;
    raspi_set_pwm_range(PIN_11, 40001);
}

void remote_gpio_valid_tests(connection pi)
{
    cout << "\n-- Testing valid GPIO calls --\n" << endl;
    // Set GPIO pin 11 as an output
    cout << "Setting GPIO pin 11 as an output" << endl;
    remote_raspi_set_mode(pi, PIN_11, GPIO_OUTPUT);

    // Read the initial value of GPIO pin 11
    int defaultValue = remote_raspi_read(pi, PIN_11);
    cout << "Value of Pin 11: " << defaultValue << endl;
    
    // Write HIGH to GPIO pin 11
    cout << "Writing HIGH to GPIO pin 11" << endl;
    remote_raspi_write(pi, PIN_11, GPIO_HIGH);

    // Read the value of GPIO pin 11
    int value = remote_raspi_read(pi, PIN_11);
    cout << "GPIO 11 value: " << value << endl;
}
void remote_gpio_invalid_tests(connection pi)
{
    cout << "\n-- Testing invalid GPIO calls --\n" << endl;

    // --- ERROR TEST: Invalid GPIO pin number ---
    cout << "Testing invalid GPIO pin number (PIN_60)" << endl;
    remote_raspi_set_mode(pi, static_cast<gpio_pin>(60), GPIO_OUTPUT); 

    // --- ERROR TEST: Invalid GPIO pin number (EEPROM pin) ---
    cout << "Testing invalid GPIO pin number (EEPROM pin)" << endl;
    remote_raspi_set_mode(pi, PIN_27, GPIO_OUTPUT); 
     
    // --- ERROR TEST: Invalid GPIO pin number (POWER line) ---
    cout << "Testing invalid GPIO pin number (PIN_17, POWER line)" << endl;
    remote_raspi_set_mode(pi, PIN_17, GPIO_OUTPUT); 
    
    // --- ERROR TEST: Invalid GPIO pin number (GROUND line) ---
    cout << "Testing invalid GPIO pin number (PIN_6, GROUND line)" << endl;
    remote_raspi_set_mode(pi, PIN_6, GPIO_OUTPUT); 
    
    // --- ERROR TEST: Invalid GPIO mode ---
    cout << "Testing invalid GPIO mode (mode 10)" << endl;
    remote_raspi_set_mode(pi, PIN_11, static_cast<gpio_pin_mode>(10));  

    // --- ERROR TEST: Invalid GPIO write value ---
    cout << "Testing invalid GPIO value (writing 5)" << endl;
    remote_raspi_write(pi, PIN_11, static_cast<gpio_pin_value>(5));  

    // --- ERROR TEST: Invalid pull-up/down configuration ---
    cout << "Testing invalid pull-up/down configuration (PUD value 3)" << endl;
    remote_raspi_set_pull_up_down(pi, PIN_11, static_cast<pull_up_down>(3));  

    // --- ERROR TEST: Invalid PWM Duty Cycle
    cout << "Testing invalid PWM duty cycle configuration (Duty Cycle value 300)" << endl;
    remote_raspi_set_pwm_dutycycle(pi, PIN_11, 300);

    // --- ERROR TEST: Invalid PWM Range
    cout << "Testing invalid PWM range configuration (Range value 40001)" << endl;
    remote_raspi_set_pwm_range(pi, PIN_11, 40001);
}
void run_gpio_tests() 
{
    raspi_init();
    local_gpio_valid_tests();
    local_gpio_invalid_tests();
    raspi_cleanup();
}
void run_remote_gpio_tests()
{

    cout << "This test requires a remote Raspberry Pi running the Pigpio Daemon\n";
    cout << "Enter IP Address of remote Pi:\n";

    std::string host;
    std::getline(std::cin, host);

    cout << "Initializing GPIO" << endl;
    connection pi = remote_raspi_init("Raspi", host, 8888);

    remote_gpio_valid_tests(pi);
    remote_gpio_invalid_tests(pi);

    remote_raspi_cleanup(pi);
}
