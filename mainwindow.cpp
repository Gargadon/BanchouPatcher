#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include "acerca.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_OrigenBoton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo de origen"),
                                                    ui->Origen->text(),
                                                    tr("Todos los archivos (*.*)"));
    if(!fileName.isEmpty())
        ui->Origen->setText(fileName);
}

void MainWindow::on_DestinoBoton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo de destino"),
                                                    ui->Destino->text(),
                                                    tr("Todos los archivos (*.*)"));
    if(!fileName.isEmpty())
        ui->Destino->setText(fileName);
}

void MainWindow::on_DirectorioBoton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this,tr("Seleccione el directorio para guardar"),
                                                        ui->Directorio->text());
    if(!dirName.isEmpty())
        ui->Directorio->setText(dirName);
}


void MainWindow::on_patchNow_clicked()
{
    // Obtenemos los nombres de las variables
    QString origen = ui->Origen->text();
    QString destino = ui->Destino->text();
    QString directorio = ui->Directorio->text();
    QString PrefijoParche = ui->Parche->text();

    bool a = QFile::exists(origen);
    bool b = QFile::exists(destino);
    bool c = QDir(directorio).exists();
    bool d = !PrefijoParche.isEmpty();

    int total = a+b+c+d;

    if(total == 4)
    {
        // Tomamos solo el nombre del archivo
        QFile f(origen);
        QString NombreOrigen = f.fileName();
        QFile g(destino);
        QString NombreDestino = g.fileName();

        // Se crean los strings que iran a los archivos y scripts
        QString TextoLeeme = "MUY IMPORTANTE\n\nUsuarios de Windows:\nCopien el archivo a parchar y ejecuten el .bat que viene incluido.\n\nUsuarios de Linux:\nAsegúrense de tener instalada en su distribución el paquete xdelta3. Una vez revisado este punto, copien el archivo a parchar y ejecuten el script en Bash que viene incluido.\n\nUsuarios de Mac:\nNo hay solución por el momento.";

        QString TextoWindows = "@echo off\necho  Archivo generado por BanchouPatcher.\necho  Archivo de origen: \"" + NombreOrigen + "\"\necho  Archivo de destino: \"" + NombreDestino + "\"\nxdelta3 -d -s" + " \"" + NombreOrigen + "\"" + " \"" + PrefijoParche + ".vcdiff\"" + " \"" + NombreDestino + "\"\necho  Borrando archivos intermedios...\ndel \"" + PrefijoParche + ".vcdiff\"\ndel \"" + PrefijoParche + ".bat\"\ndel \"" + PrefijoParche + "\"\ndel \"" + "xdelta3.exe\"\ndel \"leeme.txt\"\npause";

        QString TextoLinux = "#!/bin/bash\necho \" Archivo generado por BanchouPatcher.\"\necho \" Archivo de origen: " + NombreOrigen + "\"\necho \" Archivo de destino: " + NombreDestino + "\"\nxdelta3 -d -s" + " \"" + NombreOrigen + "\"" + " \"" + PrefijoParche + ".vcdiff\"" + " \"" + NombreDestino + "\"\nif [ \"$?\" = \"0\" ]\nthen\n echo \" Parche aplicado correctamente.\" \n echo \" Borrando archivos intermedios...\" \n rm \"" + PrefijoParche + ".vcdiff\"\n rm \"" + PrefijoParche + ".bat\"\n rm \"" + PrefijoParche + "\"\n rm \"xdelta3.exe\"\n rm \"leeme.txt\" \nelse\n echo \" Ups, algo salió mal. Revisa el nombre de los archivos y que se encuentren en el mismo directorio.\"\nfi ";

        // Creamos el directorio temporal

        QString tempDir = directorio + "/" + PrefijoParche;
        QDir().mkdir(tempDir);

        QString vcdiff = tempDir + "/" + PrefijoParche + ".vcdiff";

        // Creamos el parche
        QString xdelta = "xdelta3";
        QStringList argumentos;
        argumentos<<"-e"<<"-s"<<origen<<destino<<vcdiff;
        QProcess *myProcess = new QProcess(parent());
        myProcess->start(xdelta, argumentos);
        myProcess->waitForFinished(-1);

        // Creamos los scripts

        QString ScriptLinux = tempDir + "/" + PrefijoParche;
        QString ScriptWindows = tempDir + "/" + PrefijoParche + ".bat";
        QString Leeme = tempDir + "/leeme.txt";

        QFile file(ScriptLinux);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << TextoLinux;
        file.close();

        QFile file2(ScriptWindows);
        file2.open(QIODevice::WriteOnly);
        QTextStream stream2(&file2);
        stream2 << TextoWindows;
        file2.close();

        QFile file3(Leeme);
        file3.open(QIODevice::WriteOnly);
        QTextStream stream3(&file3);
        stream3 << TextoLeeme;
        file3.close();

        // Copiamos xdelta3.exe
        QString Origendelta = ":/files/xdelta3.exe";
        QString Destinodelta = tempDir + "/xdelta3.exe";
        QFile::copy(Origendelta,Destinodelta);

        bool checkedzip = ui->Comprimir->isChecked();

        if(checkedzip==true)
        {
            // Nombre del zip
            QString nombrezip = directorio + "/" + PrefijoParche + ".zip";

            // Creamos el zip
            QString zip = "zip";
            QStringList argumentos;
            argumentos<<"-j"<<nombrezip<<vcdiff<<ScriptLinux<<ScriptWindows<<Leeme<<Destinodelta;
            QProcess *myProcess = new QProcess(parent());
            myProcess->start(zip, argumentos);
            myProcess->waitForFinished(-1);

            // Borramos el directorio temporal
            QDir dir(tempDir);
            dir.removeRecursively();

        }

        QString Mensaje = "El parche ha sido creado satisfactoriamente.";
        QMessageBox MSGBOX;
        MSGBOX.setText(Mensaje);
        MSGBOX.exec();

    }
    else {
        QMessageBox MSGBOX;
        MSGBOX.critical(this,tr("Error"),
                        tr("Uno o más parámetros son inválidos. Revise los campos y corríjalos."));
    }

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
