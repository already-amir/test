/****************************************************************************
** Meta object code from reading C++ file 'wifi.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/wifi/wifi.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wifi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSWifiENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWifiENDCLASS = QtMocHelpers::stringData(
    "Wifi",
    "wifi_enabled",
    "",
    "wifi_disabled",
    "wifi_connected",
    "ssid",
    "wifi_disconnected",
    "wifi_scan_done",
    "wifiList",
    "wifi_error",
    "message"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWifiENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[5];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[15];
    char stringdata5[5];
    char stringdata6[18];
    char stringdata7[15];
    char stringdata8[9];
    char stringdata9[11];
    char stringdata10[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWifiENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWifiENDCLASS_t qt_meta_stringdata_CLASSWifiENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "Wifi"
        QT_MOC_LITERAL(5, 12),  // "wifi_enabled"
        QT_MOC_LITERAL(18, 0),  // ""
        QT_MOC_LITERAL(19, 13),  // "wifi_disabled"
        QT_MOC_LITERAL(33, 14),  // "wifi_connected"
        QT_MOC_LITERAL(48, 4),  // "ssid"
        QT_MOC_LITERAL(53, 17),  // "wifi_disconnected"
        QT_MOC_LITERAL(71, 14),  // "wifi_scan_done"
        QT_MOC_LITERAL(86, 8),  // "wifiList"
        QT_MOC_LITERAL(95, 10),  // "wifi_error"
        QT_MOC_LITERAL(106, 7)   // "message"
    },
    "Wifi",
    "wifi_enabled",
    "",
    "wifi_disabled",
    "wifi_connected",
    "ssid",
    "wifi_disconnected",
    "wifi_scan_done",
    "wifiList",
    "wifi_error",
    "message"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWifiENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,
       4,    1,   52,    2, 0x06,    3 /* Public */,
       6,    0,   55,    2, 0x06,    5 /* Public */,
       7,    1,   56,    2, 0x06,    6 /* Public */,
       9,    1,   59,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonArray,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject Wifi::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSWifiENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWifiENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWifiENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Wifi, std::true_type>,
        // method 'wifi_enabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'wifi_disabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'wifi_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'wifi_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'wifi_scan_done'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonArray &, std::false_type>,
        // method 'wifi_error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void Wifi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Wifi *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->wifi_enabled(); break;
        case 1: _t->wifi_disabled(); break;
        case 2: _t->wifi_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->wifi_disconnected(); break;
        case 4: _t->wifi_scan_done((*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 5: _t->wifi_error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Wifi::*)();
            if (_t _q_method = &Wifi::wifi_enabled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Wifi::*)();
            if (_t _q_method = &Wifi::wifi_disabled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Wifi::*)(const QString & );
            if (_t _q_method = &Wifi::wifi_connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Wifi::*)();
            if (_t _q_method = &Wifi::wifi_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Wifi::*)(const QJsonArray & );
            if (_t _q_method = &Wifi::wifi_scan_done; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Wifi::*)(const QString & );
            if (_t _q_method = &Wifi::wifi_error; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *Wifi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Wifi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWifiENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Wifi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Wifi::wifi_enabled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Wifi::wifi_disabled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Wifi::wifi_connected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Wifi::wifi_disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Wifi::wifi_scan_done(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Wifi::wifi_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
