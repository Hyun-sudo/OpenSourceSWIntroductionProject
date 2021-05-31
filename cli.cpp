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

    /*---------------------------------------------------------*\
    | If hasDevice is false, devices above is empty and         |
    | allDeviceOptions shall be applied to all available devices|
    \*---------------------------------------------------------*/
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

        // If there are no more colors
        if (rgb_end == std::string::npos)
            break;
        // Remove the current color and the next color's leading comma
        colors_string = colors_string.substr(color.length() + 1);
    }

    return options->colors.size() > 0;
}

unsigned int ParseMode(DeviceOptions& options)
{
    /*---------------------------------------------------------*\
    | Search through all of the device modes and see if there is|
    | a match.  If no match is found, print an error message.   |
    \*---------------------------------------------------------*/
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

    // should never happen
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

/*---------------------------------------------------------------------------------------------------------*\
| Option processing functions                                                                               |
\*---------------------------------------------------------------------------------------------------------*/

void OptionHelp()
{
    std::string help_text;
    help_text += "OpenRGB ";
    help_text += VERSION_STRING;
    help_text += ", for controlling RGB lighting.\n";
    help_text += "Usage: OpenRGB (--device [--mode] [--color])...\n";
    help_text += "\n";
    help_text += "Options:\n";
    help_text += "--gui                                    Show GUI, also appears when not passing any parameters\n";
    help_text += "-l,  --list-devices                      Lists every compatible device with their number\n";
    help_text += "-d,  --device [0-9]                      Selects device to apply colors and/or effect to, or applies to all devices if omitted\n";
    help_text += "                                         Can be specified multiple times with different modes and colors\n";
    help_text += "-c,  --color \"FFFFFF,00AAFF...\"          Sets colors on each device directly if no effect is specified, and sets the effect color if an effect is specified\n";
    help_text += "                                         If there are more LEDs than colors given, the last color will be applied to the remaining LEDs\n";
    help_text += "-m,  --mode [breathing | static | ...]   Sets the mode to be applied, check --list-devices to see which modes are supported on your device\n";
    help_text += "-v,  --version                           Display version and software build information\n";
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

        /*---------------------------------------------------------*\
        | Print device name                                         |
        \*---------------------------------------------------------*/
        std::cout << controller_idx << ": " << controller->name << std::endl;

        /*---------------------------------------------------------*\
        | Print device type                                         |
        \*---------------------------------------------------------*/
            std::cout << "  Type:           " << device_type_to_str(controller->type) << std::endl;

        /*---------------------------------------------------------*\
        | Print device description                                  |
        \*---------------------------------------------------------*/
        if(!controller->description.empty())
        {
            std::cout << "  Description:    " << controller->description << std::endl;
        }

        /*---------------------------------------------------------*\
        | Print device version                                      |
        \*---------------------------------------------------------*/
        if(!controller->version.empty())
        {
            std::cout << "  Version:        " << controller->version << std::endl;
        }

        /*---------------------------------------------------------*\
        | Print device location                                     |
        \*---------------------------------------------------------*/
        if(!controller->location.empty())
        {
            std::cout << "  Location:       " << controller->location << std::endl;
        }

        /*---------------------------------------------------------*\
        | Print device serial                                       |
        \*---------------------------------------------------------*/
        if(!controller->serial.empty())
        {
            std::cout << "  Serial:         " << controller->serial << std::endl;
        }

        /*---------------------------------------------------------*\
        | Print device modes                                        |
        \*---------------------------------------------------------*/
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

        /*---------------------------------------------------------*\
        | Print device zones                                        |
        \*---------------------------------------------------------*/
        if(!controller->zones.empty())
        {
            std::cout << "  Zones:";

            for(std::size_t zone_idx = 0; zone_idx < controller->zones.size(); zone_idx++)
            {
                std::cout << " " << QuoteIfNecessary(controller->zones[zone_idx].name);
            }
            std::cout << std::endl;
        }

        /*---------------------------------------------------------*\
        | Print device LEDs                                         |
        \*---------------------------------------------------------*/
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

        /*---------------------------------------------------------*\
        | Handle options that take an argument                      |
        \*---------------------------------------------------------*/
        if(arg_index + 1 < argc)
        {
            argument = argv[arg_index + 1];
            arg_index++;
        }

        /*---------------------------------------------------------*\
        | -h / --help                                               |
        \*---------------------------------------------------------*/
        if(option == "--help" || option == "-h")
        {
            OptionHelp();
            exit(0);
        }

        /*---------------------------------------------------------*\
        | -v / --version                                            |
        \*---------------------------------------------------------*/
        else if(option == "--version" || option == "-v")
        {
            OptionVersion();
            exit(0);
        }

        /*---------------------------------------------------------*\
        | -l / --list-devices                                       |
        \*---------------------------------------------------------*/
        else if(option == "--list-devices" || option == "-l")
        {
            OptionListDevices();
            exit(0);
        }

        /*---------------------------------------------------------*\
        | -d / --device                                             |
        \*---------------------------------------------------------*/
        else if(option == "--device" || option == "-d")
        {
            if(!OptionDevice(&currentDev, argument, options))
            {
                return false;
            }
        }

        /*---------------------------------------------------------*\
        | -c / --color                                              |
        \*---------------------------------------------------------*/
        else if(option == "--color" || option == "-c")
        {
            if(!OptionColor(&currentDev, argument, options))
            {
                return false;
            }
        }

        /*---------------------------------------------------------*\
        | -m / --mode                                               |
        \*---------------------------------------------------------*/
        else if(option == "--mode" || option == "-m")
        {
            if(!OptionMode(&currentDev, argument, options))
            {
                return false;
            }
        }

        /*
        else if(option == "--profile" || option == "-p")
        {
            OptionProfile(argument);
            exit(0);
        }*/

        /*---------------------------------------------------------*\
        | -sp / --save-profile                                      |
        \*---------------------------------------------------------*/
        else if(option == "--save-profile" || option == "-sp")
        {
            OptionSaveProfile(argument);
        }

        /*---------------------------------------------------------*\
        | Invalid option                                            |
        \*---------------------------------------------------------*/
        else
        {
            std::cout << "Error: Invalid option: " + option << std::endl;
            return false;
        }

        arg_index++;
    }

    /*---------------------------------------------------------*\
    | If a device was specified, check to verify that a         |
    | corresponding option was also specified                   |
    \*---------------------------------------------------------*/
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

    /*---------------------------------------------------------*\
    | Set mode first, in case it's 'direct' (which affects      |
    | SetLED below)                                             |
    \*---------------------------------------------------------*/
    unsigned int mode = ParseMode(options);

    /*---------------------------------------------------------*\
    | Determine which color mode this mode uses and update      |
    | colors accordingly                                        |
    \*---------------------------------------------------------*/
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

    /*---------------------------------------------------------*\
    | Set device mode                                           |
    \*---------------------------------------------------------*/
    device->SetMode(mode);

    /*---------------------------------------------------------*\
    | Set device per-LED colors if necessary                    |
    \*---------------------------------------------------------*/
    if(device->modes[mode].color_mode == MODE_COLORS_PER_LED)
    {
        device->UpdateLEDs();
    }
}

int cli_main(int argc, char *argv[], std::vector<RGBController *> rgb_controllers_in/*, ProfileManager* profile_manager_in*/)
{
    rgb_controllers = rgb_controllers_in;
    //profile_manager = profile_manager_in;

    /*---------------------------------------------------------*\
    | Process the argument options                              |
    \*---------------------------------------------------------*/
    Options options;
    if (!ProcessOptions(argc, argv, &options))
    {
        OptionHelp();
        return -1;
    }

    /*---------------------------------------------------------*\
    | If the options has one or more specific devices, loop     |
    | through all of the specific devices and apply settings.   |
    | Otherwise, apply settings to all devices.                 |
    \*---------------------------------------------------------*/
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

    /*---------------------------------------------------------*\
    | If there is a save filename set, save the profile         |
    \*---------------------------------------------------------*/
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
