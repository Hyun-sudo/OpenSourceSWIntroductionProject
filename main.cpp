#include "RGBSync.h"
#include "ProfileManager.h"
#include "RGBController.h"
#include "i2c_smbus.h"

#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "rgbdialog02.h"

extern std::vector<i2c_smbus_interface*> busses;
extern std::vector<RGBController*> rgb_controllers;

extern int cli_main(int argc, char *argv[], std::vector<RGBController *> rgb_controllers_in, ProfileManager* profile_manager_in);


int main(int argc, char *argv[])
{
    ProfileManager profile_manager(rgb_controllers);

    DetectRGBControllers();

    profile_manager.LoadSizeFromProfile("sizes.ors");

    if (argc > 1 && strcmp(argv[1], "--gui"))
    {
        return cli_main(argc, argv, rgb_controllers, &profile_manager);
    }

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    RGBDialog02 dlg(busses, rgb_controllers, profile_manager);
    dlg.show();

    return a.exec();
}
