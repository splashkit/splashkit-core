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
    write_line("  IN1 -> GPIO24");
    write_line("  IN2 -> GPIO23");
    write_line("  ENA -> GPIO25 (PWM)");
    write_line("Press any key to begin...");
    read_line();

    // Open the motor device
    motor_device dev = open_motor("Motor1", L298N, PIN_16, PIN_18, PIN_22);
    if (dev == nullptr)
    {
        write_line("ERROR: Failed to open motor device.");
        raspi_cleanup();
        return;
    }

    // Run forward at 50% speed
    write_line("\nRunning motor FORWARD @ 50% speed. Press any key to reverse direction.");
    set_motor_direction(dev, MOTOR_FORWARD);
    set_motor_speed(dev, 0.5);
    read_line();

    // Reverse at 50% speed
    write_line("\nReversing motor @ 50% speed. Press any key to brake (stop).");
    set_motor_direction(dev, MOTOR_BACKWARD);
    set_motor_speed(dev, 0.5);
    read_line();

    // Brake (both inputs HIGH)
    write_line("\nBraking motor. Press any key to clean up and exit.");
    stop_motor(dev);
    read_line();

    // Clean up
    close_motor(dev);
    raspi_cleanup();

    write_line("\nMotor driver test completed.");
}
