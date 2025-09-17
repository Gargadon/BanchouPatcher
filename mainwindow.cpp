#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QTranslator>
#include <QSettings>
#include <QRegularExpression>
#include "acerca.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(std::make_unique<Ui::MainWindow>()),
    patchGenerator(new PatchGenerator(this))
{
    ui->setupUi(this);
    loadSettings();

    // Modern Qt6 signal/slot connections
    connect(patchGenerator, &PatchGenerator::patchProgress,
            this, &MainWindow::onPatchProgress);
    connect(patchGenerator, &PatchGenerator::patchCompleted,
            this, &MainWindow::onPatchCompleted);
    connect(patchGenerator, &PatchGenerator::errorOccurred,
            this, &MainWindow::onPatchError);
}

void MainWindow::saveSettings()
{
    QSettings setting("Gargadon","BanchouPatcher");
    setting.beginGroup("MainWindow");
    if(lang.isEmpty())
    {
        setting.setValue("lang","en");
    }
    else {
        setting.setValue("lang",lang);
    }
    setting.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings setting("Gargadon","BanchouPatcher");
    setting.beginGroup("MainWindow");

    // Aqui cargamos el idioma
    QString loadlang = QVariant(setting.value("lang")).toString();
    if(loadlang == "en")
    {
        on_actionIngl_s_triggered();
    }
    else if (loadlang == "es") {
        on_actionEspa_ol_triggered();
    }
    else {
        on_actionIngl_s_triggered();
    }
}


MainWindow::~MainWindow() = default;

void MainWindow::on_OrigenBoton_clicked()
{
    ui->Origen->clear();
    const QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Abrir archivo de origen"),
                                                                ui->Origen->toPlainText(),
                                                                tr("Todos los archivos (*.*)"));
    if (!fileNames.isEmpty()) {
        for (const auto &fileName : fileNames) {
            ui->Origen->append(fileName);
        }
    }
}

void MainWindow::on_DestinoBoton_clicked()
{
    ui->Destino->clear();
    const QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Abrir archivo de destino"),
                                                                ui->Destino->toPlainText(),
                                                                tr("Todos los archivos (*.*)"));
    if (!fileNames.isEmpty()) {
        for (const auto &fileName : fileNames) {
            ui->Destino->append(fileName);
        }
    }
}

void MainWindow::on_DirectorioBoton_clicked()
{
    const QString dirName = QFileDialog::getExistingDirectory(this, tr("Seleccione el directorio para guardar"),
                                                              ui->Directorio->text());
    if (!dirName.isEmpty()) {
        ui->Directorio->setText(dirName);
    }
}


void MainWindow::on_patchNow_clicked()
{
    PatchGenerator::PatchParams params = getPatchParams();
    patchGenerator->generatePatches(params);
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    Acerca acerca;
    acerca.setModal(true);
    acerca.exec();
}

void MainWindow::on_actionIngl_s_triggered()
{
    QTranslator *qtTranslator = new QTranslator();
    QString file_translator = ":/translations/english.qm";
    if (qtTranslator->load(file_translator)) {
        qApp->installTranslator(qtTranslator);
    }
    ui->retranslateUi(this);
    lang = "en";
    saveSettings();
}

void MainWindow::on_actionEspa_ol_triggered()
{
    QTranslator *qtTraductor = new QTranslator();
    QString file_translator = ":/translations/spanish.qm";
    if (qtTraductor->load(file_translator)) {
        qApp->installTranslator(qtTraductor);
    }
    ui->retranslateUi(this);
    lang = "es";
    saveSettings();
}

PatchGenerator::PatchParams MainWindow::getPatchParams()
{
    PatchGenerator::PatchParams params;

    QString sourceText = ui->Origen->toPlainText();
    params.sourceFiles = sourceText.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);

    QString targetText = ui->Destino->toPlainText();
    params.targetFiles = targetText.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);

    params.outputDirectory = ui->Directorio->text();
    params.patchPrefix = ui->Parche->text();
    params.compress = ui->Comprimir->isChecked();

    return params;
}

void MainWindow::onPatchProgress(int current, int total)
{
    Q_UNUSED(current);
    Q_UNUSED(total);
    // Aquí se puede implementar una barra de progreso si se desea
    // Por ahora no hace nada, pero está preparado para futuras mejoras
}

void MainWindow::onPatchCompleted()
{
    QMessageBox::information(this, tr("Éxito"),
                           tr("Los parches han sido creados satisfactoriamente."));
}

void MainWindow::onPatchError(const QString &error)
{
    QMessageBox::critical(this, tr("Error"), error);
}
