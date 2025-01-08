!versionAtLeast(QT_VERSION, 5.15.0):error("Requires Qt version 5.15.0 or greater.")

TEMPLATE +=app
TARGET = KNetStats

QT       += core multimedia 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

DEFINES += VERSION_STR=\\\"$$cat(version.txt)\\\"
DEFINES += PACKAGE_NAME_STR=\\\"$$cat(package_name.txt)\\\"

DEFINES += QT_DEPRECATED_WARNINGS

# QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII
#don't use precompiled headers https://www.kdab.com/beware-of-qt-module-wide-includes/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
            src/chart.cpp \
            src/configure.cpp \
            src/knetstats.cpp \
            src/knetstatsview.cpp \
            src/main.cpp  \
  src/statistics.cpp

FORMS = src/configurebase.ui \
  src/statisticsbase.ui
#Translate
TRANSLATIONS = res/i18n/$${TARGET}_en.ts \
               res/i18n/$${TARGET}_ru.ts

RESOURCES += \
            knetstats.qrc \

lupdate_only {
    #SOURCES +=  \
}


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD/res/qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/res/qml
QML2_IMPORT_PATH = $$PWD/res/qml

FORMS += \
  src/configurebase.ui

HEADERS += \
  src/chart.h \
  src/configure.h \
  src/knetstats.h \
  src/knetstatsview.h \
  src/statistics.h


