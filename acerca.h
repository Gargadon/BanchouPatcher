#ifndef ACERCA_H
#define ACERCA_H

#include <QDialog>

namespace Ui {
class Acerca;
}

class Acerca : public QDialog
{
    Q_OBJECT

public:
    explicit Acerca(QWidget *parent = nullptr);
    ~Acerca();

private slots:
    void on_pushButton_clicked();

    void on_paypal_clicked();

    void on_myweb_clicked();

private:
    Ui::Acerca *ui;
};

#endif // ACERCA_H
