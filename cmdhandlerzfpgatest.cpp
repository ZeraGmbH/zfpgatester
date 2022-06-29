#include <QTimer>
#include <QEventLoop>
#include <QStringList>
#include <sys/types.h>
#include <unistd.h>
#include "globals.h"
#include "cmdhandlerzfpgatest.h"
#include "cmdparserzfpgatest.h"
#include "timer.h"

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
    Timer readTime;

    switch(pCmd->GetCmdID())
    {
    case CMD_ZFPGATEST_READ:
    case CMD_ZFPGATEST_READ_ASCII:
        strAddrHex = params[0].toString();
        ui32Address = strAddrHex.toInt(Q_NULLPTR, 16);
        if (lseek(gDeviceFd, ui32Address, SEEK_SET) < 0 )
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
        if(pCmd->GetCmdID() == CMD_ZFPGATEST_READ)
        {
            for(int iByte=0; iByte<readData.size(); iByte++)
            {
                strByteData.sprintf("%02X", (quint8)readData[iByte]);
                strResult += strByteData;
                if(iByte%4 == 3)
                    strResult += QLatin1String(" ");
            }
        }
        else
        {
            for(int iByte=0; iByte<readData.size(); iByte++)
            {
                if((quint8)readData[iByte] >= 32 && (quint8)readData[iByte] < 127)
                {
                    strByteData.sprintf("%c", (int)readData[iByte]);
                }
                else
                {
                    strByteData.sprintf("<0x%02X>", (quint8)readData[iByte]);
                }
                strResult += strByteData;
            }
        }
        emit OperationFinish(false, strResult);
        break;
    case CMD_ZFPGATEST_WRITE:
    case CMD_ZFPGATEST_WRITE_ASCII:
        strAddrHex = params[0].toString();
        ui32Address = strAddrHex.toInt(Q_NULLPTR, 16);
        if (lseek(gDeviceFd, ui32Address, SEEK_SET) < 0 )
        {
            emit OperationFinish(true, QLatin1String("lseek did not succeed"));
            return;
        }
        if(pCmd->GetCmdID() == CMD_ZFPGATEST_WRITE)
        {
            QString strData;
            strData = params[1].toString().replace(QLatin1String(" "), QString());
            ui32Len = strData.size() / 2;
            for(quint32 ui32Byte=0; ui32Byte<ui32Len; ui32Byte++)
            {
                writeData.append(strData.mid(ui32Byte*2, 2).toInt(Q_NULLPTR, 16));
            }
        }
        else
        {
            writeData = QSimpleCmdParserBase::BinaryFromAscii(params[1].toString());
            ui32Len = writeData.size();
        }
        if(write(gDeviceFd, writeData.data(), ui32Len) < 0)
            emit OperationFinish(true, QLatin1String("write did not succeed"));
        else
            emit OperationFinish(false, QString());
        break;
    case CMD_ZFPGATEST_READ_TIMING_MEASUREMENT:
        strAddrHex = params[0].toString();
        ui32Address = strAddrHex.toInt(Q_NULLPTR, 16);
        if (lseek(gDeviceFd, ui32Address, SEEK_SET) < 0 )
        {
            emit OperationFinish(true, QLatin1String("lseek did not succeed"));
            return;
        }
        ui32Len = params[1].toInt();
        readData.resize(ui32Len);

        readTime.start();
        if(read(gDeviceFd, readData.data(), ui32Len) < 0)
        {
            emit OperationFinish(true, QLatin1String("read did not succeed"));
            return;
        }
        readTime.stop();

        for(int iByte=0; iByte<readData.size(); iByte++)
        {
            strByteData.sprintf("%02X", (quint8)readData[iByte]);
            strResult += strByteData;
            if(iByte%4 == 3)
                strResult += QLatin1String(" ");
        }

        strByteData.sprintf("\nTime taken(high resoution clock): %ld ns, %ld us", readTime.getTimeHighResolution_ns(), readTime.getTimeHighResolution_us());
        strResult += strByteData;
        strByteData.sprintf("\nTime taken(steady clock): %ld ns, %ld us", readTime.getTimeSteadyClock_ns(), readTime.getTimeSteadyClock_us());
        strResult += strByteData;

        emit OperationFinish(false, strResult);
        break;
    }
}
