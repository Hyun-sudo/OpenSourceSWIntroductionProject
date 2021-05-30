/*
 * RGBController_Dummy.h
 * 제네릭 RGB 인터페이스 더미 클래스
*/

#pragma once

#include "RGBController.h"

class RGBController_Dummy : public RGBController
{
public:
    RGBController_Dummy();

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        UpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        SetCustomMode();
    void        UpdateMode();
};
