#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

class ThreadWorker : public QObject
{
    Q_OBJECT
public:
    explicit ThreadWorker(QObject *parent = nullptr);
    ThreadWorker(QSqlDatabase database,QDate date1,QDate date2,int iIndex,QSqlDatabase databaseErp);
    ~ThreadWorker();
    void insertIntoDatabase();

public slots:
    void slotProcess();

signals:
    void signalSend(QSqlQueryModel *model,int index);
    void signalFinished();
    void signalError(QString err);

private:
    QSqlDatabase m_Database;
    QSqlDatabase m_DatabaseErp;
    QSqlQueryModel *m_pModel;
    QString m_sSql;
    QDate m_dDate1;
    QDate m_dDate2;
    int m_iIndex;

};

#endif // THREADWORKER_H
