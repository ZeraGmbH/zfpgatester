#ifndef FILEWRAPPER_H
#define FILEWRAPPER_H

#include <qglobal.h>

class FileWrapper
{
public:
    explicit FileWrapper(int fileDescriptor);
    bool lSeek(quint32 address);

private:
    int m_fileDescriptor = -1;
};

#endif // FILEWRAPPER_H
