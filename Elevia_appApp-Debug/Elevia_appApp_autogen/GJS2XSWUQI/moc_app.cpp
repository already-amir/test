/****************************************************************************
** Meta object code from reading C++ file 'app.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Elevia_app/App/app.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'app.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSAppENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSAppENDCLASS = QtMocHelpers::stringData(
    "App",
    "ssidChanged",
    "",
    "passwordChanged",
    "enable_wifi",
    "disable_wifi",
    "connect_wifi",
    "disconnect_wifi",
    "scan_wifi",
    "forget_wifi",
    "ssid",
    "password"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSAppENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[4];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[12];
    char stringdata5[13];
    char stringdata6[13];
    char stringdata7[16];
    char stringdata8[10];
    char stringdata9[12];
    char stringdata10[5];
    char stringdata11[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSAppENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSAppENDCLASS_t qt_meta_stringdata_CLASSAppENDCLASS = {
    {
        QT_MOC_LITERAL(0, 3),  // "App"
        QT_MOC_LITERAL(4, 11),  // "ssidChanged"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 15),  // "passwordChanged"
        QT_MOC_LITERAL(33, 11),  // "enable_wifi"
        QT_MOC_LITERAL(45, 12),  // "disable_wifi"
        QT_MOC_LITERAL(58, 12),  // "connect_wifi"
        QT_MOC_LITERAL(71, 15),  // "disconnect_wifi"
        QT_MOC_LITERAL(87, 9),  // "scan_wifi"
        QT_MOC_LITERAL(97, 11),  // "forget_wifi"
        QT_MOC_LITERAL(109, 4),  // "ssid"
        QT_MOC_LITERAL(114, 8)   // "password"
    },
    "App",
    "ssidChanged",
    "",
    "passwordChanged",
    "enable_wifi",
    "disable_wifi",
    "connect_wifi",
    "disconnect_wifi",
    "scan_wifi",
    "forget_wifi",
    "ssid",
    "password"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAppENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       2,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    3 /* Public */,
       3,    0,   63,    2, 0x06,    4 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   64,    2, 0x02,    5 /* Public */,
       5,    0,   65,    2, 0x02,    6 /* Public */,
       6,    0,   66,    2, 0x02,    7 /* Public */,
       7,    0,   67,    2, 0x02,    8 /* Public */,
       8,    0,   68,    2, 0x02,    9 /* Public */,
       9,    0,   69,    2, 0x02,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00015903, uint(0), 0,
      11, QMetaType::QString, 0x00015903, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject App::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSAppENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAppENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAppENDCLASS_t,
        // property 'ssid'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'password'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<App, std::true_type>,
        // method 'ssidChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'passwordChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enable_wifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disable_wifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connect_wifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnect_wifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scan_wifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'forget_wifi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void App::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<App *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ssidChanged(); break;
        case 1: _t->passwordChanged(); break;
        case 2: _t->enable_wifi(); break;
        case 3: _t->disable_wifi(); break;
        case 4: _t->connect_wifi(); break;
        case 5: _t->disconnect_wifi(); break;
        case 6: _t->scan_wifi(); break;
        case 7: _t->forget_wifi(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (App::*)();
            if (_t _q_method = &App::ssidChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (App::*)();
            if (_t _q_method = &App::passwordChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<App *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->ssid(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->password(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<App *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSsid(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPassword(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *App::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *App::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAppENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int App::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void App::ssidChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void App::passwordChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
