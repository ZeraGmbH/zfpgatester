#include "unittest_cmdhandlerzfpgatest.h"
#include <cmdhandlerzfpgatest.h>
#include <cmdparserzfpgatest.h>
#include <QFileInfo>
#include <fcntl.h>
#include <QSignalSpy>
#include <QTemporaryFile>

QTEST_MAIN(unittest_cmdhandlerzfpgatest)

int gDeviceFd = 0;

void unittest_cmdhandlerzfpgatest::lSeekNonexistingFile()
{
    SimpleCmdData testCmd(QString(), CmdParamTypeIdList() << PARAM_TYPE_INT, CMD_ZFPGATEST_READ, true, QString());
    CmdHandlerZfpgaTest testCmdHandler;

    QTemporaryFile testF;
    gDeviceFd = testF.handle();

    QString address = "00040000";
    QVariantList params{address};

    QSignalSpy spy(&testCmdHandler, SIGNAL(OperationFinish(bool, QString)));

    testCmdHandler.StartCmd(&testCmd, params);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == true);
    QVERIFY(arguments.at(1).toString() == "lseek did not succeed");
}
