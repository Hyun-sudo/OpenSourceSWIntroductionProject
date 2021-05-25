
// Logitech G Pro Wirelss Mouse의 제네릭 인터페이스
#pragma once
#include "RGBController/RGBController.h"
#include "LogitechGProWirelessController.h"

class RGBController_LogitechGProWireless : public RGBController
{
public:
    RGBController_LogitechGProWireless(LogitechGProWirelessController* logitech_ptr);

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        SetCustomMode();
    void        DeviceUpdateMode();

private:
    LogitechGProWirelessController*   logitech;
};
