#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include <QStringList>
#include <QFile>
#include <QDir>

class TextFileHandler
{
public:
    TextFileHandler(const QString fileName, const QString filePath, bool createThisFile);

    bool fileExists();
    void deleteFile();
    bool readFile(QString &readValues);
    bool writeFile(QString &writeValues, bool append);

private:
    void createFile();
    bool openFileForRead();
    bool openFileForWrite(bool append);

    QFile m_file;
    QDir m_dir;
    QString m_filePath;
};

#endif // FILEHANDLER_H
