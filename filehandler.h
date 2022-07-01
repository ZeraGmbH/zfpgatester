#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include <QStringList>
#include <QFile>

class FileHandler
{
public:
    FileHandler(const QString fileName);

    bool readFile(uint32_t length, std::vector<QString> &readValues);

private:
    bool openFileForRead();

    QFile m_file;
    QString m_fileName;
};

#endif // FILEHANDLER_H
