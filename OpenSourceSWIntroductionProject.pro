QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AsusAuraController/AsusAuraCoreController.cpp \
    AsusAuraController/AsusAuraCoreControllerDetect.cpp \
    AsusAuraController/RGBController_AsusAuraCore.cpp \
    ColorWheel/ColorWheel.cpp \
    LogitechGProWirelessController/LogitechGProWirelessController.cpp \
    LogitechGProWirelessController/RGBController_LogitechGProWireless.cpp \
    ProfileManager.cpp \
    RGBController/RGBController.cpp \
    RGBController/RGBController_Dummy.cpp \
    ResourceManager.cpp \
    dmiinfo.cpp \
    hidapi/hidapi.c \
    i2c_smbus/i2c_smbus.cpp \
    i2c_tools/i2c_tools.cpp \
    libusb-1.0.22/examples/source/ezusb.c \
    libusb-1.0.22/examples/source/fxload.c \
    libusb-1.0.22/examples/source/listdevs.c \
    libusb-1.0.22/examples/source/testlibusb.c \
    libusb-1.0.22/examples/source/xusb.c \
    main.cpp \
    mainwindow.cpp \
    qt/deviceinfopage.cpp \
    qt/devicepage.cpp \
    qt/profilesavedialog.cpp \
    qt/rgbdialog.cpp \
    qt/supporteddevicepage.cpp \
    qt/systeminfopage.cpp \
    qt/zoneresizedialog.cpp

HEADERS += \
    AsusAuraController/AsusAuraCoreController.h \
    AsusAuraController/RGBController_AsusAuraCore.h \
    ColorWheel/ColorWheel.h \
    Detector.h \
    DetectorTableModel.h \
    DeviceDetector.h \
    DeviceView.h \
    LogitechGProWirelessController/LogitechGProWirelessController.h \
    LogitechGProWirelessController/RGBController_LogitechGProWireless.h \
    ProfileManager.h \
    ProfileSaveDialog.h \
    RGBController/RGBController.h \
    RGBController/RGBController_Dummy.h \
    RGBSync.h \
    ResourceManager.h \
    SettingsManager.h \
    dmiinfo.h \
    hidapi/hidapi/hidapi.h \
    i2c_smbus/i2c_smbus.h \
    i2c_tools/i2c_tools.h \
    json/json.hpp \
    libusb-1.0.22/examples/source/ezusb.h \
    libusb-1.0.22/examples/source/stdint.h \
    libusb-1.0.22/include/libusb-1.0/libusb.h \
    mainwindow.h \
    qt/deviceinfopage.h \
    qt/devicepage.h \
    qt/profilesavedialog.h \
    qt/rgbdialog.h \
    qt/supporteddevicepage.h \
    qt/systeminfopage.h \
    qt/zoneresizedialog.h \
    wmi/acpiwmi.h \
    wmi/wmi.h

FORMS += \
    mainwindow.ui \
    qt/deviceinfopage.ui \
    qt/devicepage.ui \
    qt/profilesavedialog.ui \
    qt/rgbdialog.ui \
    qt/supporteddevicepage.ui \
    qt/systeminfopage.ui \
    qt/zoneresizedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    hidapi-win/x64/hidapi.dll \
    hidapi-win/x64/hidapi.lib \
    hidapi-win/x86/hidapi.dll \
    hidapi-win/x86/hidapi.lib \
    libusb-1.0.22/MS32/dll/libusb-1.0.dll \
    libusb-1.0.22/MS32/dll/libusb-1.0.lib \
    libusb-1.0.22/MS32/dll/libusb-1.0.pdb \
    libusb-1.0.22/MS32/static/libusb-1.0.lib \
    libusb-1.0.22/MS64/dll/libusb-1.0.dll \
    libusb-1.0.22/MS64/dll/libusb-1.0.lib \
    libusb-1.0.22/MS64/dll/libusb-1.0.pdb \
    libusb-1.0.22/MS64/static/libusb-1.0.lib \
    libusb-1.0.22/MinGW32/dll/libusb-1.0.dll \
    libusb-1.0.22/MinGW32/dll/libusb-1.0.dll.a \
    libusb-1.0.22/MinGW32/static/libusb-1.0.a \
    libusb-1.0.22/MinGW64/dll/libusb-1.0.dll \
    libusb-1.0.22/MinGW64/dll/libusb-1.0.dll.a \
    libusb-1.0.22/MinGW64/static/libusb-1.0.a \
    libusb-1.0.22/README.txt \
    libusb-1.0.22/examples/bin32/fxload.exe \
    libusb-1.0.22/examples/bin32/listdevs.exe \
    libusb-1.0.22/examples/bin32/testlibusb.exe \
    libusb-1.0.22/examples/bin32/xusb.exe \
    libusb-1.0.22/examples/bin64/fxload.exe \
    libusb-1.0.22/examples/bin64/listdevs.exe \
    libusb-1.0.22/examples/bin64/testlibusb.exe \
    libusb-1.0.22/examples/bin64/xusb.exe \
    libusb-1.0.22/libusb-1.0.def
