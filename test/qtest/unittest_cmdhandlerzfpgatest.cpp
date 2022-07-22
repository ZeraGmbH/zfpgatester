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

void unittest_cmdhandlerzfpgatest::testStringToQBytes()
{
    QFETCH(QString, string);
    QFETCH(QByteArray, result);

    QCOMPARE(CmdHandlerZfpgaTest::stringToQBytes(string), result);
}

void unittest_cmdhandlerzfpgatest::testStringToQBytes_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QByteArray>("result");

    QByteArray res("\x01");
    QTest::newRow("One Byte") << "01" << res;
    res = ("\x11\x22");
    QTest::newRow("Two Bytes with no spaces") << "1122" << res;
    QTest::newRow("Two Bytes with spaces") << "11 22" << res;
    res = ("\x32\x34\x44\x55");
    QTest::newRow("Four Bytes with no spaces") << "32344455" << res;
    QTest::newRow("Four Bytes with new line") << "3234\n4455" << res;
    res = ("\x67\x55\x23\x78\x11\x22\x33\x44");
    QTest::newRow("Four Bytes with no spaces") << "6755237811223344" << res;
    QTest::newRow("Four Bytes with spaces") << "67552378 11223344" << res;
}
