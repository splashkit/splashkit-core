// created by XQuestCode || Aditya Parmar
#include <iostream>
#include <limits>
#include <unistd.h> // for usleep()
#include "raspi_gpio.h"
#include "raspi_servo_driver.h"
#include "terminal.h"
#include "utils.h"

using namespace std;
using namespace splashkit_lib;

void run_servo_driver_tests()
{
    write_line("=== Servo Sweep Test ===\n");
    // Initialize GPIO subsystem
    raspi_init();

    // Wiring instructions
    write_line("Wire your servo as follows:");
    write_line("  Signal → BOARD pin 12 (GPIO18)");
    write_line("  VCC    → Pi 5 V (pin 2 or 4)");
    write_line("  GND    → Pi GND (e.g. pin 6)");
    write_line("");

    // Pause until user is ready
    write_line("Press ENTER to begin...\n");
    read_line(); // splashkit’s line-reader :contentReference[oaicite:0]{index=0}

    // Open the servo on board pin 12
    servo_device srv = open_servo("TestServo", PIN_12);
    if (!srv)
    {
        write_line("ERROR: Failed to open servo device.\n");
        raspi_cleanup();
        return;
    }

    const int STEP_DEG = 10; // degrees per step
    const int DELAY_MS = 20; // 20 ms per step

    // Sweep from 0° → 180°
    write_line("Sweeping 0° → 180°...\n");
    for (int deg = 0; deg <= 180; deg += STEP_DEG)
    {
        set_servo_angle(srv, deg);
        delay(DELAY_MS); // splashkit’s millisecond delay :contentReference[oaicite:1]{index=1}
    }

    // Hold at 180° for a second
    delay(1000);

    // Sweep from 180° → 0°
    write_line("Sweeping 180° → 0°...\n");
    for (int deg = 180; deg >= 0; deg -= STEP_DEG)
    {
        set_servo_angle(srv, deg);
        delay(DELAY_MS);
    }

    // Stop pulses and clean up
    stop_servo(srv);
    close_servo(srv);
    raspi_cleanup();

    write_line("\nServo sweep test completed.\n");
}
