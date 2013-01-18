/****************************************************************************
** Meta object code from reading C++ file 'MCMStats.hpp'
**
** Created: Fri Jan 18 18:20:45 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/malcomLib/MCMStats.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MCMStats.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MCMStats[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      44,   10,    9,    9, 0x05,
      96,   76,    9,    9, 0x25,

 // slots: signature, parameters, type, tag, flags
     126,  120,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MCMStats[] = {
    "MCMStats\0\0registrationSuccess,resultMessage\0"
    "sendBeaconnResult(bool,QString)\0"
    "registrationSuccess\0sendBeaconnResult(bool)\0"
    "reply\0sendBeaconFinished(QNetworkReply*)\0"
};

void MCMStats::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MCMStats *_t = static_cast<MCMStats *>(_o);
        switch (_id) {
        case 0: _t->sendBeaconnResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sendBeaconnResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sendBeaconFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MCMStats::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MCMStats::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MCMStats,
      qt_meta_data_MCMStats, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MCMStats::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MCMStats::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MCMStats::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MCMStats))
        return static_cast<void*>(const_cast< MCMStats*>(this));
    return QObject::qt_metacast(_clname);
}

int MCMStats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MCMStats::sendBeaconnResult(bool _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
