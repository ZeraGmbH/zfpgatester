#include "cmdparserzfpgatest.h"
#include <QFile>

CmdParserZfpgaTest::CmdParserZfpgaTest(QObject *parent) : QSimpleCmdParserSocketBase(parent)
{
    /* Read: Read data from FPGA */
    /* Parameters: strHexAddress, iLen */
    /* Result: strHexData */
    AddCmdInfo("Read",
               CmdParamTypeIdList() << PARAM_TYPE_STRING << PARAM_TYPE_INT,
               CMD_ZFPGATEST_READ,
               true,
               QLatin1String("Param: strHexAddress, iLen\nResult strHexData"));

    /* Write: Write data to FPGA */
    /* Parameters: strHexAddress, strHexData */
    /* Result: None */
    AddCmdInfo("Write",
               CmdParamTypeIdList() << PARAM_TYPE_STRING << PARAM_TYPE_STRING,
               CMD_ZFPGATEST_WRITE,
               true,
               QLatin1String("Param: strHexAddress, strHexData"));

    /* ReadAscii: Read data from FPGA displayed as ASCII */
    /* Parameters: strHexAddress, iLen */
    /* Result: strAsciiData */
    AddCmdInfo("ReadAscii",
               CmdParamTypeIdList() << PARAM_TYPE_STRING << PARAM_TYPE_INT,
               CMD_ZFPGATEST_READ_ASCII,
               true,
               QLatin1String("Param: strHexAddress, iLen\nResult strAsciiData"));

    /* WriteAscii: Write Ascii data to FPGA */
    /* Parameters: strHexAddress, strAsciData */
    /* Result: None */
    AddCmdInfo("WriteAscii",
               CmdParamTypeIdList() << PARAM_TYPE_STRING << PARAM_TYPE_STRING,
               CMD_ZFPGATEST_WRITE_ASCII,
               true,
               QLatin1String("Param: strHexAddress, strAsciiData\nstrAsciiData: ") + BinaryConversionHelpString());

    /* WriteWithTimer: Write data from a file to FPGA and measure time of this operation */
    /* Parameters: strHexAddress, iLen */
    /* Result: time measured */
    AddCmdInfo("WriteFileWithTimer",
               CmdParamTypeIdList() << PARAM_TYPE_STRING << PARAM_TYPE_STRING << PARAM_TYPE_INT,
               CMD_ZFPGATEST_WRITE_FILE_WITH_TIMER,
               true,
               QLatin1String("Param: strHexAddress, strWriteDataFile, iTotalIterations"));
}

static void AppendErr(QString& strErrInfo, const QString& strCurrError)
{
    if(strErrInfo.isEmpty())
        strErrInfo = strCurrError;
    else
        strErrInfo += QLatin1String(" / ")+strCurrError;
}

