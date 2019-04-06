#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_OrigenBoton_clicked();

    void on_DestinoBoton_clicked();

    void on_DirectorioBoton_clicked();

    void on_patchNow_clicked();

    void on_actionSalir_triggered();

    void on_actionAcerca_de_triggered();

    void on_actionIngl_s_triggered();

    void on_actionEspa_ol_triggered();

private:
    Ui::MainWindow *ui;

    void loadSettings();

    void saveSettings();

    QString lang;
};

#endif // MAINWINDOW_H
