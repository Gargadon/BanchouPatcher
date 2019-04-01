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
    QStringList fileName = QFileDialog::getOpenFileNames(this,tr("Abrir archivo de origen"),
                                                    ui->Origen->toPlainText(),
                                                    tr("Todos los archivos (*.*)"));
    if(!fileName.isEmpty()){
    for(auto &data :fileName)
        ui->Origen->append(data);
    }
}

void MainWindow::on_DestinoBoton_clicked()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this,tr("Abrir archivo de destino"),
                                                    ui->Destino->toPlainText(),
                                                    tr("Todos los archivos (*.*)"));
    if(!fileName.isEmpty()){
    for(auto &data :fileName)
        ui->Destino->append(data);
    }
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
    QString origen2 = ui->Origen->toPlainText();
    QStringList origen = origen2.split(QRegExp("[\n]"),QString::SkipEmptyParts);

    QString destino2 = ui->Destino->toPlainText();
    QStringList destino = destino2.split(QRegExp("[\n]"),QString::SkipEmptyParts);

    QString directorio = ui->Directorio->text();
    QString PrefijoParche = ui->Parche->text();

    // Banderilla
    int exito = 0;

    // Si origen = destino, se hace el if, si no, else
    if(destino.count() == origen.count())
    {
        int final = destino.count();
        for(int i=0;i<final;i++)
        {
            bool a = QFile::exists(origen[i]);
            bool b = QFile::exists(destino[i]);
            bool c = QDir(directorio).exists();
            bool d = !PrefijoParche.isEmpty();

            int total = a+b+c+d;

            if(total == 4)
            {
                // PrefijoParche debe tener un identificador
                // pero solo si hay más de un archivo a parchear
                QString PrefijoParche2;
                if(final>1)
                {
                    QString prefijo = QString::number(i+1);
                    PrefijoParche2 = PrefijoParche;
                    PrefijoParche = PrefijoParche + "-" + prefijo;
                }
                // Tomamos solo el nombre del archivo
                QFile f(origen[i]);
                QString NombreOrigen = f.fileName();
                QFile g(destino[i]);
                QString NombreDestino = g.fileName();

                // Se crean los strings que iran a los archivos y scripts
                QString TextoLeeme = "MUY IMPORTANTE\n\nUsuarios de Windows:\nCopien el archivo a parchar y ejecuten el .bat que viene incluido.\n\nUsuarios de Linux:\nAsegúrense de tener instalada en su distribución el paquete xdelta3. Una vez revisado este punto, copien el archivo a parchar y ejecuten el script en Bash que viene incluido.\n\nUsuarios de Mac:\nNo hay solución por el momento.";

                QString TextoWindows = "@echo off\necho  Archivo generado por BanchouPatcher.\necho  Archivo de origen: \"" + NombreOrigen + "\"\necho  Archivo de destino: \"" + NombreDestino + "\"\nxdelta3 -d -s" + " \"" + NombreOrigen + "\"" + " \"" + PrefijoParche + ".vcdiff\"" + " \"" + NombreDestino + "\"\necho  Borrando archivos intermedios...\ndel \"" + PrefijoParche + ".vcdiff\"\ndel \"" + PrefijoParche + ".bat\"\ndel \"" + PrefijoParche + "\"\ndel \"" + "xdelta3.exe\"\ndel \"leeme.txt\"\npause";

                QString TextoLinux = "#!/bin/bash\necho \" Archivo generado por BanchouPatcher.\"\necho \" Archivo de origen: " + NombreOrigen + "\"\necho \" Archivo de destino: " + NombreDestino + "\"\nxdelta3 -d -s" + " \"" + NombreOrigen + "\"" + " \"" + PrefijoParche + ".vcdiff\"" + " \"" + NombreDestino + "\"\nif [ \"$?\" = \"0\" ]\nthen\n echo \" Parche aplicado correctamente.\" \n echo \" Borrando archivos intermedios...\" \n rm \"" + PrefijoParche + ".vcdiff\"\n rm \"" + PrefijoParche + ".bat\"\n rm \"" + PrefijoParche + "\"\n rm \"xdelta3.exe\"\n rm \"leeme.txt\" \nelse\n echo \" Ups, algo salió mal. Revisa el nombre de los archivos y que se encuentren en el mismo directorio.\"\nfi ";

                // Creamos el directorio temporal

                QString tempDir = directorio + "/" + PrefijoParche;

                QDir().mkdir(tempDir);

                QString vcdiff = tempDir + "/" + PrefijoParche + ".vcdiff";

                // Copiamos xdelta3.exe
                QString Origendelta = ":/files/xdelta3.exe";
                QString Destinodelta = tempDir + "/xdelta3.exe";
                QFile::copy(Origendelta,Destinodelta);

                // Determinamos si es Windows o Linux
                QSysInfo osname;
                QString os = osname.productType();

                // Creamos el parche
                QString xdelta;
                if(os=="windows")
                {
                    xdelta = Destinodelta;
                }
                else
                {
                    xdelta = "xdelta3";
                }
                QStringList argumentos;
                argumentos<<"-e"<<"-s"<<origen[i]<<destino[i]<<vcdiff;
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

                bool checkedzip = ui->Comprimir->isChecked();

                if(checkedzip==true)
                {
                    // Nombre del zip
                    QString nombrezip = directorio + "/" + PrefijoParche + ".zip";

                    // Creamos el zip
                    QString zip;
                    if(os=="windows")
                    {
                        QString Origenzip = ":/files/zip.exe";
                        QString Destinozip = tempDir + "/zip.exe";
                        QFile::copy(Origenzip,Destinozip);
                        zip = Destinozip;
                    }
                    else {
                        zip = "zip";
                    }
                    QStringList argumentos;
                    argumentos<<"-j"<<nombrezip<<vcdiff<<ScriptLinux<<ScriptWindows<<Leeme<<Destinodelta;
                    QProcess *myProcess = new QProcess(parent());
                    myProcess->start(zip, argumentos);
                    myProcess->waitForFinished(-1);

                    // Borramos el directorio temporal
                    QDir dir(tempDir);
                    dir.removeRecursively();

                }
                if(final>1)
                PrefijoParche = PrefijoParche2;
                exito = 1;

            }
            else {
                QMessageBox MSGBOX;
                MSGBOX.critical(this,tr("Error"),
                                tr("Uno o más parámetros son inválidos. Revise los campos y corríjalos."));
                exito = 0;
            }
        }
        if(exito == 1)
        {
            QString Mensaje = "Los parches han sido creados satisfactoriamente.";
            QMessageBox MSGBOX;
            MSGBOX.setText(Mensaje);
            MSGBOX.exec();
        }
    }
    else
    {
        QMessageBox MSGBOX;
        MSGBOX.critical(this,tr("Error"),
                        tr("La cantidad de archivos de origen es distinta a la de archivos destino.\n\nSeleccione los archivos nuevamente."));
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
