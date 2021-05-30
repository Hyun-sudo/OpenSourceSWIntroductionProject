QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qt/deviceinfopage.cpp \
    qt/devicepage.cpp \
    qt/profilesavedialog.cpp \
    qt/rgbdialog01.cpp \
    qt/rgbdialog02.cpp \
    qt/softwareinfopage.cpp \
    qt/systeminfopage.cpp \
    qt/zoneresizedialog.cpp

HEADERS += \
    ProfileManager.h \
    RGBController/RGBController.h \
    RGBController/RGBController_Dummy.h \
    qt/deviceinfopage.h \
    qt/devicepage.h \
    qt/profilesavedialog.h \
    qt/rgbdialog01.h \
    qt/rgbdialog02.h \
    qt/softwareinfopage.h \
    qt/systeminfopage.h \
    qt/zoneresizedialog.h

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
RGBController/  \
qt/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
