!versionAtLeast(QT_VERSION, 5.15.0):error("Requires Qt version 5.15.0 or greater.")

TEMPLATE +=app
TARGET = knetstats

QT       += core qml quick quickcontrols2 svg network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += bump_version
CONFIG += c++17
CONFIG += resources_big
CONFIG(release,debug|release):CONFIG += qtquickcompiler # Qt Quick compiler
CONFIG(debug,debug|release):CONFIG += qml_debug  # Add qml_debug

DEFINES += VERSION_STR=\\\"$$cat(version.txt)\\\"
DEFINES += PACKAGE_NAME_STR=\\\"$$cat(package_name.txt)\\\"
DEFINES += APP_NAME_STR=\\\"$$cat(app_name.txt)\\\"
DEFINES += QT_DEPRECATED_WARNINGS

# QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII
#don't use precompiled headers https://www.kdab.com/beware-of-qt-module-wide-includes/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
        src/hal.h

SOURCES += \
            src/hal.cpp \
            src/main.cpp
            src/main.cpp 
RESOURCES += \
        images.qrc \
        qml.qrc \
        fonts.qrc #i18n.qrc

#Translate
#TRANSLATIONS = res/i18n/$${TARGET}_en.ts \
#               res/i18n/$${TARGET}_ru.ts

lupdate_only {
    SOURCES +=  \
        res/qml/*.qml \
        res/qml/common/*.qml \
}


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD/res/qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/res/qml
QML2_IMPORT_PATH = $$PWD/res/qml

bump_version{
    message("Bump or update App version")
    system($$PWD/tools/ci/bump_ver.sh)
}



