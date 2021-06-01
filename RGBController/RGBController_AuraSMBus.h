/*
 * RGBController_AuraSMBus.h
 * Asus Aura SMBus 드라이버를 위한 제네릭 RGB 인터페이스
*/

#pragma once

#include "RGBController.h"
#include "AuraSMBusController.h"

class RGBController_AuraSMBus : public RGBController
{
public:
    RGBController_AuraSMBus(AuraSMBusController* aura_ptr);

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        UpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        SetCustomMode();
    void        UpdateMode();

private:
    AuraSMBusController* aura;

    int         GetDeviceMode();
};
