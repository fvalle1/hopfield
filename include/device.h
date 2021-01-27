#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>

#include "device_I.h"

#ifdef __APPLE__
#include "mtlpp.hpp"
#endif

using std::cout;
using std::endl;

class Device: public Device_I<mtlpp::Device>{

public:
    static void Describe(const mtlpp::Device &);
    static void PrintDevices();

};

#endif