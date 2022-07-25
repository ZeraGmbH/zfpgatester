#ifndef UNITTEST_DATAFORMATTING_H
#define UNITTEST_DATAFORMATTING_H

#include <QtTest/QTest>

class unittest_dataformatting: public QObject
{
    Q_OBJECT

private slots:

    void testStringToQBytes();
    void testStringToQBytes_data();
    void testHexStringToInt();
    void testHexStringToInt_data();
};

#endif // UNITTEST_DATAFORMATTING_H
