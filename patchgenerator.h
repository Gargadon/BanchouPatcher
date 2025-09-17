#ifndef PATCHGENERATOR_H
#define PATCHGENERATOR_H

#include <QString>
#include <QStringList>
#include <QObject>

class PatchGenerator : public QObject
{
    Q_OBJECT

public:
    struct PatchParams {
        QStringList sourceFiles;
        QStringList targetFiles;
        QString outputDirectory;
        QString patchPrefix;
        bool compress;
    };

    struct ValidationResult {
        bool isValid;
        QString errorMessage;
    };

    explicit PatchGenerator(QObject *parent = nullptr);

    ValidationResult validateParams(const PatchParams &params);
    bool generatePatches(const PatchParams &params);

private:
    static const QString README_TEXT;
    static const QString WINDOWS_SCRIPT_TEMPLATE;
    static const QString LINUX_SCRIPT_TEMPLATE;
    static const int REQUIRED_PARAMS_COUNT = 4;

    bool validateSinglePatch(const QString &source, const QString &target,
                           const QString &outputDir, const QString &prefix);
    bool createPatchFiles(const QString &source, const QString &target,
                         const QString &outputDir, const QString &prefix, bool compress);
    bool createScripts(const QString &tempDir, const QString &prefix,
                      const QString &sourceName, const QString &targetName);
    bool createZipArchive(const QString &tempDir, const QString &outputDir,
                         const QString &prefix);
    bool createZipWithPowerShell(const QString &zipPath, const QStringList &filePaths);
    bool createZipWithSystemZip(const QString &zipPath, const QStringList &filePaths);
    QString getXdeltaPath(const QString &tempDir);
    bool copyResourceFile(const QString &resourcePath, const QString &destination);
    QString getCurrentOS();
    void cleanupTempDirectory(const QString &tempDir);

signals:
    void patchProgress(int current, int total);
    void patchCompleted();
    void errorOccurred(const QString &error);
};

#endif // PATCHGENERATOR_H