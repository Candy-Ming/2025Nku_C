/****************************************************************************
** Meta object code from reading C++ file 'mazewidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mazewidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mazewidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSmazeWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSmazeWidgetENDCLASS = QtMocHelpers::stringData(
    "mazeWidget",
    "on_start_btn_clicked",
    "",
    "on_stop_ptn_clicked",
    "on_end_btn_clicked",
    "on_rule_btn_clicked",
    "on_setting_btn_clicked",
    "on_solve_btn_clicked",
    "time_update",
    "dogAnimationUpdate"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSmazeWidgetENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[11];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[19];
    char stringdata5[20];
    char stringdata6[23];
    char stringdata7[21];
    char stringdata8[12];
    char stringdata9[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSmazeWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSmazeWidgetENDCLASS_t qt_meta_stringdata_CLASSmazeWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "mazeWidget"
        QT_MOC_LITERAL(11, 20),  // "on_start_btn_clicked"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 19),  // "on_stop_ptn_clicked"
        QT_MOC_LITERAL(53, 18),  // "on_end_btn_clicked"
        QT_MOC_LITERAL(72, 19),  // "on_rule_btn_clicked"
        QT_MOC_LITERAL(92, 22),  // "on_setting_btn_clicked"
        QT_MOC_LITERAL(115, 20),  // "on_solve_btn_clicked"
        QT_MOC_LITERAL(136, 11),  // "time_update"
        QT_MOC_LITERAL(148, 18)   // "dogAnimationUpdate"
    },
    "mazeWidget",
    "on_start_btn_clicked",
    "",
    "on_stop_ptn_clicked",
    "on_end_btn_clicked",
    "on_rule_btn_clicked",
    "on_setting_btn_clicked",
    "on_solve_btn_clicked",
    "time_update",
    "dogAnimationUpdate"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSmazeWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    0,   66,    2, 0x08,    5 /* Private */,
       7,    0,   67,    2, 0x08,    6 /* Private */,
       8,    0,   68,    2, 0x08,    7 /* Private */,
       9,    0,   69,    2, 0x08,    8 /* Private */,

 // slots: parameters
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

Q_CONSTINIT const QMetaObject mazeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSmazeWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSmazeWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSmazeWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<mazeWidget, std::true_type>,
        // method 'on_start_btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_stop_ptn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_end_btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_rule_btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_setting_btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_solve_btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'time_update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dogAnimationUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void mazeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mazeWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_start_btn_clicked(); break;
        case 1: _t->on_stop_ptn_clicked(); break;
        case 2: _t->on_end_btn_clicked(); break;
        case 3: _t->on_rule_btn_clicked(); break;
        case 4: _t->on_setting_btn_clicked(); break;
        case 5: _t->on_solve_btn_clicked(); break;
        case 6: _t->time_update(); break;
        case 7: _t->dogAnimationUpdate(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *mazeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mazeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSmazeWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int mazeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    }
    return _id;
}
QT_WARNING_POP
