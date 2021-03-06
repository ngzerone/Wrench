#ifndef _ADBNOTIFICATIONTHREAD_H_
#define _ADBNOTIFICATIONTHREAD_H_

#include <QtCore/QThread>
#include <QTcpSocket>
#include <QTimer>
#include "adbclient.h"
class AdbNotificationThread : public QThread
{
    Q_OBJECT
public:
    AdbNotificationThread(QObject *parent = 0);
    ~AdbNotificationThread();

public slots:
    void onAdbNotificationClicked(const QString&);

private slots:
    void timeOut();
    void onDisconnected();
    void onNewNotification();

private:
    QTimer *mConnectTimer;
    QTcpSocket *notificationSocket;
    QByteArray mLastJsonStr;
    qint64 mLastTime;

signals:
    void adbNotificationArrived(const QString& key, const QString& pkg,
                                const QString& title, const QString& text,
                                const QString& ticker);
    void adbNotificationState(const QString&);
protected:
    void run();
};

#endif /* _ADBNOTIFICATIONTHREAD_H_ */
