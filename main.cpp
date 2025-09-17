#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configure application metadata
    a.setApplicationName("BanchouPatcher");
    a.setApplicationVersion("4.0.0");
    a.setOrganizationName("David Kantun");

    // Load translations
    QTranslator translator;
    QString locale = QLocale::system().name();

    // Try to load embedded translations first
    if (locale.startsWith("en")) {
        if (translator.load(":/translations/english.qm")) {
            a.installTranslator(&translator);
        }
    } else if (locale.startsWith("es")) {
        if (translator.load(":/translations/spanish.qm")) {
            a.installTranslator(&translator);
        }
    }

    // Fallback: try to load from file system
    if (translator.isEmpty()) {
        QString translationPath = QDir::currentPath() + "/translations/";
        bool loaded = false;
        if (locale.startsWith("en")) {
            loaded = translator.load("english.qm", translationPath);
        } else if (locale.startsWith("es")) {
            loaded = translator.load("spanish.qm", translationPath);
        }
        if (loaded) {
            a.installTranslator(&translator);
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
