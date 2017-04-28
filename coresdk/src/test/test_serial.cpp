//
//  test_serial.cpp
//  splashkit
//
//  Created by Andrew Cain on 28/4/17.
//  Copyright © 2017 Andrew Cain. All rights reserved.
//

#include <iostream>

#include "serial_comms.h"

using namespace std;

using namespace splashkit_lib;

void run_serial_test()
{
    vector<string> ports = list_serial_ports();
    
    for(string s: ports)
    {
        cout << s << endl;
    }
}
