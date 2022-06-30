#ifndef CMDPARSERZFPGATEST_H
#define CMDPARSERZFPGATEST_H

#include <QSimpleCmdParserSocketBase>
#include "cmdhandlerzfpgatest.h"

enum CmdZfpgaTestCmdIds
{
    CMD_ZFPGATEST_READ = 1,
    CMD_ZFPGATEST_WRITE,
    CMD_ZFPGATEST_READ_ASCII,
    CMD_ZFPGATEST_WRITE_ASCII,
    CMD_ZFPGATEST_READ_TIMING_MEASUREMENT,
    CMD_ZFPGATEST_WRITE_TIMING_MEASUREMENT
};

class CmdParserZfpgaTest : public QSimpleCmdParserSocketBase
{
    Q_OBJECT
public:
    explicit CmdParserZfpgaTest(QObject *parent = NULL);
    virtual QString GetParserName() { return QLatin1String("ZfpgaTest"); }

signals:

protected:
    virtual const QString PlausiCheck(SimpleCmdData *pCmd, const QVariantList &params);

private:
};

#endif // CMDPARSERZFPGATEST_H
