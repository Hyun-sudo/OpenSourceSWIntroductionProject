#include <vector>
#include <cstring>
#include <string>
#include <tuple>
#include <iostream>
#include "RGBSync.h"
#include "ProfileManager.h"
#include "RGBController.h"
#include "i2c_smbus.h"

static std::vector<RGBController*> rgb_controllers;
static ProfileManager*             profile_manager;
static std::string                 profile_save_filename = "";

struct DeviceOptions
{
    int device;
    std::vector<std::tuple<unsigned char, unsigned char, unsigned char>> colors;
    std::string mode;
    bool hasOption;
};

struct Options
{
    std::vector<DeviceOptions> devices;

    // hasDevice 가 false이면, 기기는 비어있는 것
    // allDeviceOptions은 모든 활성화 기기에 적용되어야 함
    bool hasDevice;
    DeviceOptions allDeviceOptions;
};

bool ParseColors(std::string colors_string, DeviceOptions *options)
{
    while (colors_string.length() >= 6)
    {
        int rgb_end = colors_string.find_first_of(',');
        std::string color = colors_string.substr(0, rgb_end);
        if (color.length() != 6)
            break;

        try
        {
            unsigned char r = std::stoi(color.substr(0, 2), nullptr, 16);
            unsigned char g = std::stoi(color.substr(2, 2), nullptr, 16);
            unsigned char b = std::stoi(color.substr(4, 2), nullptr, 16);
            options->colors.push_back(std::make_tuple(r, g, b));
        }
        catch (...)
        {
            break;
        }

        // 색이 더 이상 없으면
        if (rgb_end == std::string::npos)
            break;
        // 현재 색 제거함
        colors_string = colors_string.substr(color.length() + 1);
    }

    return options->colors.size() > 0;
}

unsigned int ParseMode(DeviceOptions& options)
{
    // 모든 기기 모드에서 맞는 모드를 찾음
    // 찾지 못하면 에러 메세지 출력
    for(std::size_t mode_idx = 0; mode_idx < rgb_controllers[options.device]->modes.size(); mode_idx++)
    {
        if (rgb_controllers[options.device]->modes[mode_idx].name == options.mode)
        {
            return mode_idx;
        }
    }

    std::cout << "Error: Mode '" + options.mode + "' not available for device '" + rgb_controllers[options.device]->name + "'" << std::endl;
    return false;
}

DeviceOptions* GetDeviceOptionsForDevID(Options *opts, int device)
{
    if (device == -1)
    {
        return &opts->allDeviceOptions;
    }

    for (int i = 0; i < opts->devices.size(); i++)
    {
        if (opts->devices[i].device == device)
        {
            return &opts->devices[i];
        }
    }
    std::cout << "Internal error: Tried setting an option on a device that wasn't specified" << std::endl;
    abort();
}

std::string QuoteIfNecessary(std::string str)
{
    if (str.find(' ') == std::string::npos)
    {
        return str;
    }
    else
    {
        return "'" + str + "'";
    }
}

// 옵션 처리 함수들

void OptionHelp()
{
    std::string help_text;
    help_text += "OpenRGB ";
    help_text += VERSION_STRING;
    help_text += ", for controlling RGB lighting.\n";
    help_text += "Usage: OpenRGB (--device [--mode] [--color])...\n";
    help_text += "\n";
    help_text += "Options:\n";
    help_text += "--gui                                    GUI를 보여줍니다.\n";
    help_text += "-l,  --list-devices                      모든 호환 장치를 해당 번호로 나열합니다.\n";
    help_text += "-d,  --device [0-9]                      색상 또는 효과를 적용할 장치를 선택하거나 누락된 경우 모든 장치에 적용합니다.\n";
    help_text += "                                         C다른 모드와 색상으로 여러 번 지정할 수 있습니다.\n";
    help_text += "-c,  --color \"FFFFFF,00AAFF...\"          효과가 지정되지 않은 경우 각 장치에 직접 색상을 설정하고 효과가 지정된 경우 효과 색상을 설정합니다.\n";
    help_text += "                                         주어진 색상보다 LED가 많을 경우 남은 LED에 마지막 색상이 적용됩니다.\n";
    help_text += "-m,  --mode [breathing | static | ...]   적용할 모드를 설정합니다. --list-devices를 확인하여 장치에서 지원되는 모드를 확인합니다.\n";
    help_text += "-v,  --version                           버전 및 소프트웨어 빌드 정보 표시\n";
    help_text += "-p,  --profile filename.orp              Load the profile from filename.orp\n";
    help_text += "-sp, --save-profile filename.orp         Save the given settings to profile filename.orp\n";

    std::cout << help_text << std::endl;
}

