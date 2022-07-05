#include <QTextStream>
#include "textfilehandler.h"

TextFileHandler::TextFileHandler(const QString fileName, const QString filePath, bool createThisFile) : m_filePath(filePath)
{
    m_file.setFileName(fileName);
    m_dir.setPath(m_filePath);

    if (createThisFile)
        createFile();
}

bool TextFileHandler::fileExists()
{
    return m_file.exists();
}

void TextFileHandler::deleteFile()
{
    m_file.remove();
}

bool TextFileHandler::readFile(uint32_t length, std::vector<QString> &readValues)
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

bool TextFileHandler::writeFile(std::vector<QString> &writeValues, bool append)
{
    QTextStream in(&m_file);
    bool fileOpened = openFileForWrite(append);

    if (fileOpened) {
        for (uint32_t i = 0; i < writeValues.size(); i++) {
            in << writeValues.at(i) << "\n";
        }
        m_file.close();
    }

    return fileOpened;
}

void TextFileHandler::createFile()
{
    if(!m_dir.exists(m_filePath))
        m_dir.mkpath(m_filePath);

    m_file.open(QIODevice::ReadWrite);
}

bool TextFileHandler::openFileForRead()
{
    return m_file.open(QIODevice::ReadOnly);
}

bool TextFileHandler::openFileForWrite(bool append)
{
    if (append)
        return m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    else
        return m_file.open(QIODevice::WriteOnly | QIODevice::Text);
}


