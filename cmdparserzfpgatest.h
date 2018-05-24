#ifndef CMDPARSERZFPGATEST_H
#define CMDPARSERZFPGATEST_H

#include <QSimpleCmdParserSocketBase>
#include "cmdhandlerzfpgatest.h"

enum CmdZfpgaTestCmdIds
{
    CMD_ZFPGATEST_READ = 1,
    CMD_ZFPGATEST_WRITE,
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
