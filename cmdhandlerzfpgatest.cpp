#include <QTimer>
#include <QEventLoop>
#include <QStringList>
#include <sys/types.h>
#include <unistd.h>
#include "globals.h"
#include "cmdhandlerzfpgatest.h"
#include "cmdparserzfpgatest.h"

CmdHandlerZfpgaTest::CmdHandlerZfpgaTest(QObject *parent) : QSimpleCmdHandlerBase(parent)
{
}

void CmdHandlerZfpgaTest::StartCmd(SimpleCmdData *pCmd, QVariantList params)
{
    QString strAddrHex;
    quint32 ui32Address;
    quint32 ui32Len;
    QByteArray writeData;
    QByteArray readData;
    QString strResult, strByteData;

    switch(pCmd->GetCmdID())
    {
    case CMD_ZFPGATEST_READ:
        strAddrHex = params[0].toString();
        ui32Address = strAddrHex.toInt(Q_NULLPTR, 16);
        if (lseek(gDeviceFd, ui32Address, 0) < 0 )
        {
            emit OperationFinish(true, QLatin1String("lseek did not succeed"));
            return;
        }
        ui32Len = params[1].toInt();
        readData.resize(ui32Len);
        if(read(gDeviceFd, readData.data(), ui32Len) < 0)
        {
            emit OperationFinish(true, QLatin1String("read did not succeed"));
            return;
        }
        for(int iByte=0; iByte<readData.size(); iByte++)
        {
            strByteData.sprintf("%02X", (quint8)readData[iByte]);
            strResult += strByteData;
            if(iByte%4 == 3)
                strResult += QLatin1String(" ");
        }
        emit OperationFinish(false, strResult);
        break;
    case CMD_ZFPGATEST_WRITE:
        strAddrHex = params[0].toString();
        ui32Address = strAddrHex.toInt(Q_NULLPTR, 16);
        if (lseek(gDeviceFd, ui32Address, 0) < 0 )
        {
            emit OperationFinish(true, QLatin1String("lseek did not succeed"));
            return;
        }
        QString strData = params[1].toString().replace(QLatin1String(" "), QString());
        ui32Len = strData.size() / 2;
        for(quint32 ui32Byte=0; ui32Byte<ui32Len; ui32Byte++)
        {
            writeData.append(strData.mid(ui32Byte*2, 2).toInt(Q_NULLPTR, 16));
        }
        if(write(gDeviceFd, readData.data(), ui32Len) < 0)
            emit OperationFinish(true, QLatin1String("read did not succeed"));
        else
            emit OperationFinish(false, QString());
        break;
    }
}
