#include "device.h"

#ifdef __APPLE__
template <typename T>
void Describe(const T& dev)
{
    cout << dev.GetName().GetCStr() << endl;
    cout << "It is " << (dev.IsLowPower() ? "" : " not ") << "low power" << endl;
    cout << "It is " << (dev.IsRemovable() ? "" : " not ") << "removable" << endl;
    cout << "It has " << (dev.HasUnifiedMemory() ? "" : " not ") << "unified memory" << endl;
}
#endif

void PrintDevices(){
#ifdef __APPLE__
    auto devices = mtlpp::Device::CopyAllDevices();
    cout << "I found " << sizeof(devices) / sizeof(devices[0]) << " devices" << endl;
    try
    {
        for (uint8_t idev = 0; idev < devices.GetSize(); idev++)
        {
            Describe<mtlpp::Device>(devices[idev]);
        }
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << endl;
    }
#else
    cout<<"No metal GPU device available on this platform"<<endl;
#endif
}

bool IsGPUAvailable(){
#ifdef __APPLE__
    auto devices = mtlpp::Device::CopyAllDevices();
    return (sizeof(devices) / sizeof(devices[0])) > 0;
#else
    return false;
#endif
}