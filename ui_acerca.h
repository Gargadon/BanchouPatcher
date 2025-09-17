/********************************************************************************
** Form generated from reading UI file 'acerca.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACERCA_H
#define UI_ACERCA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Acerca
{
public:
    QTextEdit *textEdit;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *paypal;
    QPushButton *myweb;

    void setupUi(QDialog *Acerca)
    {
        if (Acerca->objectName().isEmpty())
            Acerca->setObjectName("Acerca");
        Acerca->resize(544, 300);
        textEdit = new QTextEdit(Acerca);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(160, 10, 371, 241));
        textEdit->setReadOnly(true);
        label = new QLabel(Acerca);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 141, 251));
#if QT_CONFIG(whatsthis)
        label->setWhatsThis(QString::fromUtf8(""));
#endif // QT_CONFIG(whatsthis)
        pushButton = new QPushButton(Acerca);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(160, 260, 84, 30));
        paypal = new QPushButton(Acerca);
        paypal->setObjectName("paypal");
        paypal->setGeometry(QRect(265, 260, 121, 30));
        myweb = new QPushButton(Acerca);
        myweb->setObjectName("myweb");
        myweb->setGeometry(QRect(410, 260, 121, 30));

        retranslateUi(Acerca);

        QMetaObject::connectSlotsByName(Acerca);
    } // setupUi

    void retranslateUi(QDialog *Acerca)
    {
        Acerca->setWindowTitle(QCoreApplication::translate("Acerca", "Acerca de", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Acerca", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Inter'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Noto Sans';\">BanchouPatcher es un asistente de asignaci\303\263n de parches para archivos que utiliza xdelta3 para trabajar.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; marg"
                        "in-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Noto Sans';\">La versi\303\263n 4 ahora utiliza Qt6 y las compresiones nativas zip de cada sistema operativo.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Noto Sans';\">BanchouPatcher est\303\241 liberado bajo la licencia GPLv3, la cual se incluye en el c\303\263digo fuente de este software.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span s"
                        "tyle=\" font-family:'Noto Sans';\">Puedes colaborar con la mejora de BanchouPatcher entrando a cualquiera de las siguientes direcciones:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Noto Sans';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Noto Sans';\">-Gargadon's Dungeon: </span><a href=\"http://www.gargadon.com/\"><span style=\" font-family:'Noto Sans'; text-decoration: underline; color:#0057ae;\">http://www.gargadon.com/</span></a></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Noto Sans';\">-GitHub: </span><a href=\"https://github.com/Gargadon/BanchouPatcher\"><span style=\" font-family:'Noto Sans'; text-decoration: underline; color:#0057ae;\">https://git"
                        "hub.com/Gargadon/BanchouPatcher</span></a></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Noto Sans';\">-Correo electr\303\263nico: </span><a href=\"mailto:dkantun@gmail.com\"><span style=\" font-family:'Noto Sans'; text-decoration: underline; color:#0057ae;\">dkantun@gmail.com</span></a></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("Acerca", "<html><head/><body><p><img src=\":/files/musashi-miyamoto-sw.jpg\"/></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("Acerca", "OK", nullptr));
        paypal->setText(QCoreApplication::translate("Acerca", "Donar v\303\255a PayPal", nullptr));
        myweb->setText(QCoreApplication::translate("Acerca", "Ir a mi sitio web", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Acerca: public Ui_Acerca {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACERCA_H
