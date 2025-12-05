/**
 * @header raspi_motor_driver
 * @brief Provides support for using a motor driver with the GPIO pins on the Raspberry Pi.
 * @author Aditya Parmar
 *
 * @attribute group  raspberry
 * @attribute static raspberry
 */
#ifndef RASPI_MOTOR_DRIVER_H
#define RASPI_MOTOR_DRIVER_H

#include <string>
#include <map>
#include "backend_types.h" // for pointer_identifier
#include "easylogging++.h"
#include "types.h"

namespace splashkit_lib
{
    /**
     * @brief Opaque handle for an L298N motor driver instance.
     *
     * The `motor_device` type is used to refer to motor driver devices that can
     * be managed by the SplashKit motor driver code. Motor devices are:
     *
     *   - checked with `has_motor_device` to see if a motor is already opened,
     *
     *   - accessed using `motor_named` to retrieve an existing motor device by name,
     *
     *   - opened using `open_motor` with specific parameters such as motor type and GPIO pins,
     *
     *   - controlled using `set_motor_direction` to set the rotation direction and
     *     `set_motor_speed` to adjust the PWM speed,
     *
     *   - stopped immediately using `stop_motor` for braking,
     *
     *   - and must be released using `close_motor` (to release a specific motor device
     *     by handle or name) or `close_all_motors` (to release all opened motor devices).
     *
     * Motor devices allow you to control DC motors or similar devices using GPIO pins
     * and PWM signals, enabling precise control over speed and direction.
     *
     * Use `close_motor` or `close_all_motors` to release resources associated with
     * motor devices when they are no longer needed.
     *
     * @attribute class motor_device
     */
    typedef struct _motor_data *motor_device;

    /**
     * Checks if a motor device with the given name is already opened.
     * 
     * @param name  Identifier for the motor driver.
     * @returns     true if open, false otherwise.
     */
    bool has_motor_device(const string &name);

    /**
     * Retrieves an existing motor device handle by name.
     * 
     * @param name  Identifier for the motor driver.
     * @returns     motor_device pointer or nullptr.
     */
    motor_device motor_named(const string &name);

    /**
     * Opens a motor device with the specified parameters.
     * 
     * @param name      Identifier for the motor driver.
     * @param type      Type of motor driver (e.g., L298N).
     * @param in1_pin   GPIO pin for IN1.
     * @param in2_pin   GPIO pin for IN2.
     * @param en_pin    GPIO pin for ENA.
     * @returns         A valid motor_device on success, or nullptr on failure.
     */
    motor_device open_motor(const string &name, motor_driver_type type, gpio_pin in1_pin, gpio_pin in2_pin, gpio_pin en_pin);

    /**
     * Sets the motor rotation direction.
     * 
     * @param dev       The motor device handle.
     * @param dir       Desired rotation direction.
     */
    void set_motor_direction(motor_device dev, motor_direction dir);

    /**
     * Sets the PWM speed of the motor (0-1).
     * 
     * @param dev       The motor device handle.
     * @param speed     Duty cycle speed (0..1).
     */
    void set_motor_speed(motor_device dev, double speed);

    /**
     * Stops the motor immediately (brake).
     * 
     * @param dev       The motor device handle.
     */
    void stop_motor(motor_device dev);

    /**
     * Closes and frees resources for a motor device.
     * 
     * @param dev       The motor device handle.
     */
    void close_motor(motor_device dev);

    /**
     * Closes and frees a motor device by name.
     * 
     * @param name      Name of the motor device.
     * 
     * @attribute suffix  named
     */
    void close_motor(const string &name);

    /**
     * Closes all opened motor devices.
     */
    void close_all_motors();

}

#endif // RASPI_MOTOR_DRIVER_H
