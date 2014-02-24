/****************************************************************************
** Meta object code from reading C++ file 'jarvis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jarvis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jarvis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Jarvis_t {
    QByteArrayData data[8];
    char stringdata[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Jarvis_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Jarvis_t qt_meta_stringdata_Jarvis = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 11),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 30),
QT_MOC_LITERAL(4, 51, 17),
QT_MOC_LITERAL(5, 69, 33),
QT_MOC_LITERAL(6, 103, 4),
QT_MOC_LITERAL(7, 108, 13)
    },
    "Jarvis\0setSettings\0\0VoiceSettingsDialog::Settings*\0"
    "onVoiceRecognized\0PXCVoiceRecognition::Recognition*\0"
    "data\0prepareToQuit\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Jarvis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a,
       4,    1,   32,    2, 0x0a,
       7,    0,   35,    2, 0x08,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void Jarvis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Jarvis *_t = static_cast<Jarvis *>(_o);
        switch (_id) {
        case 0: _t->setSettings((*reinterpret_cast< VoiceSettingsDialog::Settings*(*)>(_a[1]))); break;
        case 1: _t->onVoiceRecognized((*reinterpret_cast< PXCVoiceRecognition::Recognition*(*)>(_a[1]))); break;
        case 2: _t->prepareToQuit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VoiceSettingsDialog::Settings* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Jarvis::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Jarvis.data,
      qt_meta_data_Jarvis,  qt_static_metacall, 0, 0}
};


const QMetaObject *Jarvis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Jarvis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Jarvis.stringdata))
        return static_cast<void*>(const_cast< Jarvis*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Jarvis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
