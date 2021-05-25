/*
 * 로지텍 G Pro Wireless 마우스 컨트롤러
*/

#include "RGBController/RGBController.h"

#include <string>
#include <hidapi/hidapi/hidapi.h>

#pragma once

enum
{
    LOGITECH_G_PRO_WIRELESS_MODE_OFF               = 0x00,
    LOGITECH_G_PRO_WIRELESS_MODE_STATIC            = 0x01,
    LOGITECH_G_PRO_WIRELESS_MODE_CYCLE             = 0x02,
    LOGITECH_G_PRO_WIRELESS_MODE_BREATHING         = 0x03,
};

// 속도는 1000이 빠르고 20000이 느림
// GUI에서 한칸에 100씩 곱함
enum
{
    LOGITECH_G_PRO_WIRELESS_SPEED_SLOWEST          = 0xC8,  // Slowest speed
    LOGITECH_G_PRO_WIRELESS_SPEED_NORMAL           = 0x32,  // Normal speed
    LOGITECH_G_PRO_WIRELESS_SPEED_FASTEST          = 0x0A,  // Fastest speed
};

class LogitechGProWirelessController
{
public:
    LogitechGProWirelessController(hid_device* dev_handle, const char* path);
    ~LogitechGProWirelessController();
    std::string GetDeviceLocation();
    std::string GetSerialString();
    void SendMouseMode(unsigned char mode, unsigned short speed, unsigned char zone, unsigned char red, unsigned char green, unsigned char blue);
private:
    hid_device*             dev;
    std::string             location;
};
