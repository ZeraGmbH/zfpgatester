#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <memory>

class TextFileHandler
{
public:
    TextFileHandler(const QString fileName, bool createThisFile);

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
    std::shared_ptr<QFileInfo> m_fileInfo;
};

#endif // FILEHANDLER_H
