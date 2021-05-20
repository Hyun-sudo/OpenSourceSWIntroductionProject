#pragma once

#include "RGBContoller.h"

class RGBController_Dummy : public RGBController
{
public:
    RGBController_Dummy();

    void SetupZones();
    void ResizeZone(int zone, int new_size);
    void DeviceUpdateLEDs();
    void DeviceUpdateZoneLEDs();
    void UpdateZoneLEDs(int zone);
    void UpdateSingleLED(int led);
    void SetCustomMode();
    void DeviceUpdateMode();
};
