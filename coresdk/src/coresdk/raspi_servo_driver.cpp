//
//  raspi_servo_driver.cpp
//  splashkit
//
// Created by Aditya Parmar on 14/05/2025.
// Copyright © 2024 XQuestCode. All rights reserved.
//

#include "raspi_servo_driver.h"
#include "raspi_gpio.h" // for raspi_init()

#include <algorithm> // for std::clamp

namespace splashkit_lib
{
  struct _servo_data
  {
    pointer_identifier id;
    string name;
    gpio_pin pin;
  };

  static std::map<string, servo_device> _servo_devices;
  static const unsigned MIN_PW = 500;  // µs at 0°
  static const unsigned MAX_PW = 2500; // µs at 180°

  bool has_servo_device(const string &name)
  {
    return _servo_devices.count(name) > 0;
  }

  servo_device servo_named(const string &name)
  {
    auto it = _servo_devices.find(name);
    return (it != _servo_devices.end()) ? it->second : nullptr;
  }

  servo_device open_servo(const string &name, gpio_pin control_pin)
  {
#ifdef RASPBERRY_PI
    if (has_servo_device(name))
      return servo_named(name);

    // ensure pigpio is initialized
    raspi_init();

    auto dev = new _servo_data();
    dev->id = SERVO_DRIVER_PTR; // you'll need to #define this in backend_types.h
    dev->name = name;
    dev->pin = control_pin;

    // configure as output
    raspi_set_mode(control_pin, GPIO_OUTPUT);
    // configure the pin for 50 Hz PWM, range = 20000 units ? 1 unit = 1 µs
    raspi_set_pwm_range(control_pin, 20000);
    raspi_set_pwm_frequency(control_pin, 50);
    // stop any pulses initially
    raspi_set_pwm_dutycycle(control_pin, 0);

    _servo_devices[name] = dev;
    return dev;
#else
    LOG(ERROR) << "Servo driver not supported on this platform";
    return nullptr;
#endif
  }

  void set_servo_angle(servo_device dev, double angle)
  {
#ifdef RASPBERRY_PI
    if (!dev || dev->id != SERVO_DRIVER_PTR)
      return;

    // clamp to [0,180]
    angle = std::clamp(angle, 0.0, 180.0);
    unsigned pw = static_cast<unsigned>(
        MIN_PW + (angle / 180.0) * (MAX_PW - MIN_PW));
    raspi_set_servo_pulsewidth(dev->pin, pw - 180);
#else
    LOG(ERROR) << "Servo driver not supported on this platform";
#endif
  }

  void stop_servo(servo_device dev)
  {
#ifdef RASPBERRY_PI
    if (!dev || dev->id != SERVO_DRIVER_PTR)
      return;
    // 0 µs stops pulses
    raspi_set_pwm_dutycycle(dev->pin, 0);
#else
    LOG(ERROR) << "Servo driver not supported on this platform";
#endif
  }

  void close_servo(servo_device dev)
  {
#ifdef RASPBERRY_PI
    if (!dev || dev->id != SERVO_DRIVER_PTR)
      return;
    // make sure pulses are off
    raspi_set_pwm_dutycycle(dev->pin, 0);
    _servo_devices.erase(dev->name);
    delete dev;
#else
    LOG(ERROR) << "Servo driver not supported on this platform";
#endif
  }

  void close_servo(const string &name)
  {
#ifdef RASPBERRY_PI
    auto dev = servo_named(name);
    if (dev)
      close_servo(dev);
#else
    LOG(ERROR) << "Servo driver not supported on this platform";
#endif
  }

  void close_all_servos()
  {
#ifdef RASPBERRY_PI
    for (auto &kv : _servo_devices)
    {
      auto dev = kv.second;
      raspi_set_pwm_dutycycle(dev->pin, 0);
      delete dev;
    }
    _servo_devices.clear();
#else
    LOG(ERROR) << "Servo driver not supported on this platform";
#endif
  }
}
