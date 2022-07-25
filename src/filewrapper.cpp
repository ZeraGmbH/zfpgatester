#include <unistd.h>
#include "filewrapper.h"

FileWrapper::FileWrapper(int fileDescriptor) : m_fileDescriptor(fileDescriptor)
{
}

bool FileWrapper::lSeek(quint32 address)
{
    return (lseek(m_fileDescriptor, address, SEEK_SET) >= 0);
}