void OptionVersion()
{
    std::string version_text;
    version_text += "OpenRGB ";
    version_text += VERSION_STRING;
    version_text += ", for controlling RGB lighting.\n";
    version_text += "  Version:\t\t ";
    version_text += VERSION_STRING;
    version_text += "\n  Build Date\t\t ";
    version_text += BUILDDATE_STRING;
    version_text += "\n  Git Commit ID\t\t ";
    version_text += GIT_COMMIT_ID;
    version_text += "\n  Git Commit Date\t ";
    version_text += GIT_COMMIT_DATE;
    version_text += "\n  Git Branch\t\t ";
    version_text += GIT_BRANCH;
    version_text += "\n";

    std::cout << version_text << std::endl;
}

void OptionListDevices()
{
    for(std::size_t controller_idx = 0; controller_idx < rgb_controllers.size(); controller_idx++)
    {
        RGBController *controller = rgb_controllers[controller_idx];

        // 기기 이름 출력
        std::cout << controller_idx << ": " << controller->name << std::endl;

        // 기기 타입 출력
            std::cout << "  Type:           " << device_type_to_str(controller->type) << std::endl;

        // 기기 설명 출력
        if(!controller->description.empty())
        {
            std::cout << "  Description:    " << controller->description << std::endl;
        }

        // 기기 버전 출력
        if(!controller->version.empty())
        {
            std::cout << "  Version:        " << controller->version << std::endl;
        }

        // 기기 위치 출력
        if(!controller->location.empty())
        {
            std::cout << "  Location:       " << controller->location << std::endl;
        }

        // 기기 시리얼 출력
        if(!controller->serial.empty())
        {
            std::cout << "  Serial:         " << controller->serial << std::endl;
        }

        // 기기 모드 출력
        if(!controller->modes.empty())
        {
            std::cout << "  Modes:";

            int current_mode = controller->GetMode();
            for(std::size_t mode_idx = 0; mode_idx < controller->modes.size(); mode_idx++)
            {
                std::string modeStr = QuoteIfNecessary(controller->modes[mode_idx].name);

                if(current_mode == (int)mode_idx)
                {
                    modeStr = "[" + modeStr + "]";
                }
                std::cout << " " << modeStr;
            }
            std::cout << std::endl;
        }

        // 기기 zone 출력
        if(!controller->zones.empty())
        {
            std::cout << "  Zones:";

            for(std::size_t zone_idx = 0; zone_idx < controller->zones.size(); zone_idx++)
            {
                std::cout << " " << QuoteIfNecessary(controller->zones[zone_idx].name);
            }
            std::cout << std::endl;
        }

        // 기기 LED 출력
        if(!controller->leds.empty())
        {
            std::cout << "  LEDs:";

            for(std::size_t led_idx = 0; led_idx < controller->leds.size(); led_idx++)
            {
                std::cout << " " << QuoteIfNecessary(controller->leds[led_idx].name);
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}

bool OptionDevice(int *currentDev, std::string argument, Options *options)
{
    try
    {
        *currentDev = std::stoi(argument);

        if (rgb_controllers.size() <= *currentDev || *currentDev < 0)
        {
            throw;
        }

        DeviceOptions newDev;
        newDev.device = *currentDev;

        if(!options->hasDevice)
        {
            options->hasDevice = true;
        }

        options->devices.push_back(newDev);

        return true;
    }
    catch(...)
    {
        std::cout << "Error: Invalid device ID: " + argument << std::endl;
        return false;
    }
}

bool OptionColor(int *currentDev, std::string argument, Options *options)
{
    DeviceOptions* currentDevOpts = GetDeviceOptionsForDevID(options, *currentDev);

    if(ParseColors(argument, currentDevOpts))
    {
        currentDevOpts->hasOption = true;
        return true;
    }
    else
    {
        std::cout << "Error: Invalid color value: " + argument << std::endl;
        return false;
    }
}

bool OptionMode(int *currentDev, std::string argument, Options *options)
{
    DeviceOptions* currentDevOpts = GetDeviceOptionsForDevID(options, *currentDev);
    currentDevOpts->mode = argument;
    currentDevOpts->hasOption = true;
    return true;
}
bool OptionProfile(std::string argument)
{
    if(profile_manager->LoadProfile(argument))
    {
        for(std::size_t controller_idx = 0; controller_idx < rgb_controllers.size(); controller_idx++)
        {
            RGBController* device = rgb_controllers[controller_idx];

            device->SetMode(device->active_mode);

            if(device->modes[device->active_mode].color_mode == MODE_COLORS_PER_LED)
            {
                device->UpdateLEDs();
            }
        }

        std::cout << "Profile loaded successfully" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Profile failed to load" << std::endl;
        return false;
    }
}

bool OptionSaveProfile(std::string argument)
{
    /*---------------------------------------------------------*\
    | Set save profile filename                                 |
    \*---------------------------------------------------------*/
    profile_save_filename = argument;
    return(true);
}

bool ProcessOptions(int argc, char *argv[], Options *options)
{
    int arg_index = 1;
    int currentDev = -1;

    options->hasDevice = false;

    while(arg_index < argc)
    {
        std::string option   = argv[arg_index];
        std::string argument = "";

        // argument를 가지는 옵션 처리
        if(arg_index + 1 < argc)
        {
            argument = argv[arg_index + 1];
            arg_index++;
        }

        // 도움말
        if(option == "--help" || option == "-h")
        {
            OptionHelp();
            exit(0);
        }

        // 버전
        else if(option == "--version" || option == "-v")
        {
            OptionVersion();
            exit(0);
        }

        // 기기 목록
        else if(option == "--list-devices" || option == "-l")
        {
            OptionListDevices();
            exit(0);
        }

        // 기기
        else if(option == "--device" || option == "-d")
        {
            if(!OptionDevice(&currentDev, argument, options))
            {
                return false;
            }
        }

        // 색
        else if(option == "--color" || option == "-c")
        {
            if(!OptionColor(&currentDev, argument, options))
            {
                return false;
            }
        }

        // 모드
        else if(option == "--mode" || option == "-m")
        {
            if(!OptionMode(&currentDev, argument, options))
            {
                return false;
            }
        }

        // 프로필 저장
        else if(option == "--save-profile" || option == "-sp")
        {
            OptionSaveProfile(argument);
        }

        // invaild option
        else
        {
            std::cout << "Error: Invalid option: " + option << std::endl;
            return false;
        }

        arg_index++;
    }

    // 기기가 특정되면 이에 대응하는 옵션들도 특정되는 지 확인
    if(options->hasDevice)
    {
        for(std::size_t option_idx = 0; option_idx < options->devices.size(); option_idx++)
        {
            if(!options->devices[option_idx].hasOption)
            {
                std::cout << "Error: Device " + std::to_string(option_idx) + " specified, but neither mode nor color given" << std::endl;
                return false;
            }
        }
    }
    else
    {
        return options->allDeviceOptions.hasOption;
    }

    return true;
}

void ApplyOptions(DeviceOptions& options)
{
    RGBController *device = rgb_controllers[options.device];

    // 모드가 'direct'이면 모드 먼저 설정
    unsigned int mode = ParseMode(options);

    // 어떤 색 모드가 사용되는지 결정
    // 색을 통일되게 업데이트
    switch(device->modes[mode].color_mode)
    {
        case MODE_COLORS_NONE:
            break;

        case MODE_COLORS_RANDOM:
            break;

        case MODE_COLORS_PER_LED:
            if(options.colors.size() != 0)
            {
                std::size_t last_set_color;

                for(std::size_t led_idx = 0; led_idx < device->leds.size(); led_idx++)
                {
                    if(led_idx < options.colors.size())
                    {
                        last_set_color = led_idx;
                    }

                    device->colors[led_idx] = ToRGBColor(std::get<0>(options.colors[last_set_color]),
                                                         std::get<1>(options.colors[last_set_color]),
                                                         std::get<2>(options.colors[last_set_color]));
                }
            }
            break;

        case MODE_COLORS_MODE_SPECIFIC:
            if(options.colors.size() >= device->modes[mode].colors_min && options.colors.size() <= device->modes[mode].colors_max)
            {
                device->modes[mode].colors.resize(options.colors.size());

                for(std::size_t color_idx = 0; color_idx <= options.colors.size(); color_idx++)
                {
                    device->modes[mode].colors[color_idx] = ToRGBColor(std::get<0>(options.colors[color_idx]),
                                                                       std::get<1>(options.colors[color_idx]),
                                                                       std::get<2>(options.colors[color_idx]));
                }
            }
            else
            {
                std::cout << "Wrong number of colors specified for mode" << std::endl;
                exit(0);
            }
            break;
    }


    // 기기 모드 설정
    device->SetMode(mode);

    // 지원하는 경우에만 각 LED 색 설정
    if(device->modes[mode].color_mode == MODE_COLORS_PER_LED)
    {
        device->UpdateLEDs();
    }
}

int cli_main(int argc, char *argv[], std::vector<RGBController *> rgb_controllers_in, ProfileManager* profile_manager_in)
{
    rgb_controllers = rgb_controllers_in;
    profile_manager = profile_manager_in;

    // options argument 처리
    Options options;
    if (!ProcessOptions(argc, argv, &options))
    {
        OptionHelp();
        return -1;
    }

    // 옵션이 하나 이상의 특정된 기기를 가진다면 모든 특정된 기기를 루프하면서 설정을 적용
    // 아니면 모든 새팅을 모든 기기에 적용
    if (options.hasDevice)
    {
        for(std::size_t device_idx = 0; device_idx < options.devices.size(); device_idx++)
        {
            ApplyOptions(options.devices[device_idx]);
        }
    }
    else
    {
        for (std::size_t device_idx = 0; device_idx < rgb_controllers.size(); device_idx++)
        {
            options.allDeviceOptions.device = device_idx;
            ApplyOptions(options.allDeviceOptions);
        }
    }

    // 파일 이름이 존재하면 프로필 파일을 저장함
    if(profile_save_filename != "")
    {
        if(profile_manager->SaveProfile(profile_save_filename))
        {
            std::cout << "Profile saved successfully" << std::endl;
        }
        else
        {
            std::cout << "Profile saving failed" << std::endl;
        }
    }

    return 0;
}
