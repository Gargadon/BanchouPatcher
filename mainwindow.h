#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <memory>
#include "patchgenerator.h"

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

private slots:
    void onPatchProgress(int current, int total);
    void onPatchCompleted();
    void onPatchError(const QString &error);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    PatchGenerator *patchGenerator;

    void loadSettings();
    void saveSettings();
    PatchGenerator::PatchParams getPatchParams();

    QString lang;
};

#endif // MAINWINDOW_H
