#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class FileHandler
{
public:
    FileHandler(const QString fileName);

    void readFile(uint32_t length, std::vector<QString> &readValues);

private:
    bool openFileForRead();

    QFile m_file;
    QString m_fileName;
};

#endif // FILEHANDLER_H
