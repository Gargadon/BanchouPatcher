#-------------------------------------------------
#
# Project created by QtCreator 2019-03-30T13:44:26
# Migrated to Qt6 2025
#
#-------------------------------------------------

QT += core gui widgets

TARGET = BanchouPatcher
TEMPLATE = app
VERSION = 4.0.0

# Qt6 specific configuration
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Modern C++ standard
CONFIG += c++17 static

# Qt6 minimum version requirement
lessThan(QT_MAJOR_VERSION, 6): error("This project requires Qt 6.0 or later")

# Include Qt6 private headers for QZipWriter
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore/$$[QT_VERSION]/QtCore

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        acerca.cpp \
        patchgenerator.cpp

HEADERS += \
        mainwindow.h \
        acerca.h \
        patchgenerator.h

FORMS += \
        mainwindow.ui \
    acerca.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target

icono.path = /usr/share/icons/hicolor/256x256/apps
icono.files = BanchouPatcher.png
INSTALLS += icono

escritorio.path = /usr/share/applications
escritorio.files = BanchouPatcher.desktop
INSTALLS += escritorio

RESOURCES += \
    resources.qrc

RC_ICONS = icons/icon.ico

TRANSLATIONS += translations/spanish.ts \
                translations/english.ts

# Configure lupdate and lrelease for Qt6
CONFIG += lrelease
CONFIG += embed_translations
QM_FILES_INSTALL_PATH = /usr/share/$$TARGET/translations
