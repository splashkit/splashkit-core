//
// SplashKit Generated Raspi Motor Driver C++ Code
// DO NOT MODIFY
//

#ifndef __raspi_motor_driver_h
#define __raspi_motor_driver_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

struct _motor_device_data;
typedef struct _motor_device_data *motor_device;
/**
* Closes all opened motor devices.

*
*/
void close_all_motors();
/**
* Closes and frees a motor device by name.
* @param name Name of the motor device.
*
*/
void close_motor(const string &name);
/**
* Closes and frees resources for a motor device.
* @param dev The motor device handle.
*
*/
void close_motor(motor_device dev);
/**
* Free the resources associated with a motor device.
* @param dev The motor device to be destroyed.
*
*/
void free_motor_device(motor_device dev);
/**
* Checks if a motor device with the given name is already opened.
* @param name Identifier for the motor driver.
* @return true if open, false otherwise.
*/
bool has_motor_device(const string &name);
/**
* Retrieves an existing motor device handle by name.
* @param name Identifier for the motor driver.
* @return motor_device pointer or nullptr.
*/
motor_device motor_named(const string &name);
/**
* Opens a motor device with the specified parameters.
* @param name Identifier for the motor driver.
* @param type Type of motor driver (e.g., L298N).
* @param in1_pin GPIO pin for IN1.
* @param in2_pin GPIO pin for IN2.
* @param en_pin GPIO pin for ENA.
* @return A valid motor_device on success, or nullptr on failure.
*/
motor_device open_motor(const string &name, motor_driver_type type, gpio_pin in1_pin, gpio_pin in2_pin, gpio_pin en_pin);
/**
* Sets the motor rotation direction.
* @param dev The motor device handle.
* @param dir Desired rotation direction.
*
*/
void set_motor_direction(motor_device dev, motor_direction dir);
/**
* Sets the PWM speed of the motor (0-1).
* @param dev The motor device handle.
* @param speed Duty cycle speed (0..1).
*
*/
void set_motor_speed(motor_device dev, double speed);
/**
* Stops the motor immediately (brake).
* @param dev The motor device handle.
*
*/
void stop_motor(motor_device dev);

#endif /* __raspi_motor_driver_h */
