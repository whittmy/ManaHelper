/****************************************************************************
** Meta object code from reading C++ file 'newdownloadinfodialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialogs/newdownloadinfodialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newdownloadinfodialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NewDownloadInfoDialog_t {
    QByteArrayData data[9];
    char stringdata[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NewDownloadInfoDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NewDownloadInfoDialog_t qt_meta_stringdata_NewDownloadInfoDialog = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 29),
QT_MOC_LITERAL(2, 52, 0),
QT_MOC_LITERAL(3, 53, 23),
QT_MOC_LITERAL(4, 77, 23),
QT_MOC_LITERAL(5, 101, 34),
QT_MOC_LITERAL(6, 136, 5),
QT_MOC_LITERAL(7, 142, 23),
QT_MOC_LITERAL(8, 166, 18)
    },
    "NewDownloadInfoDialog\0"
    "on_browseSaveToButton_clicked\0\0"
    "on_pushButton_4_clicked\0on_pushButton_2_clicked\0"
    "on_categoryBox_currentIndexChanged\0"
    "index\0on_pushButton_3_clicked\0"
    "insertANewDownload\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewDownloadInfoDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08,
       3,    0,   45,    2, 0x08,
       4,    0,   46,    2, 0x08,
       5,    1,   47,    2, 0x08,
       7,    0,   50,    2, 0x08,
       8,    0,   51,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void NewDownloadInfoDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewDownloadInfoDialog *_t = static_cast<NewDownloadInfoDialog *>(_o);
        switch (_id) {
        case 0: _t->on_browseSaveToButton_clicked(); break;
        case 1: _t->on_pushButton_4_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_categoryBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: { int _r = _t->insertANewDownload();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject NewDownloadInfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewDownloadInfoDialog.data,
      qt_meta_data_NewDownloadInfoDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *NewDownloadInfoDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewDownloadInfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewDownloadInfoDialog.stringdata))
        return static_cast<void*>(const_cast< NewDownloadInfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewDownloadInfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
