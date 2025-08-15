//
//  raspi_motor_driver.cpp
//  splashkit
//
// Created by Aditya Parmar on 14/05/2025.
// Copyright © 2024 XQuestCode. All rights reserved.
//

#include "raspi_motor_driver.h"
#include "raspi_gpio.h"    // For GPIO functions
#include "easylogging++.h" // For logging
#include "backend_types.h" // For pointer_identifier

namespace splashkit_lib
{

    struct _motor_data
    {
        pointer_identifier id;
        std::string name;
        motor_driver_type type;
        gpio_pin in1, in2, en;
        motor_direction dir;
    };

    static std::map<std::string, motor_device> _motor_devices;

    bool has_motor_device(const std::string &name)
    {
        return _motor_devices.count(name) > 0;
    }

    motor_device motor_named(const std::string &name)
    {
        auto it = _motor_devices.find(name);
        return it != _motor_devices.end() ? it->second : nullptr;
    }

    motor_device open_motor(const std::string &name, motor_driver_type type, gpio_pin in1_pin, gpio_pin in2_pin, gpio_pin en_pin)
    {
#ifdef RASPBERRY_PI
        if (has_motor_device(name))
            return motor_named(name);
        raspi_init();
        motor_device dev = new _motor_data();
        dev->id = MOTOR_DRIVER_PTR; // defined MOTOR_PTR in backend_types.h
        dev->name = name;
        dev->in1 = in1_pin;
        dev->in2 = in2_pin;
        dev->en = en_pin;
        dev->dir = MOTOR_FORWARD;

        // Configure pins
        raspi_set_mode(in1_pin, GPIO_OUTPUT);
        raspi_set_mode(in2_pin, GPIO_OUTPUT);
        raspi_set_mode(en_pin, GPIO_OUTPUT);
        raspi_write(in1_pin, GPIO_LOW);
        raspi_write(in2_pin, GPIO_LOW);
        raspi_write(en_pin, GPIO_LOW);

        _motor_devices[name] = dev;
        return dev;
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
        return nullptr;
#endif
    }

    void set_motor_direction(motor_device dev, motor_direction dir)
    {
#ifdef RASPBERRY_PI
        if (!dev || dev->id != MOTOR_DRIVER_PTR)
            return;
        dev->dir = dir;
        if (dir == MOTOR_FORWARD)
        {
            raspi_write(dev->in1, GPIO_HIGH);
            raspi_write(dev->in2, GPIO_LOW);
        }
        else
        {
            raspi_write(dev->in1, GPIO_LOW);
            raspi_write(dev->in2, GPIO_HIGH);
        }
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
#endif
    }

    void set_motor_speed(motor_device dev, double speed)
    {
#ifdef RASPBERRY_PI
        if (!dev || dev->id != MOTOR_DRIVER_PTR)
            return;
        // input speed goes from 0 to 1
        // output speed goes from 0 to 255
        int pwm_speed = static_cast<int>(speed * 255);
        if (speed < 0)
        {
            speed = 0;
            LOG(WARNING) << "Motor speed cant be "
                         << "negative, setting to 0";
        }
        if (speed > 1)
        {
            speed = 1;
            LOG(WARNING) << "Motor speed cant be "
                         << "greater than 1, setting to 1";
        }

        raspi_set_pwm_dutycycle(dev->en, pwm_speed);
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
#endif
    }

    void stop_motor(motor_device dev)
    {
#ifdef RASPBERRY_PI
        if (!dev || dev->id != MOTOR_DRIVER_PTR)
            return;
        // Brake: both inputs high
        raspi_write(dev->in1, GPIO_HIGH);
        raspi_write(dev->in2, GPIO_HIGH);
        raspi_set_pwm_dutycycle(dev->en, GPIO_LOW);
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
#endif
    }

    void close_motor(motor_device dev)
    {
#ifdef RASPBERRY_PI
        if (!dev || dev->id != MOTOR_DRIVER_PTR)
            return;
        raspi_write(dev->in1, GPIO_LOW);
        raspi_write(dev->in2, GPIO_LOW);
        raspi_set_pwm_dutycycle(dev->en, GPIO_LOW);
        _motor_devices.erase(dev->name);
        delete dev;
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
#endif
    }

    void close_motor(const std::string &name)
    {
#ifdef RASPBERRY_PI
        if (!has_motor_device(name))
            return;
        motor_device dev = motor_named(name);
        if (dev)
            close_motor(dev);
        _motor_devices.erase(name);
        LOG(INFO) << "Motor device " << name << " closed.";
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
#endif
    }

    void close_all_motors()
    {
#ifdef RASPBERRY_PI
        for (auto &kv : _motor_devices)
        {
            motor_device dev = kv.second;
            raspi_write(dev->in1, GPIO_LOW);
            raspi_write(dev->in2, GPIO_LOW);
            raspi_set_pwm_dutycycle(dev->en, GPIO_LOW);
            delete dev;
        }
        _motor_devices.clear();
        LOG(INFO) << "All motor devices closed.";
#else
        LOG(ERROR) << "Motor driver not supported on this platform";
#endif
    }

}
