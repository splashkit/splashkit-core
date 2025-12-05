//  raspi_adc.cpp
//  splashkit
// This file is part of the SplashKit Core Library.
// XQuestCode || Aditya Parmar

#include "raspi_adc.h"
#include "gpio_driver.h" // Provides i2c_open, i2c_close, etc.
#include "backend_types.h"
#include "easylogging++.h" // For logging
#include "utils.h"         // For delay function
#include <string>
#include <map>

using std::map;
using std::string;

namespace splashkit_lib
{
    // Internal structure for the ADC device.
    // We use ADC_PTR (defined in BackendTypes.h) to tag these pointers.
    struct _adc_data
    {
        pointer_identifier id; // Should be ADC_PTR
        int i2c_handle;        // I2C handle (obtained from i2c_open)
        int bus;               // I2C bus number
        int address;           // I2C address for the ADC device
        adc_type type;         // ADC type (e.g., ADS7830, PCF8591, etc.)
        string name;           // Device name
    };

    // Static map to manage loaded ADC devices (keyed by name)
    static map<string, adc_device> _adc_devices;

    // a function to return address based on pin number of ads7830
    int _get_ads7830_pin_address(adc_pin pin)
    {
        switch (pin)
        {
        case ADC_PIN_0:
            return 0x84; // CH0
        case ADC_PIN_1:
            return 0xC4; // CH1
        case ADC_PIN_2:
            return 0x94; // CH2
        case ADC_PIN_3:
            return 0xD4; // CH3
        case ADC_PIN_4:
            return 0xA4; // CH4
        case ADC_PIN_5:
            return 0xE4; // CH5
        case ADC_PIN_6:
            return 0xB4; // CH6
        case ADC_PIN_7:
            return 0xF4; // CH7
        default:
            return -1; // Invalid pin
        }
    }

    // a function to return address based on pin number of pcf8591
    int _get_pcf8591_pin_address(adc_pin pin)
    {
        switch (pin)
        {
        case ADC_PIN_0:
            return 0x48; // CH0
        case ADC_PIN_1:
            return 0x49; // CH1
        case ADC_PIN_2:
            return 0x4A; // CH2
        case ADC_PIN_3:
            return 0x4B; // CH3
        default:
            return -1; // Invalid pin
        }
    }

    bool has_adc_device(const string &name)
    {
        return _adc_devices.count(name) > 0;
    }

    adc_device adc_device_named(const string &name)
    {
        if (has_adc_device(name))
            return _adc_devices[name];
        else
        {
            LOG(WARNING) << "ADC device not loaded with name: " << name;
            return nullptr;
        }
    }

    adc_device _load_adc_device(const string &name, int bus, int address, adc_type type)
    {
#ifdef RASPBERRY_PI
        if (has_adc_device(name))
            return adc_device_named(name);

        adc_device result = new _adc_data();
        result->id = ADC_PTR; // ADC_PTR is defined in backend_types.h (0x41444350)
        result->bus = bus;
        result->address = address;
        result->name = name;
        result->type = type;

        // Open the I2C channel to the ADC device.
        // (For both ADS7830 and PCF8591, we assume the initialization is similar.)
        result->i2c_handle = sk_i2c_open(bus, address);
        if (result->i2c_handle < 0)
        {
            LOG(WARNING) << "Error opening ADC device " << name
                         << " on bus " << bus << " at address " << address;
            delete result;
            return nullptr;
        }
        // Try to write a test byte to the device to check if it's responding.
        // This is a simple way to check if the device is connected.
        int test;
        switch (result->type)
        {
        case ADS7830:
        {
            // For ADS7830, we can use a command like 0x84 (CH0) to test.
            test = sk_i2c_write_byte(result->i2c_handle, 0x84);
            break;
        }
        case PCF8591:
        {
            // For PCF8591, we can use a command like 0x48 (CH0) to test.
            test = sk_i2c_write_byte(result->i2c_handle, 0x48);
            break;
        }
        default:
            test = -1;
        }
        if (test < 0)
        {
            // ask the user to check the device connection
            LOG(WARNING) << "Error communicating with ADC device, check your ADC connection" << name
                         << " on bus " << bus << " at address " << address;
            sk_i2c_close(result->i2c_handle);
            delete result;
            return nullptr;
        }

        _adc_devices[name] = result;
        return result;
#else
        LOG(ERROR) << "ADC not supported on this platform";
        return nullptr;
#endif
    }

    adc_device open_adc(const string &name, int bus, int address, adc_type type_of_adc)
    {
#ifdef RASPBERRY_PI
        // Check if the device is already loaded
        if (has_adc_device(name))
        {
            LOG(WARNING) << "ADC device " << name << " already loaded.";
            return adc_device_named(name);
        }

        // Load the ADC device with the specified parameters
        return _load_adc_device(name, bus, address, type_of_adc);
#else
        LOG(ERROR) << "ADC not supported on this platform";
        return nullptr;
#endif
    }

