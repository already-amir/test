/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <quickstudiocsvtablemodel.h>
#include <quickstudiofilereader.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_QtQuick_Studio_Utils()
{
    qmlRegisterModule("QtQuick.Studio.Utils", 1, 0);
    qmlRegisterModule("QtQuick.Studio.Utils", 1, 254);
    qmlRegisterModule("QtQuick.Studio.Utils", 254, 0);
    QMetaType::fromType<QAbstractItemModel *>().id();
    QMetaType::fromType<QAbstractTableModel *>().id();
    qmlRegisterTypesAndRevisions<QuickStudioCsvTableModel>("QtQuick.Studio.Utils", 254);
    qmlRegisterTypesAndRevisions<QuickStudioFileReader>("QtQuick.Studio.Utils", 254);
    qmlRegisterModule("QtQuick.Studio.Utils", 254, 254);
}

static const QQmlModuleRegistration registration("QtQuick.Studio.Utils", qml_register_types_QtQuick_Studio_Utils);
