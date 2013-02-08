/****************************************************************************
** Meta object code from reading C++ file 'MCMNotification.hpp'
**
** Created: Fri Feb 1 11:11:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/malcomLib/MCMNotification.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MCMNotification.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MCMNotification[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      57,   16,   16,   16, 0x0a,
     118,  105,   16,   16, 0x0a,
     181,  174,   16,   16, 0x0a,
     230,  174,   16,   16, 0x0a,
     281,  174,   16,   16, 0x0a,
     342,  336,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MCMNotification[] = {
    "MCMNotification\0\0"
    "handleInvoke(bb::system::InvokeRequest)\0"
    "createSessionCompleted(bb::network::PushStatus)\0"
    "status,token\0"
    "createChannelCompleted(bb::network::PushStatus,QString)\0"
    "status\0destroyChannelCompleted(bb::network::PushStatus)\0"
    "registerToLaunchCompleted(bb::network::PushStatus)\0"
    "unregisterFromLaunchCompleted(bb::network::PushStatus)\0"
    "reply\0registerFinished(QNetworkReply*)\0"
};

void MCMNotification::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MCMNotification *_t = static_cast<MCMNotification *>(_o);
        switch (_id) {
        case 0: _t->handleInvoke((*reinterpret_cast< const bb::system::InvokeRequest(*)>(_a[1]))); break;
        case 1: _t->createSessionCompleted((*reinterpret_cast< const bb::network::PushStatus(*)>(_a[1]))); break;
        case 2: _t->createChannelCompleted((*reinterpret_cast< const bb::network::PushStatus(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->destroyChannelCompleted((*reinterpret_cast< const bb::network::PushStatus(*)>(_a[1]))); break;
        case 4: _t->registerToLaunchCompleted((*reinterpret_cast< const bb::network::PushStatus(*)>(_a[1]))); break;
        case 5: _t->unregisterFromLaunchCompleted((*reinterpret_cast< const bb::network::PushStatus(*)>(_a[1]))); break;
        case 6: _t->registerFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MCMNotification::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MCMNotification::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MCMNotification,
      qt_meta_data_MCMNotification, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MCMNotification::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MCMNotification::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MCMNotification::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MCMNotification))
        return static_cast<void*>(const_cast< MCMNotification*>(this));
    return QObject::qt_metacast(_clname);
}

int MCMNotification::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
