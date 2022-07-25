#ifndef DATAFORMATTING_H
#define DATAFORMATTING_H

#include <qglobal.h>
#include <QVariant>

namespace DataFormatting{
    QByteArray stringToQBytes(QString strData);
    quint32 hexStringToInt(QString string);
}

#endif // DATAFORMATTING_H
