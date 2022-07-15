#include <QTextStream>
#include "textfilehandler.h"

TextFileHandler::TextFileHandler(const QString fileInfo, bool createThisFile)
{
    m_fileInfo = std::make_shared<QFileInfo>(fileInfo);
    m_file.setFileName(m_fileInfo->fileName());
    m_dir = (m_fileInfo->dir());

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

bool TextFileHandler::readFile(QString &readValues)
{
    QTextStream fileContents(&m_file);
    bool fileOpened = openFileForRead();

    if (fileOpened) {
        readValues = fileContents.readAll();
        m_file.close();
    }

    return fileOpened;
}

bool TextFileHandler::writeFile(QString &writeValues, bool append)
{
    QTextStream fileContents(&m_file);
    bool fileOpened = openFileForWrite(append);

    if (fileOpened) {
        fileContents << writeValues;
        m_file.close();
    }

    return fileOpened;
}

void TextFileHandler::createFile()
{
    if(!m_dir.exists(m_fileInfo->filePath()))
        m_dir.mkpath(m_fileInfo->filePath());

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


