#include "patchgenerator.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>
#include <QSysInfo>
#include <QStandardPaths>

const QString PatchGenerator::README_TEXT =
    "MUY IMPORTANTE\n\n"
    "Este parche fue generado con BanchouPatcher (GPL-3) compatible con xdelta3.\n\n"
    "Usuarios de Windows:\n"
    "Copien el archivo a parchar y ejecuten el .bat que viene incluido.\n\n"
    "Usuarios de Linux:\n"
    "Asegúrense de tener instalada en su distribución el paquete xdelta3. "
    "Una vez revisado este punto, copien el archivo a parchar y ejecuten el script en Bash que viene incluido.\n\n"
    "Usuarios de Mac:\n"
    "No hay solución por el momento.";

const QString PatchGenerator::WINDOWS_SCRIPT_TEMPLATE =
    "@echo off\n"
    "echo  Archivo generado por BanchouPatcher.\n"
    "echo  Archivo de origen: \"%1\"\n"
    "echo  Archivo de destino: \"%2\"\n"
    "xdelta3 -d -s \"%1\" \"%3.vcdiff\" \"%2\"\n"
    "echo  Borrando archivos intermedios...\n"
    "del \"%3.vcdiff\"\n"
    "del \"%3.bat\"\n"
    "del \"%3\"\n"
    "del \"xdelta3.exe\"\n"
    "del \"leeme.txt\"\n"
    "pause";

const QString PatchGenerator::LINUX_SCRIPT_TEMPLATE =
    "#!/bin/bash\n"
    "echo \" Archivo generado por BanchouPatcher.\"\n"
    "echo \" Archivo de origen: %1\"\n"
    "echo \" Archivo de destino: %2\"\n"
    "xdelta3 -d -s \"%1\" \"%3.vcdiff\" \"%2\"\n"
    "if [ \"$?\" = \"0\" ]\n"
    "then\n"
    " echo \" Parche aplicado correctamente.\" \n"
    " echo \" Borrando archivos intermedios...\" \n"
    " rm \"%3.vcdiff\"\n"
    " rm \"%3.bat\"\n"
    " rm \"%3\"\n"
    " rm \"xdelta3.exe\"\n"
    " rm \"leeme.txt\" \n"
    "else\n"
    " echo \" Ups, algo salió mal. Revisa el nombre de los archivos y que se encuentren en el mismo directorio.\"\n"
    "fi ";

PatchGenerator::PatchGenerator(QObject *parent) : QObject(parent)
{
}

PatchGenerator::ValidationResult PatchGenerator::validateParams(const PatchParams &params)
{
    ValidationResult result;
    result.isValid = true;

    if (params.sourceFiles.isEmpty()) {
        result.isValid = false;
        result.errorMessage = "No se han seleccionado archivos de origen";
        return result;
    }

    if (params.targetFiles.isEmpty()) {
        result.isValid = false;
        result.errorMessage = "No se han seleccionado archivos de destino";
        return result;
    }

    if (params.sourceFiles.count() != params.targetFiles.count()) {
        result.isValid = false;
        result.errorMessage = "La cantidad de archivos de origen es distinta a la de archivos destino";
        return result;
    }

    if (params.outputDirectory.isEmpty()) {
        result.isValid = false;
        result.errorMessage = "No se ha seleccionado directorio de salida";
        return result;
    }

    if (params.patchPrefix.isEmpty()) {
        result.isValid = false;
        result.errorMessage = "No se ha especificado prefijo para el parche";
        return result;
    }

    if (!QDir(params.outputDirectory).exists()) {
        result.isValid = false;
        result.errorMessage = "El directorio de salida no existe";
        return result;
    }

    for (const QString &sourceFile : params.sourceFiles) {
        if (!QFile::exists(sourceFile)) {
            result.isValid = false;
            result.errorMessage = QString("El archivo de origen no existe: %1").arg(sourceFile);
            return result;
        }
    }

    for (const QString &targetFile : params.targetFiles) {
        if (!QFile::exists(targetFile)) {
            result.isValid = false;
            result.errorMessage = QString("El archivo de destino no existe: %1").arg(targetFile);
            return result;
        }
    }

    return result;
}

