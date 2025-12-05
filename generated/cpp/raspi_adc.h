//
// SplashKit Generated Raspi Adc C++ Code
// DO NOT MODIFY
//

#ifndef __raspi_adc_h
#define __raspi_adc_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _adc_device_data;
typedef struct _adc_device_data *adc_device;
adc_device adc_device_named(const string &name);
void close_adc(adc_device adc);
void close_adc(const string &name);
void close_all_adc();
bool has_adc_device(const string &name);
adc_device open_adc(const string &name, adc_type type_of_adc);
adc_device open_adc(const string &name, int bus, int address, adc_type type_of_adc);
int read_adc(adc_device adc, adc_pin channel);
int read_adc(const string &name, adc_pin channel);

#endif /* __raspi_adc_h */
