#ifndef CMDHANDERZFPGATEST_H
#define CMDHANDERZFPGATEST_H

#include <QList>
#include <QMap>
#include <QTcpSocket>
#include <QSimpleCmdHandlerBase>

class CmdHandlerZfpgaTest : public QSimpleCmdHandlerBase
{
    Q_OBJECT
public:
    explicit CmdHandlerZfpgaTest(QObject *parent = 0);
    virtual void StartCmd(SimpleCmdData *pCmd, QVariantList params);
signals:

public slots:

private:
};

#endif // CMDHANDERZFPGATEST_H
