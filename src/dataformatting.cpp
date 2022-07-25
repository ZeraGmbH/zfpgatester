#include "dataformatting.h"

namespace DataFormatting {

quint32 hexStringToInt(QString string)
{
    return string.toInt(Q_NULLPTR, 16);
}

QByteArray stringToQBytes(QString strData)
{
    strData = strData.replace(" ", "").replace("\n", "");
    quint32 ui32Len = strData.size() / 2;
    QByteArray intData;
    for(quint32 ui32Byte=0; ui32Byte<ui32Len; ui32Byte++) {
        intData.append(strData.mid(ui32Byte*2, 2).toInt(Q_NULLPTR, 16));
    }
    return intData;
}

}
