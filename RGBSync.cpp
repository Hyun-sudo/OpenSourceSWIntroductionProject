#include "RGBController.h"
#include "i2c_smbus.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <regex>

//#include "wmi.h"



std::vector<i2c_smbus_interface*> busses;
std::vector<RGBController*> rgb_controllers;

/*void DetectI2CBusses()
{
    i2c_smbus_interface * bus;
    HRESULT hres;
    Wmi wmi;
    wmi.init();

    std::vector<QueryObj> q_res_PnPSignedDriver;
    hres = wmi.query("SELECT * FROM Win32_PnPSignedDriver WHERE Description LIKE '\%SMBUS\%' OR Description LIKE '\%SM BUS\%'", q_res_PnPSignedDriver);

    if (hres)
    {
        return;
    }

}*/

void DetectAuraSMBusControllers(std::vector<i2c_smbus_interface*> &busses, std::vector<RGBController*> &rgb_controllers);

void DetectRGBControllers(void)
{
    DetectAuraSMBusControllers(busses, rgb_controllers);
}   /* DetectRGBControllers() */