bool PatchGenerator::generatePatches(const PatchParams &params)
{
    ValidationResult validation = validateParams(params);
    if (!validation.isValid) {
        emit errorOccurred(validation.errorMessage);
        return false;
    }

    int totalFiles = params.sourceFiles.count();

    for (int i = 0; i < totalFiles; ++i) {
        emit patchProgress(i + 1, totalFiles);

        QString currentPrefix = params.patchPrefix;
        if (totalFiles > 1) {
            currentPrefix += QString("-%1").arg(i + 1);
        }

        if (!createPatchFiles(params.sourceFiles[i], params.targetFiles[i],
                             params.outputDirectory, currentPrefix, params.compress)) {
            return false;
        }
    }

    emit patchCompleted();
    return true;
}

bool PatchGenerator::createPatchFiles(const QString &source, const QString &target,
                                     const QString &outputDir, const QString &prefix, bool compress)
{
    QFileInfo sourceInfo(source);
    QFileInfo targetInfo(target);
    QString sourceName = sourceInfo.fileName();
    QString targetName = targetInfo.fileName();

    QString tempDir = QString("%1/%2").arg(outputDir, prefix);
    if (!QDir().mkdir(tempDir)) {
        emit errorOccurred(QString("No se pudo crear el directorio temporal: %1").arg(tempDir));
        return false;
    }

    QString vcdiffPath = QString("%1/%2.vcdiff").arg(tempDir, prefix);
    QString xdeltaPath = getXdeltaPath(tempDir);

    if (!copyResourceFile(":/files/xdelta3.exe", QString("%1/xdelta3.exe").arg(tempDir))) {
        emit errorOccurred("No se pudo copiar xdelta3.exe");
        return false;
    }

    QStringList arguments;
    arguments << "-e" << "-s" << source << target << vcdiffPath;

    QProcess xdeltaProcess;
    xdeltaProcess.start(xdeltaPath, arguments);
    if (!xdeltaProcess.waitForFinished(-1)) {
        emit errorOccurred("Error al ejecutar xdelta3");
        cleanupTempDirectory(tempDir);
        return false;
    }

    if (!createScripts(tempDir, prefix, sourceName, targetName)) {
        cleanupTempDirectory(tempDir);
        return false;
    }

    if (!QFile::exists(QString("%1/%2.vcdiff").arg(tempDir, prefix))) {
        emit errorOccurred("No se pudo crear el archivo vcdiff");
        cleanupTempDirectory(tempDir);
        return false;
    }

    if (compress) {
        if (!createZipArchive(tempDir, outputDir, prefix)) {
            cleanupTempDirectory(tempDir);
            return false;
        }
        cleanupTempDirectory(tempDir);
    }

    return true;
}

bool PatchGenerator::createScripts(const QString &tempDir, const QString &prefix,
                                  const QString &sourceName, const QString &targetName)
{
    QString windowsScript = WINDOWS_SCRIPT_TEMPLATE
        .arg(sourceName)
        .arg(targetName)
        .arg(prefix);

    QString linuxScript = LINUX_SCRIPT_TEMPLATE
        .arg(sourceName)
        .arg(targetName)
        .arg(prefix);

    QString windowsScriptPath = QString("%1/%2.bat").arg(tempDir, prefix);
    QString linuxScriptPath = QString("%1/%2").arg(tempDir, prefix);
    QString readmePath = QString("%1/leeme.txt").arg(tempDir);

    QFile windowsFile(windowsScriptPath);
    if (!windowsFile.open(QIODevice::WriteOnly)) {
        emit errorOccurred("No se pudo crear el script de Windows");
        return false;
    }
    QTextStream windowsStream(&windowsFile);
    windowsStream << windowsScript;
    windowsFile.close();

    QFile linuxFile(linuxScriptPath);
    if (!linuxFile.open(QIODevice::WriteOnly)) {
        emit errorOccurred("No se pudo crear el script de Linux");
        return false;
    }
    QTextStream linuxStream(&linuxFile);
    linuxStream << linuxScript;
    linuxFile.close();

    QFile readmeFile(readmePath);
    if (!readmeFile.open(QIODevice::WriteOnly)) {
        emit errorOccurred("No se pudo crear el archivo leeme.txt");
        return false;
    }
    QTextStream readmeStream(&readmeFile);
    readmeStream << README_TEXT;
    readmeFile.close();

    return true;
}

