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

    static QByteArray stringToQBytes(QString strData);
signals:

public slots:

private:
    bool lSeek(quint32 address, int fd);
    void reportlSeekError();

    quint32 hexStringToInt(QVariant param);
};

#endif // CMDHANDERZFPGATEST_H
