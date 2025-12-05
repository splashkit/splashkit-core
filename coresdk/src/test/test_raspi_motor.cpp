// created by XQuestCode || Aditya Parmar
#include <iostream>
#include "raspi_gpio.h"
#include "raspi_motor_driver.h"
#include "terminal.h"
#include "utils.h"

using namespace std;
using namespace splashkit_lib;

void run_motor_driver_tests()
{
    write_line("=== L298N Motor Driver Test ===");
    // Initialize the Raspberry Pi GPIO subsystem
    raspi_init();

    // Instructions for wiring
    write_line("Wire your L298N driver as follows:");
    write_line("  ENA -> Pin 33 (GPIO13/PWM1)");
    write_line("  IN1 -> Pin 31 (GPIO6)");
    write_line("  IN2 -> Pin 29 (GPIO5)");
    write_line("Press any key to begin...");
    read_line();

    // Open the motor device
    motor_device dev = open_motor("Motor1", L298N, PIN_31, PIN_29, PIN_33);
    if (dev == nullptr)
    {
        write_line("ERROR: Failed to open motor device.");
        raspi_cleanup();
        return;
    }

    // Run forward at 50% speed
    write_line("\nRunning motor FORWARD @ 50% speed. Press any key to reverse direction.");
    set_motor_direction(dev, MOTOR_FORWARD);
    // short burst to get motor "unstuck"
    set_motor_speed(dev, 1);
    delay(20);

    set_motor_speed(dev, 0.5);
    read_line();

    // Reverse at 50% speed
    write_line("\nReversing motor @ 50% speed. Press any key to brake (stop), clean up and exit.");
    set_motor_direction(dev, MOTOR_BACKWARD);
    // short burst to get motor "unstuck"
    set_motor_speed(dev, 1);
    delay(20);
    set_motor_speed(dev, 0.5);
    read_line();

    // Clean up
    stop_motor(dev); // Brake (both inputs HIGH)
    close_motor(dev);
    raspi_cleanup();

    write_line("\nMotor driver test completed.");
}
