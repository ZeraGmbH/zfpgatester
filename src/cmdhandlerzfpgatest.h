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
    bool lSeek(quint32 address, int fd);
    void reportlSeekError();

    quint32 hexStringToInt(QVariant param);

    QByteArray stringToQBytes(QString strData);
};

#endif // CMDHANDERZFPGATEST_H
