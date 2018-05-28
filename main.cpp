#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QSimpleCmdServer>
#include "globals.h"
#include "cmdparserzfpgatest.h"
#include "cmdhandlerzfpgatest.h"

QFile gDeviceFile;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser cmdLineParser;
    cmdLineParser.setApplicationDescription("zfpgatester");
    cmdLineParser.addHelpOption();

    // command line parameters
    QCommandLineOption optPortNo(QStringList() << "p" << "port", "IP-Port server opens (default: 5000)", "ip-port");
    optPortNo.setDefaultValue("5000");
    cmdLineParser.addOption(optPortNo);
    QCommandLineOption optDevFile(QStringList() << "d" << "devicefile", "Device file to open (default: /dev/zFPGA1dbg)", "filename");
    optDevFile.setDefaultValue("/dev/zFPGA1dbg");
    cmdLineParser.addOption(optDevFile);
    QCommandLineOption optVerboseLevel(QStringList() << "v" << "verbose", "Verbose level", "verbose-level");
    optVerboseLevel.setDefaultValue("0");
    cmdLineParser.addOption(optVerboseLevel);

    // process command line
    cmdLineParser.process(a);
    QString strPorNo = cmdLineParser.value(optPortNo);
    if(strPorNo.isEmpty())
        cmdLineParser.showHelp(-1);
    bool bConversionOK = true;
    int iPortNo = strPorNo.toInt(&bConversionOK);
    if(!bConversionOK)
        cmdLineParser.showHelp(-1);
    QString strDevFile = cmdLineParser.value(optDevFile);
    QString strVerboseLevel = cmdLineParser.value(optVerboseLevel);
    int iVerboseLevel = 0;
    if(!strVerboseLevel.isEmpty())
    {
        iVerboseLevel = strVerboseLevel.toInt(&bConversionOK);
        if(!bConversionOK)
            cmdLineParser.showHelp(-1);
    }

    // parser/handler/server objects
    CmdParserZfpgaTest parserZfpgaTest;
    CmdHandlerZfpgaTest handlerZfpgaTest;
    parserZfpgaTest.SetCmdHandler(&handlerZfpgaTest);
    QSimpleCmdServer serverZfpgaTest;

    // Log Level
    QSimpleCmdParserSocketBase::SetCmdLogGlobal(iVerboseLevel >= 1);

    // Open device file
    QFileInfo check_dev_file(strDevFile);
    if(check_dev_file.exists())
    {
        gDeviceFile.setFileName(strDevFile);
        if(!gDeviceFile.open(QIODevice::ReadWrite | QIODevice::Unbuffered))
        {
            QString strMsg = QString(QLatin1String("Could not open device file %1")).arg(strDevFile);
            parserZfpgaTest.SetGlobalOutOfOrderMessage(strMsg);
            qWarning(qPrintable(strMsg));
        }

    }
    else
    {
        QString strMsg = QString(QLatin1String("Device file %1 does not exist")).arg(strDevFile);
        parserZfpgaTest.SetGlobalOutOfOrderMessage(strMsg);
        qWarning(qPrintable(strMsg));
    }

    // Ensure event loop up
    QTimer::singleShot(300,[&]
                       ()

    {
        // start server
        if(serverZfpgaTest.Setup(iPortNo, &parserZfpgaTest))
            qInfo("Opened FPGA I/O server on port %u", iPortNo);
        else
            qWarning("FPGA I/O server does not listen on %u", iPortNo);
    });

    return a.exec();
}