const QString CmdParserZfpgaTest::PlausiCheck(SimpleCmdData *pCmd, const QVariantList &params)
{
    QString strRet;
    QString strCurrError, strErrInfo;
    QString strAddrHex;
    quint32 ui32Address;
    quint32 ui32Len;
    const quint32 ui32MaxAddress = (1<<19);
    bool bConversionOK = true;
    switch(pCmd->GetCmdID())
    {
    case CMD_ZFPGATEST_READ:
    case CMD_ZFPGATEST_READ_ASCII:
        strAddrHex = params[0].toString();
        ui32Len = params[1].toInt();
        ui32Address = strAddrHex.toInt(&bConversionOK, 16);
        if(bConversionOK)
        {
            // ensure aligned address
            if(ui32Address % 4)
            {
                strCurrError = QString("Hex address %1 is not 32bit aligned").arg(strAddrHex);
                AppendErr(strErrInfo, strCurrError);
            }
            // ensure aligned len
            if(ui32Len % 4)
            {
                strCurrError = QString("Length %1 is not 32bit aligned").arg(ui32Len);
                AppendErr(strErrInfo, strCurrError);
            }
            // check address / len limits
            if(ui32Address + ui32Len > ui32MaxAddress)
            {
                strCurrError.sprintf("Maximum address accessed 0x%04X exceeds maximum 0x%04X",
                                   ui32Address + ui32Len, ui32MaxAddress);
                AppendErr(strErrInfo, strCurrError);
            }
        }
        else
            strErrInfo = QString("Invalid hex address: %1").arg(strAddrHex);

        if(!strErrInfo.isEmpty())
            strRet = FormatErrorMsg(pCmd->GetDisplayStr(), strErrInfo);
        break;
    case CMD_ZFPGATEST_WRITE:
    case CMD_ZFPGATEST_WRITE_ASCII:
    case CMD_ZFPGATEST_WRITE_FILE_WITH_TIMER:
        strAddrHex = params[0].toString();
        ui32Address = strAddrHex.toInt(&bConversionOK, 16);
        if(bConversionOK)
        {
            // ensure aligned address
            if(ui32Address % 4)
            {
                strCurrError = QString("Hex address %1 is not 32bit aligned").arg(strAddrHex);
                AppendErr(strErrInfo, strCurrError);
            }
            if(pCmd->GetCmdID() == CMD_ZFPGATEST_WRITE)
            {
                QString strData;
                // ensure aligned data
                strData = params[1].toString().replace(QLatin1String(" "), QString());
                if(strData.size()%8 != 0)
                {
                    strCurrError = QString("Write data %1 does not contain 32bit values only").arg(params[1].toString());
                    AppendErr(strErrInfo, strCurrError);
                }
                // check correct hex for data
                if(!isValidHexValue(strData, 0))
                {
                    strCurrError = QString("Write data %1 is not valid hexadecimal").arg(params[1].toString());
                    AppendErr(strErrInfo, strCurrError);
                }
                ui32Len = strData.size() / 2;
            }
            else if(pCmd->GetCmdID() == CMD_ZFPGATEST_WRITE_FILE_WITH_TIMER)
            {
                QString strData;
                QFile inputDataFile(params[1].toString());
                if (!inputDataFile.exists()) {
                    strCurrError = QString("File %s doesn't exist").arg(params[1].toString());
                    AppendErr(strErrInfo, strCurrError);
                }
                if(!inputDataFile.open(QIODevice::ReadOnly)) {
                    strCurrError = QString("File %s couldn't be read").arg(params[1].toString());
                    AppendErr(strErrInfo, strCurrError);
                }
                strData = inputDataFile.readAll();
                inputDataFile.close();
                strData = strData.replace(" ", "").replace("\n", "");

                if(strData.size()%8 != 0)
                {
                    strCurrError = QString("Write data does not contain 32bit values only");
                    AppendErr(strErrInfo, strCurrError);
                }
                // check correct hex for data
                if(!isValidHexValue(strData, 0))
                {
                    strCurrError = QString("Write data is not valid hexadecimal");
                    AppendErr(strErrInfo, strCurrError);
                }
                ui32Len = strData.size() / 2;
            }
            else // Ascii
            {
                // ensure aligned data
                QByteArray data = BinaryFromAscii(params[1].toString());
                if(data.size()%4 != 0)
                {
                    strCurrError = QString("Write data %1 does not contain multiple 4byte-blocks").arg(params[1].toString());
                    AppendErr(strErrInfo, strCurrError);
                }
                ui32Len = data.size();
            }
            // check address / datalen limits
            if(ui32Address + ui32Len > ui32MaxAddress)
            {
                strCurrError.sprintf("Maximum address accessed 0x%04X exceeds maximum 0x%04X",
                                   ui32Address + ui32Len, ui32MaxAddress);
                AppendErr(strErrInfo, strCurrError);
            }
        }
        else
            strErrInfo = QString("Invalid hex address: %1").arg(strAddrHex);

        if(!strErrInfo.isEmpty())
            strRet = FormatErrorMsg(pCmd->GetDisplayStr(), strErrInfo);
        break;
    }
    return strRet;
}
