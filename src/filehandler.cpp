#include <QTextStream>
#include <QDir>
#include "filehandler.h"

FileHandler::FileHandler(const QString fileName) : m_fileName(fileName)
{
    m_file.setFileName(m_fileName);
}

bool FileHandler::readFile(uint32_t length, std::vector<QString> &readValues)
{
    QTextStream in(&m_file);
    QString temp;
    bool fileOpened = openFileForRead();

    if (fileOpened) {
        for (uint32_t i = 0; i < length; i++) {
            temp = in.readLine();
            readValues.push_back(temp);
        }
        m_file.close();
    }

    return fileOpened;
}

bool FileHandler::openFileForRead()
{
    QDir::setCurrent("/home/operator/Desktop");
    return m_file.open(QIODevice::ReadOnly);
}


