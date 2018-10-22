#ifndef THREADSQLCONNECTIONWORKER_H
#define THREADSQLCONNECTIONWORKER_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QSqlDatabase>
#include <QtDebug>

class ThreadSQLConnectionWorker : public QObject
{
    Q_OBJECT
public:
    explicit ThreadSQLConnectionWorker(QObject *parent = nullptr);
    ~ThreadSQLConnectionWorker();
    QSqlDatabase checkConnection(QString strDatabaseHost,
                                 QString strDatabaseAddress,
                                 QSqlDatabase database,
                                 QString mDatabaseName);

signals:
    void finished();
    void error(QString err);
    void signalSendResult(bool flag,int index);

public slots:
    void process();

private:
    QSqlDatabase m_DatabaseERP;
    QSqlDatabase m_DatabaseVentap1;
    QSqlDatabase m_DatabaseVentap2;
    QSqlDatabase m_DatabaseVentap3;
    QSqlDatabase m_DatabaseVentap4;
    QSqlDatabase m_DatabaseVentap5;
    QSqlDatabase m_DatabaseVentap6;
    QSqlDatabase m_DatabaseVentap7;

    bool m_flagErp = false;
    bool m_flag1 = false;
    bool m_flag2 = false;
    bool m_flag3 = false;
    bool m_flag4 = false;
    bool m_flag5 = false;
    bool m_flag6 = false;
    bool m_flag7 = false;
};

#endif // THREADSQLCONNECTIONWORKER_H
