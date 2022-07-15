#include <QTimer>
#include <QEventLoop>
#include <QStringList>
#include <sys/types.h>
#include <unistd.h>
#include "globals.h"
#include "cmdhandlerzfpgatest.h"
#include "cmdparserzfpgatest.h"
#include "timer.h"
#include "textfilehandler.h"

CmdHandlerZfpgaTest::CmdHandlerZfpgaTest(QObject *parent) : QSimpleCmdHandlerBase(parent)
{
}

void CmdHandlerZfpgaTest::StartCmd(SimpleCmdData *pCmd, QVariantList params)
{
    quint32 ui32Address;
    quint32 ui32Len;
    QByteArray writeData;
    QByteArray readData;
    QString strResult, strByteData;
    Timer readTime, writeTime;

    switch(pCmd->GetCmdID())
    {
    case CMD_ZFPGATEST_READ:
    case CMD_ZFPGATEST_READ_ASCII:
        ui32Address = hexStringToInt(params[0]);
        if (lSeek(ui32Address, gDeviceFd)) {
            reportlSeekError();
            return;
        }
        ui32Len = params[1].toInt();
        readData.resize(ui32Len);
        if(read(gDeviceFd, readData.data(), ui32Len) < 0) {
            emit OperationFinish(true, QLatin1String("read did not succeed"));
            return;
        }
        if(pCmd->GetCmdID() == CMD_ZFPGATEST_READ) {
            for(int iByte=0; iByte<readData.size(); iByte++) {
                strByteData.sprintf("%02X", (quint8)readData[iByte]);
                strResult += strByteData;
                if(iByte%4 == 3)
                    strResult += QLatin1String(" ");
            }
        }
        else {
            for(int iByte=0; iByte<readData.size(); iByte++) {
                if((quint8)readData[iByte] >= 32 && (quint8)readData[iByte] < 127) {
                    strByteData.sprintf("%c", (int)readData[iByte]);
                }
                else {
                    strByteData.sprintf("<0x%02X>", (quint8)readData[iByte]);
                }
                strResult += strByteData;
            }
        }
        emit OperationFinish(false, strResult);
        break;
    case CMD_ZFPGATEST_WRITE:
    case CMD_ZFPGATEST_WRITE_ASCII:
        ui32Address = hexStringToInt(params[0]);
        if (lSeek(ui32Address, gDeviceFd)) {
            reportlSeekError();
            return;
        }
        if(pCmd->GetCmdID() == CMD_ZFPGATEST_WRITE) {
            QString strData;
            strData = params[1].toString().replace(QLatin1String(" "), QString());
            ui32Len = strData.size() / 2;
            for(quint32 ui32Byte=0; ui32Byte<ui32Len; ui32Byte++) {
                writeData.append(strData.mid(ui32Byte*2, 2).toInt(Q_NULLPTR, 16));
            }
        }
        else {
            writeData = QSimpleCmdParserBase::BinaryFromAscii(params[1].toString());
            ui32Len = writeData.size();
        }
        if(write(gDeviceFd, writeData.data(), ui32Len) < 0)
            emit OperationFinish(true, QLatin1String("write did not succeed"));
        else
            emit OperationFinish(false, QString());
        break;
    case CMD_ZFPGATEST_READ_WITH_TIMER:
        ui32Address = hexStringToInt(params[0]);
        if (lSeek(ui32Address, gDeviceFd)) {
            reportlSeekError();
            return;
        }
        ui32Len = params[1].toInt();
        readData.resize(ui32Len);

        readTime.start();
        if(read(gDeviceFd, readData.data(), ui32Len) < 0) {
            emit OperationFinish(true, QLatin1String("read did not succeed"));
            return;
        }
        readTime.stop();

        for(int iByte=0; iByte<readData.size(); iByte++) {
            strByteData.sprintf("%02X", (quint8)readData[iByte]);
            strResult += strByteData;
            if(iByte%4 == 3)
                strResult += QLatin1String(" ");
        }

        strByteData.sprintf("\nTime taken: %ld us", readTime.getTimeSteadyClock_us());
        strResult += strByteData;

        emit OperationFinish(false, strResult);
        break;
    case CMD_ZFPGATEST_WRITE_WITH_TIMER:
        ui32Address = hexStringToInt(params[0]);
        if (lSeek(ui32Address, gDeviceFd)) {
            reportlSeekError();
            return;
        }

        QString fileName = params[2].toString();
        TextFileHandler inputDataFile(fileName, false);
        QString fileData, strData;
        if (!inputDataFile.fileExists()) {
            emit OperationFinish(true, QLatin1String("file doesn't exist"));
            return;
        }
        if (!inputDataFile.readFile(fileData)) {
            emit OperationFinish(true, QLatin1String("file could not be opened"));
            return;
        }
        strData = fileData.replace(QLatin1String("\n"), QString());

        ui32Len = params[1].toInt();
        for(quint32 ui32Byte=0; ui32Byte<ui32Len; ui32Byte++) {
            writeData.append(strData.mid(ui32Byte*2, 2).toInt(Q_NULLPTR, 16));
        }

        quint32 iterations = params[3].toInt();
        std::vector<long> time_us;
        long avgTime_us = 0;
        for(quint32 i=0; i<iterations; i++) {
            writeTime.start();
            if(write(gDeviceFd, writeData.data(), ui32Len) < 0) {
                emit OperationFinish(true, QLatin1String("write did not succeed"));
                return;
            }
            writeTime.stop();
            time_us.push_back(writeTime.getTimeHighResolution_us());
            strByteData.sprintf("\nTime taken: %ld us", writeTime.getTimeHighResolution_us());
            strResult += strByteData;
        }
        auto minmaxTime = std::minmax_element(time_us.begin(), time_us.end());
        for(const auto &time : time_us) {
            avgTime_us += time;
        }
        avgTime_us /= time_us.size();

        strByteData.sprintf("\nTime taken:\tAverage %ld us,\tMin %ld us,\tMax %ld us", avgTime_us, *minmaxTime.first, *minmaxTime.second);
        strResult += strByteData;


        emit OperationFinish(false, strResult);

        break;

    }
}

bool CmdHandlerZfpgaTest::lSeek(quint32 address, int fd)
{
    return (lseek(fd, address, SEEK_SET) >= 0);
}

void CmdHandlerZfpgaTest::reportlSeekError()
{
    emit OperationFinish(true, QLatin1String("lseek did not succeed"));
}

quint32 CmdHandlerZfpgaTest::hexStringToInt(QVariant param)
{
    return param.toString().toInt(Q_NULLPTR, 16);
}
