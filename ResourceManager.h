#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <thread>
#include <string>

#include "i2c_smbus/i2c_smbus.h"
#include "ProfileManager.h"
#include "RGBController/RGBController.h"
#include "SettingsManager.h"

#define HID_INTERFACE_ANY   -1
#define HID_USAGE_ANY       -1
#define HID_USAGE_PAGE_ANY  -1L

#define CONTROLLER_LIST_HID 0

struct hid_device_info;

typedef std::function<void(std::vector<i2c_smbus_interface*>&)>                                 I2CBusDetectorFunction;
typedef std::function<void(std::vector<RGBController*>&)>                                       DeviceDetectorFunction;
typedef std::function<void(std::vector<i2c_smbus_interface*>&, std::vector<RGBController*>&)>   I2CDeviceDetectorFunction;
typedef std::function<void(hid_device_info*, const std::string&)>                               HIDDeviceDetectorFunction;
typedef struct
{
    std::string                 name;
    HIDDeviceDetectorFunction   function;
    unsigned int                address;
    int                         interface;
    int                         usage_page;
    int                         usage;
} HIDDeviceDetectorBlock;

typedef void (*DeviceListChangeCallback)(void *);
typedef void (*DetectionProgressCallback)(void *);
typedef void (*I2CBusListChangeCallback)(void *);

class ResourceManager
{
public:
    static ResourceManager *get();

    ResourceManager();
    ~ResourceManager();

    void RegisterI2CBus(i2c_smbus_interface *);
    std::vector<i2c_smbus_interface*> & GetI2CBusses();

    void RegisterRGBController(RGBController *rgb_controller);

    std::vector<RGBController*> & GetRGBControllers();

    void RegisterI2CBusDetector (I2CBusDetectorFunction     detector);
    void RegisterDeviceDetector (std::string name, DeviceDetectorFunction     detector);
    void RegisterI2CDeviceDetector (std::string name, I2CDeviceDetectorFunction  detector);
    void RegisterHIDDeviceDetector (std::string name, HIDDeviceDetectorFunction  detector, uint16_t vid, uint16_t pid, int interface  = HID_INTERFACE_ANY, int usage_page = HID_USAGE_PAGE_ANY, int usage = HID_USAGE_ANY);

    void RegisterDeviceListChangeCallback(DeviceListChangeCallback new_callback, void * new_callback_arg);
    void RegisterDetectionProgressCallback(DetectionProgressCallback new_callback, void * new_callback_arg);
    void RegisterI2CBusListChangeCallback(I2CBusListChangeCallback new_callback, void * new_callback_arg);

    unsigned int GetDetectionPercent();
    const char * GetDetectionString();

    std::string GetConfigurationDirectory();

    ProfileManager * GetProfileManager();
    SettingsManager * GetSettingsManager();

    void                            SetConfigurationDirectory(std::string directory);

    void DeviceListChanged();
    void DetectionProgressChanged();
    void I2CBusListChanged();

    void Cleanup();
    void DetectDevices();
    void DisableDetection();
    void StopDeviceDetection();
    void WaitForDeviceDetection();

private:
    void DetectDevicesThreadFunction();

    static std::unique_ptr<ResourceManager>     instance;

    // 기기 감지 플래그
    bool detection_enabled;

    // Profile Manager
    ProfileManager * profile_manager;

    // Settings Manager
    SettingsManager * settings_manager;

    // I2C SMBus Interface
    std::vector<i2c_smbus_interface *> busses;

    // RGBControllers
    std::vector<RGBController *> rgb_controllers_sizes;
    std::vector<RGBController *> rgb_controllers_hw;
    std::vector<RGBController *> rgb_controllers;

    // Detectors
    std::vector<DeviceDetectorFunction> device_detectors;
    std::vector<std::string> device_detector_strings;
    std::vector<I2CBusDetectorFunction>         i2c_bus_detectors;
    std::vector<I2CDeviceDetectorFunction>      i2c_device_detectors;
    std::vector<std::string>                    i2c_device_detector_strings;
    std::vector<HIDDeviceDetectorBlock>         hid_device_detectors;
    std::vector<std::string>                    hid_device_detector_strings;

    // Thread Detection & Detection State
    std::thread *                               DetectDevicesThread;
    std::mutex                                  DetectDeviceMutex;

    std::atomic<bool>                           detection_is_required;
    std::atomic<unsigned int>                   detection_percent;
    const char*                                 detection_string;

    // 기기 목록 변화 콜백
    std::mutex                                  DeviceListChangeMutex;
    std::vector<DeviceListChangeCallback>       DeviceListChangeCallbacks;
    std::vector<void *>                         DeviceListChangeCallbackArgs;

    // Detection Progress Callback
    std::mutex                                  DetectionProgressMutex;
    std::vector<DetectionProgressCallback>      DetectionProgressCallbacks;
    std::vector<void *>                         DetectionProgressCallbackArgs;

    // I2C SMBus 어뎁터 리스트 변화 콜백
    std::mutex                                  I2CBusListChangeMutex;
    std::vector<I2CBusListChangeCallback>       I2CBusListChangeCallbacks;
    std::vector<void *>                         I2CBusListChangeCallbackArgs;
};