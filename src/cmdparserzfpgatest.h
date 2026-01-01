#ifndef CMDPARSERZFPGATEST_H
#define CMDPARSERZFPGATEST_H

#include <QSimpleCmdParserSocketBase>

enum CmdZfpgaTestCmdIds
{
    CMD_ZFPGATEST_READ = 1,
    CMD_ZFPGATEST_WRITE,
    CMD_ZFPGATEST_READ_ASCII,
    CMD_ZFPGATEST_WRITE_ASCII,
    CMD_ZFPGATEST_WRITE_FILE_WITH_TIMER
};

class CmdParserZfpgaTest : public QSimpleCmdParserSocketBase
{
    Q_OBJECT
public:
    explicit CmdParserZfpgaTest(QObject *parent = NULL);
    virtual QString GetParserName() override { return QLatin1String("ZfpgaTest"); }
protected:
    virtual const QString PlausiCheck(SimpleCmdData *pCmd, const QVariantList &params) override;
};

#endif // CMDPARSERZFPGATEST_H
