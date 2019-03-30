#include "acerca.h"
#include "ui_acerca.h"
#include <QDesktopServices>

Acerca::Acerca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acerca)
{
    ui->setupUi(this);
}

Acerca::~Acerca()
{
    delete ui;
}

void Acerca::on_pushButton_clicked()
{
    close();
}

void Acerca::on_paypal_clicked()
{
    QString link = "https://paypal.me/gargadon";
    QDesktopServices::openUrl(QUrl(link));
}

void Acerca::on_myweb_clicked()
{
    QString link = "https://www.gargadon.info/";
    QDesktopServices::openUrl(QUrl(link));
}
