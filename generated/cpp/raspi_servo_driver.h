//
// SplashKit Generated Raspi Servo Driver C++ Code
// DO NOT MODIFY
//

#ifndef __raspi_servo_driver_h
#define __raspi_servo_driver_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

struct _servo_device_data;
typedef struct _servo_device_data *servo_device;
/**
* Close *all* servos.

*
*/
void close_all_servos();
/**
* Closes a servo device given its name.
* @param name The name of the servo device to close.
*
*/
void close_servo(const string &name);
/**
* Close one servo (by handle) or by name.
* Closes a servo device given its pointer.
* @param dev The servo device to close.
*
*/
void close_servo(servo_device dev);
/**
* Returns true if a servo with this name is already open.
* @param name Your identifier for this servo.
* @return true if the servo is open, false otherwise.
*/
bool has_servo_device(const string &name);
/**
* Open (and initialize) a servo on the given board pin.
* @param name Your identifier for this servo.
* @param control_pin Board‐numbered GPIO pin for the servo signal line.
* @return A valid servo_device, or nullptr on failure.
*/
servo_device open_servo(const string &name, gpio_pin control_pin);
/**
* Look up an already‐opened servo by name.
* @param name Your identifier for this servo.
* @return A valid servo_device, or nullptr if not found.
*/
servo_device servo_named(const string &name);
/**
* Convenience: map an angle (0…180°) into the 500…2500 µs range.
* This is a linear mapping, so it may not be accurate for all servos.
* @param dev The servo device to control.
* @param angle_degrees The angle in degrees (0…180).
*
*/
void set_servo_angle(servo_device dev, double angle_degrees);
/**
* Stop sending pulses (servo will hold last position or drift).
* This is a convenience function that sets the pulse width to 0.
* @param dev The servo device to control.
*
*/
void stop_servo(servo_device dev);

#endif /* __raspi_servo_driver_h */
