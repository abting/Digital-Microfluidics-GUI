/****************************************************************************
** Meta object code from reading C++ file 'layout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../layout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Layout_t {
    QByteArrayData data[7];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Layout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Layout_t qt_meta_stringdata_Layout = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Layout"
QT_MOC_LITERAL(1, 7, 7), // "Lsignal"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "Droplet*"
QT_MOC_LITERAL(4, 25, 5), // "nDrop"
QT_MOC_LITERAL(5, 31, 1), // "l"
QT_MOC_LITERAL(6, 33, 1) // "a"

    },
    "Layout\0Lsignal\0\0Droplet*\0nDrop\0l\0a"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Layout[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void Layout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Layout *_t = static_cast<Layout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Lsignal((*reinterpret_cast< Droplet*(*)>(_a[1]))); break;
        case 1: _t->l((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Layout::*_t)(Droplet * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Layout::Lsignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Layout::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Layout::l)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Layout::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Layout.data,
      qt_meta_data_Layout,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Layout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Layout::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Layout.stringdata0))
        return static_cast<void*>(const_cast< Layout*>(this));
    return QObject::qt_metacast(_clname);
}

int Layout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Layout::Lsignal(Droplet * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Layout::l(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