QString PatchGenerator::getXdeltaPath(const QString &tempDir)
{
    QString os = getCurrentOS();
    if (os == "windows") {
        return QString("%1/xdelta3.exe").arg(tempDir);
    }
    return "xdelta3";
}

QString PatchGenerator::getCurrentOS()
{
    QSysInfo osInfo;
    return osInfo.productType();
}

bool PatchGenerator::copyResourceFile(const QString &resourcePath, const QString &destination)
{
    return QFile::copy(resourcePath, destination);
}

bool PatchGenerator::createZipArchive(const QString &tempDir, const QString &outputDir, const QString &prefix)
{
    QString zipPath = QString("%1/%2.zip").arg(outputDir, prefix);
    QString currentOS = getCurrentOS();

    // Files to include in archive
    QStringList filesToZip = {
        QString("%1/%2.vcdiff").arg(tempDir, prefix),
        QString("%1/%2").arg(tempDir, prefix),
        QString("%1/%2.bat").arg(tempDir, prefix),
        QString("%1/leeme.txt").arg(tempDir),
        QString("%1/xdelta3.exe").arg(tempDir)
    };

    // Try different native compression methods
    if (currentOS == "windows") {
        // Windows: Use PowerShell Compress-Archive (Windows 10+)
        return createZipWithPowerShell(zipPath, filesToZip);
    } else {
        // Linux/Unix: Use system zip command
        return createZipWithSystemZip(zipPath, filesToZip);
    }
}


bool PatchGenerator::createZipWithPowerShell(const QString &zipPath, const QStringList &filePaths)
{
    // Create PowerShell script to compress files
    QStringList validFiles;
    for (const QString &filePath : filePaths) {
        if (QFile::exists(filePath)) {
            validFiles.append(QString("'%1'").arg(filePath));
        }
    }

    if (validFiles.isEmpty()) {
        emit errorOccurred("No hay archivos válidos para comprimir");
        return false;
    }

    QString psScript = QString("Compress-Archive -Path %1 -DestinationPath '%2' -Force")
                          .arg(validFiles.join(","))
                          .arg(zipPath);

    QProcess psProcess;
    psProcess.start("powershell.exe", QStringList() << "-Command" << psScript);

    if (!psProcess.waitForFinished(30000)) { // 30 second timeout
        emit errorOccurred("Timeout al ejecutar PowerShell Compress-Archive");
        return false;
    }

    if (psProcess.exitCode() != 0) {
        emit errorOccurred("Error en PowerShell Compress-Archive: " + psProcess.readAllStandardError());
        return false;
    }

    return QFile::exists(zipPath);
}

bool PatchGenerator::createZipWithSystemZip(const QString &zipPath, const QStringList &filePaths)
{
    // Check if system zip command is available
    QProcess testZip;
    testZip.start("zip", QStringList() << "-v");
    if (!testZip.waitForFinished(5000) || testZip.exitCode() != 0) {
        emit errorOccurred("Comando 'zip' no disponible en el sistema. Instala zip: sudo apt install zip");
        return false;
    }

    // Prepare arguments for zip command
    QStringList arguments;
    arguments << "-j" << zipPath; // -j = junk paths (store files without directory structure)

    // Add only existing files
    for (const QString &filePath : filePaths) {
        if (QFile::exists(filePath)) {
            arguments.append(filePath);
        }
    }

    if (arguments.size() <= 2) { // Only zipPath and -j flag
        emit errorOccurred("No hay archivos válidos para comprimir");
        return false;
    }

    QProcess zipProcess;
    zipProcess.start("zip", arguments);

    if (!zipProcess.waitForFinished(30000)) { // 30 second timeout
        emit errorOccurred("Timeout al ejecutar comando zip");
        return false;
    }

    if (zipProcess.exitCode() != 0) {
        emit errorOccurred("Error en comando zip: " + zipProcess.readAllStandardError());
        return false;
    }

    return QFile::exists(zipPath);
}

void PatchGenerator::cleanupTempDirectory(const QString &tempDir)
{
    QDir dir(tempDir);
    dir.removeRecursively();
}