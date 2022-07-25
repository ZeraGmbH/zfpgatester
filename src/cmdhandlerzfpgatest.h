#ifndef CMDHANDERZFPGATEST_H
#define CMDHANDERZFPGATEST_H

#include <QList>
#include <QMap>
#include <QTcpSocket>
#include <QSimpleCmdHandlerBase>
#include "filewrapper.h"

class CmdHandlerZfpgaTest : public QSimpleCmdHandlerBase
{
    Q_OBJECT
public:
    explicit CmdHandlerZfpgaTest(QObject *parent = 0);
    virtual void StartCmd(SimpleCmdData *pCmd, QVariantList params);

signals:

public slots:

private:
    std::shared_ptr<FileWrapper> thisFile;

    void reportlSeekError();

};

#endif // CMDHANDERZFPGATEST_H