    // Open an ADC device with default parameters (bus 1, address 0x48)
    // ADC functions
    adc_device open_adc(const string &name, adc_type type_of_adc)
    {
#ifdef RASPBERRY_PI
        if (type_of_adc != ADS7830 && type_of_adc != PCF8591)
        {
            LOG(ERROR) << "Unsupported ADC type for " << name;
            return nullptr;
        }
        const int default_bus = 1;
        const int default_address = 0x48; // Default I2C address for ADS7830 and PCF8591
        return _load_adc_device(name, default_bus, default_address, type_of_adc);
#else
        LOG(ERROR) << "ADC not supported on this platform";
        return nullptr;
#endif
    }

    int _read_adc_channel(adc_device dev, int channel)
    {
#ifdef RASPBERRY_PI
        if (dev == nullptr)
        {
            LOG(WARNING) << "Invalid ADC device.";
            return -1;
        }
        int command = 0;
        // Dispatch based on the ADC type.
        switch (dev->type)
        {
        case ADS7830:
        case PCF8591:
            command = channel;
            break;
        default:
            LOG(WARNING) << "Unsupported ADC type for device " << dev->name;
            return -1;
        }

        // Write the command byte to the device (selecting the channel and settings)
        if (sk_i2c_write_byte(dev->i2c_handle, command) < 0)
        {
            LOG(WARNING) << "Failed to write ADC channel command for channel " << channel
                         << " on device " << dev->name;
            return -1;
        }
        // Wait for the conversion to complete (if needed)
        // delay 10 milliseconds
        delay(10);
        // Read the conversion result (8-bit value)
        int value = sk_i2c_read_byte(dev->i2c_handle);
        if (value < 0)
        {
            LOG(WARNING) << "Error reading ADC channel " << channel
                         << " from device " << dev->name;
        }
        return value;
#else
        LOG(ERROR) << "ADC not supported on this platform";
        return -1;
#endif
    }

    // Read the ADC value from a given channel (0-7) using a device pointer.
    int read_adc(adc_device adc, adc_pin channel)
    {
#ifdef RASPBERRY_PI
        if (adc == nullptr)
        {
            LOG(ERROR) << "ADC device not initialized.";
            return -1;
        }
        int channel_num;
        switch (adc->type)
        {
        case ADS7830:
        {
            // ADS7830 supports channels 0-7
            if (channel < ADC_PIN_0 || channel > ADC_PIN_7)
            {
                LOG(WARNING) << "Invalid ADC channel: " << channel
                             << " for device " << adc->name << " (ADS7830 supports 0-7)";
                return -1;
            }
            // Convert the adc_pin enum to the corresponding channel number using _get_ads7830_pin_address
            channel_num = _get_ads7830_pin_address(channel);
            break;
        }
        // Uncomment and complete when implementing other ADC types.
        case PCF8591:
        {
            // Assuming PCF8591 supports channels 0-3; adjust validation as needed.
            if (channel < ADC_PIN_0 || channel > ADC_PIN_3)
            {
                LOG(WARNING) << "Invalid ADC channel: " << channel
                             << " for device " << adc->name << " (PCF8591 supports 0-3)";
                return -1;
            }
            channel_num = _get_pcf8591_pin_address(channel);
            break;
        }
        default:
            LOG(WARNING) << "Unsupported ADC type for device " << adc->name;
            return -1;
        }

        if (channel_num == -1)
        {
            LOG(ERROR) << "Invalid ADC pin: " << channel;
            return -1;
        }
        return _read_adc_channel(adc, channel_num);
#else
        LOG(ERROR) << "ADC not supported on this platform";
        return -1;
#endif
    }

    // Overload: read ADC value by providing the ADC device name.
    int read_adc(const string &name, adc_pin channel)
    {
#ifdef RASPBERRY_PI
        adc_device dev = adc_device_named(name);
        if (dev == nullptr)
        {
            LOG(ERROR) << "ADC device \"" << name << "\" not found.";
            return -1;
        }
        
        return read_adc(dev, channel);
#else
        LOG(ERROR) << "ADC not supported on this platform";
        return -1;
#endif
    }

    void _close_adc_device(adc_device dev)
    {
#ifdef RASPBERRY_PI
        if (dev)
        {
            // Close the I2C connection
            sk_i2c_close(dev->i2c_handle);
            // Remove the device from our map
            _adc_devices.erase(dev->name);
            dev->id = NONE_PTR; // Set pointer to a non-valid identifier
            delete dev;
        }
        else
        {
            LOG(WARNING) << "Attempting to free an invalid ADC device";
        }
#else
        LOG(ERROR) << "ADC not supported on this platform";
#endif
    }

    // Close an ADC device given its pointer.
    void close_adc(adc_device adc)
    {
#ifdef RASPBERRY_PI
        if (adc != nullptr)
            _close_adc_device(adc);
        else
            LOG(WARNING) << "Attempted to close unknown ADC device: " << adc->name;
#else
        LOG(ERROR) << "ADC not supported on this platform";
#endif
    }

    // Overload: close an ADC device using its name.
    void close_adc(const string &name)
    {
#ifdef RASPBERRY_PI
        adc_device dev = adc_device_named(name);
        close_adc(dev);
#else
        LOG(ERROR) << "ADC not supported on this platform";
#endif
    }

    void close_all_adc()
    {
#ifdef RASPBERRY_PI
        for (auto &entry : _adc_devices)
        {
            _close_adc_device(entry.second);
        }
        _adc_devices.clear();
#else
        LOG(ERROR) << "ADC not supported on this platform";
#endif
    }
}
