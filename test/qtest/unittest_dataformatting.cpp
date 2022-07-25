#include "unittest_dataformatting.h"
#include "dataformatting.h"

QTEST_MAIN(unittest_dataformatting)

void unittest_dataformatting::testStringToQBytes()
{
    QFETCH(QString, string);
    QFETCH(QByteArray, result);

    QCOMPARE(DataFormatting::stringToQBytes(string), result);
}

void unittest_dataformatting::testStringToQBytes_data()
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

void unittest_dataformatting::testHexStringToInt()
{
    QFETCH(QString, string1);
    QFETCH(quint32, result1);

    QCOMPARE(DataFormatting::hexStringToInt(string1), result1);
}

void unittest_dataformatting::testHexStringToInt_data()
{
    QTest::addColumn<QString>("string1");
    QTest::addColumn<quint32>("result1");

    QVariant param = "0001";
    quint32 res = 1;
    QTest::newRow("String 22") << "0000" << static_cast<quint32>(0);
    QTest::newRow("String 22") << "0022" << static_cast<quint32>(34);
    QTest::newRow("String 22") << "1000" << static_cast<quint32>(4096);
}
