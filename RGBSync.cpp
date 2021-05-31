/******************************************************************************************\
*                                                                                          *
*   OpenRGB.cpp                                                                            *
*                                                                                          *
*       Functions for communicating with RGBController API devices on Windows and Linux    *
*                                                                                          *
\******************************************************************************************/

#include "RGBController.h"
#include "i2c_smbus.h"
#include "i2c_smbus_piix4.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include "wmi.h"



std::vector<i2c_smbus_interface*> busses;
std::vector<RGBController*> rgb_controllers;

void DetectAuraSMBusControllers(std::vector<i2c_smbus_interface*> &busses, std::vector<RGBController*> &rgb_controllers);

/******************************************************************************************\
*                                                                                          *
*   DetectI2CBusses (Windows)                                                              *
*                                                                                          *
*       Detects available AMD and Intel SMBUS adapters and enumerates i2c_smbus_interface  *
*       objects for them                                                                   *
*                                                                                          *
\******************************************************************************************/

void DetectI2CBusses()
{
    i2c_smbus_interface * bus;
    HRESULT hres;
    Wmi wmi;
    wmi.init();

    // Query WMI for Win32_PnPSignedDriver entries with names matching "SMBUS" or "SM BUS"
    // These devices may be browsed under Device Manager -> System Devices
    std::vector<QueryObj> q_res_PnPSignedDriver;
    hres = wmi.query("SELECT * FROM Win32_PnPSignedDriver WHERE Description LIKE '\%SMBUS\%' OR Description LIKE '\%SM BUS\%'", q_res_PnPSignedDriver);

    if (hres)
    {
        return;
    }

    // For each detected SMBus adapter, try enumerating it as either AMD or Intel
    for (QueryObj &i : q_res_PnPSignedDriver)
    {
        // AMD SMBus controllers do not show any I/O resources allocated in Device Manager
        // Analysis of many AMD boards has shown that AMD SMBus controllers have two adapters with fixed I/O spaces at 0x0B00 and 0x0B20
        // AMD SMBus adapters use the PIIX4 driver
        if (i["Manufacturer"].find("Advanced Micro Devices, Inc") != std::string::npos)
        {
            bus = new i2c_smbus_piix4();
            strcpy(bus->device_name, i["Description"].c_str());
            strcat(bus->device_name, " at 0x0B00");
            ((i2c_smbus_piix4 *)bus)->piix4_smba = 0x0B00;
            busses.push_back(bus);

            bus = new i2c_smbus_piix4();
            ((i2c_smbus_piix4 *)bus)->piix4_smba = 0x0B20;
            strcpy(bus->device_name, i["Description"].c_str());
            strcat(bus->device_name, " at 0x0B20");
            busses.push_back(bus);
        }
    }
}   /* DetectI2CBusses() */

/******************************************************************************************\
*                                                                                          *
*   DetectRGBConrollers                                                                    *
*                                                                                          *
*       Detect and populate RGB Controllers vector                                         *
*                                                                                          *
\******************************************************************************************/


void DetectRGBControllers(void)
{
    DetectI2CBusses();

    DetectAuraSMBusControllers(busses, rgb_controllers);

}   /* DetectRGBControllers() */
