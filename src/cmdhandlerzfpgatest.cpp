#include <QTimer>
#include <QEventLoop>
#include <QStringList>
#include <sys/types.h>
#include <unistd.h>
#include "globals.h"
#include "cmdhandlerzfpgatest.h"
#include "cmdparserzfpgatest.h"
#include "timer.h"
#include "dataformatting.h"

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

    thisFile = std::make_shared<FileWrapper>(gDeviceFd);

    switch(pCmd->GetCmdID())
    {
    case CMD_ZFPGATEST_READ:
    case CMD_ZFPGATEST_READ_ASCII:
        ui32Address = DataFormatting::hexStringToInt(params[0].toString());
        if (!thisFile->lSeek(ui32Address)) {
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
        ui32Address = DataFormatting::hexStringToInt(params[0].toString());
        if (!thisFile->lSeek(ui32Address)) {
            reportlSeekError();
            return;
        }
        if(pCmd->GetCmdID() == CMD_ZFPGATEST_WRITE) {
            writeData = DataFormatting::stringToQBytes(params[1].toString());
        }
        else {
            writeData = QSimpleCmdParserBase::BinaryFromAscii(params[1].toString());
        }
        ui32Len = writeData.size();
        if(write(gDeviceFd, writeData.data(), ui32Len) < 0)
            emit OperationFinish(true, QLatin1String("write did not succeed"));
        else
            emit OperationFinish(false, QString());
        break;
    case CMD_ZFPGATEST_WRITE_FILE_WITH_TIMER:
        ui32Address = DataFormatting::hexStringToInt(params[0].toString());
        if (!thisFile->lSeek(ui32Address)) {
            reportlSeekError();
            return;
        }

        QFile inputDataFile(params[1].toString());
        inputDataFile.open(QIODevice::ReadOnly);
        QString fileData = inputDataFile.readAll();
        inputDataFile.close();

        writeData = DataFormatting::stringToQBytes(fileData);
        ui32Len = writeData.size();

        quint32 iterations = params[2].toInt();
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

void CmdHandlerZfpgaTest::reportlSeekError()
{
    emit OperationFinish(true, QLatin1String("lseek did not succeed"));
}
