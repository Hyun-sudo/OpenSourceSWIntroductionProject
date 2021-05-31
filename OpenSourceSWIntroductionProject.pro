QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RGBSync
TEMPLATE = app

VERSION         = 0.1
win32:BUILDDATE = $$system(date /t)
unix:BUILDDATE  = $$system(date -R)
GIT_COMMIT_ID   = $$system(git --git-dir $$_PRO_FILE_PWD_/.git --work-tree $$_PRO_FILE_PWD_ rev-parse HEAD)
GIT_COMMIT_DATE = $$system(git --git-dir $$_PRO_FILE_PWD_/.git --work-tree $$_PRO_FILE_PWD_ show -s --format=%ci HEAD)
GIT_BRANCH      = $$system(git --git-dir $$_PRO_FILE_PWD_/.git --work-tree $$_PRO_FILE_PWD_ rev-parse --abbrev-ref HEAD)

DEFINES += \
    VERSION_STRING=\\"\"\"$$VERSION\\"\"\"                              \
    BUILDDATE_STRING=\\"\"\"$$BUILDDATE\\"\"\"                          \
    GIT_COMMIT_ID=\\"\"\"$$GIT_COMMIT_ID\\"\"\"                         \
    GIT_COMMIT_DATE=\\"\"\"$$GIT_COMMIT_DATE\\"\"\"                     \
    GIT_BRANCH=\\"\"\"$$GIT_BRANCH\\"\"\"
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/AuraSMBusController/AuraSMBusController.cpp \
    Controllers/AuraSMBusController/AuraSMBusControllerDetect.cpp \
    ProfileManger.cpp \
    RGBController/RGBController.cpp \
    RGBController/RGBController_AuraSMBus.cpp \
    RGBController/RGBController_Dummy.cpp \
    RGBSync.cpp \
    cli.cpp \
    dependencies/NVFC/nvapi.cpp \
    dependencies/hidapi/hidapi.c \
    i2c_smbus/i2c_smbus.cpp \
    i2c_smbus/i2c_smbus_piix4.cpp \
    i2c_tools/i2c_tools.cpp \
    main.cpp \
    qt/deviceinfopage.cpp \
    qt/devicepage.cpp \
    qt/hsv.cpp \
    qt/profilesavedialog.cpp \
    qt/rgbdialog01.cpp \
    qt/rgbdialog02.cpp \
    qt/softwareinfopage.cpp \
    qt/systeminfopage.cpp \
    qt/zoneresizedialog.cpp \
    wmi/wmi.cpp

HEADERS += \
    Controllers/AuraSMBusController/AuraSMBusController.h \
    ProfileManager.h \
    RGBController/RGBController.h \
    RGBController/RGBController_AuraSMBus.h \
    RGBController/RGBController_Dummy.h \
    RGBSync.h \
    dependencies/NVFC/nvapi.h \
    dependencies/hidapi/hidapi/hidapi.h \
    dependencies/inpout32_1501/Win32/inpout32.h \
    i2c_smbus/i2c_smbus.h \
    i2c_smbus/i2c_smbus_piix4.h \
    i2c_tools/i2c_tools.h \
    qt/deviceinfopage.h \
    qt/devicepage.h \
    qt/profilesavedialog.h \
    qt/rgbdialog01.h \
    qt/rgbdialog02.h \
    qt/softwareinfopage.h \
    qt/systeminfopage.h \
    qt/zoneresizedialog.h \
    wmi/wmi.h

FORMS += \
    qt/deviceinfopage.ui \
    qt/devicepage.ui \
    qt/profilesavedialog.ui \
    qt/rgbdialog01.ui \
    qt/rgbdialog02.ui \
    qt/softwareinfopage.ui \
    qt/systeminfopage.ui \
    qt/zoneresizedialog.ui

INCLUDEPATH +=  \
dependencies/ \
dependencies/libusb-1.0.22/include \
dependencies/hidapi \
dependencies/inpout32_1501/Win32 \
dependencies/NVFC \
Controllers/AuraSMBusController \
i2c_smbus/ \
i2c_tools/ \
net_port/ \
serial_port/ \
super_io/ \
RGBController/  \
wmi/ \
qt/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:contains(QMAKE_TARGET.arch, x86_64) {
    LIBS +=                                                             \
        -lws2_32                                                        \
        -L"$$PWD/dependencies/inpout32_1501/x64/" -linpoutx64           \
        -L"$$PWD/dependencies/libusb-1.0.22/MS64/dll" -llibusb-1.0      \
}

win32:contains(QMAKE_TARGET.arch, x86) {
    LIBS +=                                                             \
        -lws2_32                                                        \
        -L"$$PWD/dependencies/inpout32_1501/Win32/" -linpout32          \
        -L"$$PWD/dependencies/libusb-1.0.22/MS32/dll" -llibusb-1.0      \
}

win32:DEFINES -=                                                        \
    UNICODE

win32:DEFINES +=                                                        \
    _MBCS                                                               \
    WIN32                                                               \
    _CRT_SECURE_NO_WARNINGS                                             \
    _WINSOCK_DEPRECATED_NO_WARNINGS                                     \
    WIN32_LEAN_AND_MEAN

RESOURCES += \
    qt/resources.qrc
