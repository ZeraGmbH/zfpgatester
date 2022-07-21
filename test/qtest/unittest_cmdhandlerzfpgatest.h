#ifndef UNITTEST_CMDHANDLERZFPGATEST_H
#define UNITTEST_CMDHANDLERZFPGATEST_H

#include <QtTest/QTest>

class unittest_cmdhandlerzfpgatest : public QObject
{
    Q_OBJECT

private slots:
    void lSeekNonexistingFile();

    void testStringToQBytes();
    void testStringToQBytes_data();
};

#endif // UNITTEST_CMDHANDLERZFPGATEST_H
