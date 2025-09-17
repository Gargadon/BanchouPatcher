/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAcerca_de;
    QAction *actionSalir;
    QAction *actionEspa_ol;
    QAction *actionIngl_s;
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *OrigenBoton;
    QLabel *label_2;
    QPushButton *DestinoBoton;
    QLineEdit *Directorio;
    QLabel *label_3;
    QPushButton *DirectorioBoton;
    QLabel *label_4;
    QLineEdit *Parche;
    QPushButton *patchNow;
    QCheckBox *Comprimir;
    QTextEdit *Origen;
    QTextEdit *Destino;
    QMenuBar *menuBar;
    QMenu *menuAyuda;
    QMenu *menuIdioma;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(684, 450);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        actionAcerca_de = new QAction(MainWindow);
        actionAcerca_de->setObjectName("actionAcerca_de");
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName("actionSalir");
        actionEspa_ol = new QAction(MainWindow);
        actionEspa_ol->setObjectName("actionEspa_ol");
        actionEspa_ol->setCheckable(false);
        actionIngl_s = new QAction(MainWindow);
        actionIngl_s->setObjectName("actionIngl_s");
        actionIngl_s->setCheckable(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 17, 601, 21));
        label->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        OrigenBoton = new QPushButton(centralWidget);
        OrigenBoton->setObjectName("OrigenBoton");
        OrigenBoton->setGeometry(QRect(633, 40, 31, 30));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 77, 601, 21));
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        DestinoBoton = new QPushButton(centralWidget);
        DestinoBoton->setObjectName("DestinoBoton");
        DestinoBoton->setGeometry(QRect(633, 100, 31, 30));
        Directorio = new QLineEdit(centralWidget);
        Directorio->setObjectName("Directorio");
        Directorio->setGeometry(QRect(20, 160, 601, 28));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 137, 591, 21));
        label_3->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        DirectorioBoton = new QPushButton(centralWidget);
        DirectorioBoton->setObjectName("DirectorioBoton");
        DirectorioBoton->setGeometry(QRect(633, 160, 31, 30));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 197, 591, 21));
        label_4->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        Parche = new QLineEdit(centralWidget);
        Parche->setObjectName("Parche");
        Parche->setGeometry(QRect(20, 220, 601, 28));
        patchNow = new QPushButton(centralWidget);
        patchNow->setObjectName("patchNow");
        patchNow->setGeometry(QRect(230, 320, 221, 71));
        QFont font;
        font.setPointSize(14);
        patchNow->setFont(font);
        Comprimir = new QCheckBox(centralWidget);
        Comprimir->setObjectName("Comprimir");
        Comprimir->setGeometry(QRect(20, 270, 601, 24));
        Comprimir->setChecked(true);
        Origen = new QTextEdit(centralWidget);
        Origen->setObjectName("Origen");
        Origen->setGeometry(QRect(20, 40, 601, 31));
        Destino = new QTextEdit(centralWidget);
        Destino->setObjectName("Destino");
        Destino->setGeometry(QRect(20, 100, 601, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 684, 21));
        menuAyuda = new QMenu(menuBar);
        menuAyuda->setObjectName("menuAyuda");
        menuIdioma = new QMenu(menuBar);
        menuIdioma->setObjectName("menuIdioma");
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuAyuda->menuAction());
        menuBar->addAction(menuIdioma->menuAction());
        menuAyuda->addAction(actionAcerca_de);
        menuAyuda->addAction(actionSalir);
        menuIdioma->addAction(actionEspa_ol);
        menuIdioma->addAction(actionIngl_s);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BanchouPatcher", nullptr));
        actionAcerca_de->setText(QCoreApplication::translate("MainWindow", "Acerca de...", nullptr));
#if QT_CONFIG(shortcut)
        actionAcerca_de->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
#if QT_CONFIG(shortcut)
        actionSalir->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEspa_ol->setText(QCoreApplication::translate("MainWindow", "Espa\303\261ol", nullptr));
        actionIngl_s->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Archivos de origen", nullptr));
        OrigenBoton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Archivos de destino", nullptr));
        DestinoBoton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Directorio", nullptr));
        DirectorioBoton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Prefijo del parche", nullptr));
        patchNow->setText(QCoreApplication::translate("MainWindow", "PATCH!!!1", nullptr));
        Comprimir->setText(QCoreApplication::translate("MainWindow", "Comprimir en .zip y eliminar archivos intermedios", nullptr));
        menuAyuda->setTitle(QCoreApplication::translate("MainWindow", "Ayuda", nullptr));
        menuIdioma->setTitle(QCoreApplication::translate("MainWindow", "Idioma", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
