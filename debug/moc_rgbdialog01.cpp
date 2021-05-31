/****************************************************************************
** Meta object code from reading C++ file 'rgbdialog01.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../qt/rgbdialog01.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rgbdialog01.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RGBDialog01_t {
    QByteArrayData data[14];
    char stringdata0[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RGBDialog01_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RGBDialog01_t qt_meta_stringdata_RGBDialog01 = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RGBDialog01"
QT_MOC_LITERAL(1, 12, 20), // "on_ButtonRed_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_ButtonYellow_clicked"
QT_MOC_LITERAL(4, 58, 22), // "on_ButtonGreen_clicked"
QT_MOC_LITERAL(5, 81, 21), // "on_ButtonCyan_clicked"
QT_MOC_LITERAL(6, 103, 21), // "on_ButtonBlue_clicked"
QT_MOC_LITERAL(7, 125, 24), // "on_ButtonMagenta_clicked"
QT_MOC_LITERAL(8, 150, 23), // "on_ButtonSetAll_clicked"
QT_MOC_LITERAL(9, 174, 26), // "on_ButtonSetDevice_clicked"
QT_MOC_LITERAL(10, 201, 24), // "on_ButtonSetZone_clicked"
QT_MOC_LITERAL(11, 226, 23), // "on_ButtonSetLED_clicked"
QT_MOC_LITERAL(12, 250, 35), // "on_ComboDevices_currentIndexC..."
QT_MOC_LITERAL(13, 286, 33) // "on_ComboModes_currentIndexCha..."

    },
    "RGBDialog01\0on_ButtonRed_clicked\0\0"
    "on_ButtonYellow_clicked\0on_ButtonGreen_clicked\0"
    "on_ButtonCyan_clicked\0on_ButtonBlue_clicked\0"
    "on_ButtonMagenta_clicked\0"
    "on_ButtonSetAll_clicked\0"
    "on_ButtonSetDevice_clicked\0"
    "on_ButtonSetZone_clicked\0"
    "on_ButtonSetLED_clicked\0"
    "on_ComboDevices_currentIndexChanged\0"
    "on_ComboModes_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RGBDialog01[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RGBDialog01::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RGBDialog01 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ButtonRed_clicked(); break;
        case 1: _t->on_ButtonYellow_clicked(); break;
        case 2: _t->on_ButtonGreen_clicked(); break;
        case 3: _t->on_ButtonCyan_clicked(); break;
        case 4: _t->on_ButtonBlue_clicked(); break;
        case 5: _t->on_ButtonMagenta_clicked(); break;
        case 6: _t->on_ButtonSetAll_clicked(); break;
        case 7: _t->on_ButtonSetDevice_clicked(); break;
        case 8: _t->on_ButtonSetZone_clicked(); break;
        case 9: _t->on_ButtonSetLED_clicked(); break;
        case 10: _t->on_ComboDevices_currentIndexChanged(); break;
        case 11: _t->on_ComboModes_currentIndexChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject RGBDialog01::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_RGBDialog01.data,
    qt_meta_data_RGBDialog01,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RGBDialog01::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RGBDialog01::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RGBDialog01.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RGBDialog01::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
