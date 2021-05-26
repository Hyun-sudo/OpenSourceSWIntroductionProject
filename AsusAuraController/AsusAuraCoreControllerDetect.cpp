#include "Detector.h"
#include "AsusAuraCoreController.h"
#include "RGBController/RGBController.h"
#include "AsusAuraController/RGBController_AsusAuraCore.h"
#include <hidapi/hidapi/hidapi.h>

#define AURA_CORE_VID 0x0B05

void DetectAsusAuraCoreControllers(hid_device_info* info, const std::string&)
{
    hid_device * dev = hid_open_path(info->path);
    if(dev)
    {
        AuraCoreController * controller = new AuraCoreController(dev, info->path);
        RGBController_AuraCore * rgb_controller = new RGBController_AuraCore(controller);
        // Constructor sets the name
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR("ASUS Aura Core", DetectAsusAuraCoreControllers, AURA_CORE_VID, 0x1854);
REGISTER_HID_DETECTOR("ASUS Aura Core", DetectAsusAuraCoreControllers, AURA_CORE_VID, 0x1866);
REGISTER_HID_DETECTOR("ASUS Aura Core", DetectAsusAuraCoreControllers, AURA_CORE_VID, 0x1869);
