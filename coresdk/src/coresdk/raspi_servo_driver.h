/**
 * @header raspi_servo_driver
 * @brief Provides support for using servo motors with the GPIO pins on the Raspberry Pi.
 * @author Aditya Parmar
 *
 * @attribute group  raspberry
 * @attribute static raspberry
 */
#ifndef RASPI_SERVO_DRIVER_H
#define RASPI_SERVO_DRIVER_H

#include <string>
#include <map>
#include "backend_types.h" // for pointer_identifier
#include "easylogging++.h"
#include "types.h" // for gpio_pin

namespace splashkit_lib
{
  /**
   * The `servo_device` type is used to refer to servo driver devices that can
   * be managed by the SplashKit servo driver code. Servo devices are:
   * Opaque handle for a single‐pin servo device.
   * Servo devices are:
   *   - checked with `has_servo_device` to see if a servo is already opened,
   *
   *   - accessed using `servo_named` to retrieve an existing servo device by name,
   *
   *   - opened using `open_servo` with specific parameters such as a unique name
   *     and the GPIO pin for the servo signal line,
   *
   *   - controlled using `set_servo_pulsewidth` to send raw pulse-width signals
   *     or `set_servo_angle` to map an angle (0–180°) into the pulse-width range,
   *
   *   - stopped using `stop_servo` to halt signal pulses while holding the last
   *     position or allowing the servo to drift,
   *
   *   - and must be released using `close_servo` (to release a specific servo device
   *     by handle or name) or `close_all_servos` (to release all opened servo devices).
   *
   * Servo devices allow you to control hobby servos or similar devices using GPIO pins
   * and PWM signals, enabling precise control over position and movement.
   *
   * Use `close_servo` or `close_all_servos` to release resources associated with
   * servo devices when they are no longer needed.
   *
   * @attribute class servo_device
   */
  typedef struct _servo_data *servo_device;

  /**
   * Returns true if a servo with this name is already open.
   * @param name  Your identifier for this servo.
   * @returns     true if the servo is open, false otherwise.
   */
  bool has_servo_device(const std::string &name);

  /**
   * Look up an already‐opened servo by name.
   * @param name  Your identifier for this servo.
   * @returns A valid servo_device, or nullptr if not found.
   *
   */
  servo_device servo_named(const std::string &name);

  /**
   * Open (and initialize) a servo on the given board pin.
   * @param name         Your identifier for this servo.
   * @param control_pin  Board‐numbered GPIO pin for the servo signal line.
   * @returns            A valid servo_device, or nullptr on failure.
   */
  servo_device open_servo(const std::string &name, gpio_pin control_pin);

  /**
   * Convenience: map an angle (0…180°) into the 500…2500 µs range.
   * This is a linear mapping, so it may not be accurate for all servos.
   * @param dev  The servo device to control.
   * @param angle_degrees  The angle in degrees (0…180).
   */

  void set_servo_angle(servo_device dev, double angle_degrees);

  /**
   * Stop sending pulses (servo will hold last position or drift).
   * This is a convenience function that sets the pulse width to 0.
   * @param dev  The servo device to control.
   * @note This is not the same as closing the servo.
   */
  void stop_servo(servo_device dev);

  /**
   * Close one servo (by handle) or by name.
   * @param dev  The servo device to close.
   * @note This will free the resources associated with the servo.
   */
  void close_servo(servo_device dev);
  void close_servo(const std::string &name);

  /**
   * Close *all* servos.
   */
  void close_all_servos();
}

#endif // RASPI_SERVO_DRIVER_H
