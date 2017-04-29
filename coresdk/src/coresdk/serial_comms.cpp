//
//  serial.cpp
//  splashkit
//
//  Created by Andrew Cain on 12/4/17.
//  Copyright © 2017 Andrew Cain. All rights reserved.
//

#include "serial_comms.h"

#ifdef WINDOWS
#define _WIN32
#include <string.h>
#define __int64 int64_t
#endif

#include "serial/serial.h"

#ifdef WINDOWS
#undef _WIN32
#endif


#include "backend_types.h"

namespace splashkit_lib
{

    struct _serial_device
    {
        _serial_device(string port, unsigned int baud) : device(port,  static_cast<uint32_t>(baud), serial::Timeout::simpleTimeout(1000))
        {
            this->id = SERIAL_PTR;
        }
        
        pointer_identifier id;
        string name;
        serial::Serial device;
    };
    
    static map<string, serial_device> _serial_devices;
    
    bool has_serial_device(string name)
    {
        return _serial_devices.count(name) > 0;
    }
    
    serial_device serial_device_named(string name)
    {
        if (has_serial_device(name))
            return _serial_devices[name];
        else
            return nullptr;
    }

    vector<string> list_serial_ports()
    {
        vector<serial::PortInfo> devices_found = serial::list_ports();
        
        vector<serial::PortInfo>::iterator iter = devices_found.begin();
        
        vector<string> result;
        
        while( iter != devices_found.end() )
        {
            serial::PortInfo device = *iter++;
            
            result.push_back(device.port);
        }
        
        return result;
    }
    
    serial_device open_serial_device(string name, string port, unsigned int baud)
    {
        serial_device result = new _serial_device(port, baud);
        
        result->id = SERIAL_PTR;
        result->name = name;
        
//        result->device = serial::Serial(port, baud, serial::Timeout::simpleTimeout(1000));
        
        return result;
    }
    
}
