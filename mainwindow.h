#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QFile>
#include <QMessageBox>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QtXlsx>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QDebug>
#include "dialogsetting.h"
#include "threadworker.h"
#include "threadsqlconnectionworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //For every ventap, check the connection
    QSqlDatabase checkConnection(QString strDatabaseHost,QString strDatabaseAddress,QSqlDatabase database,QString databaseName);
    bool execSqlErp(QSqlDatabase database,QString sqlErp,QDate date1,QDate date2);
    QThread* createThread(QSqlDatabase database,QDate date1,QDate date2,int iIndex);
    bool initDatabase();
    void showTableview();

private slots:
    void on_pushButtonSetting_clicked();

    void slotCheckConnection();

    void on_pushButton_clicked();

    void on_pushButtonExport_clicked();

    void on_pushButtonCheck_clicked();

    void slotSettingConfirm();
    void slotRecevied(QSqlQueryModel *pModel,int index);
    void slotCheckConnection(bool flag,int index);
    void slotCheckConnectionFinished();

private:
    Ui::MainWindow *ui;

    QString m_sIniFilePath;
    DialogSetting *m_pDialogSetting;
    QSqlDatabase m_DatabaseERP;
    QSqlDatabase m_DatabaseVentap1;
    QSqlDatabase m_DatabaseVentap2;
    QSqlDatabase m_DatabaseVentap3;
    QSqlDatabase m_DatabaseVentap4;
    QSqlDatabase m_DatabaseVentap5;
    QSqlDatabase m_DatabaseVentap6;
    QSqlDatabase m_DatabaseVentap7;
    bool m_flagErp = false;
    bool m_flag1,m_flag2,m_flag3,m_flag4,m_flag5,m_flag6,m_flag7;

    int m_iThreadFinishedCount = 0;
    int m_iThreadNumber = 0;

};

#endif // MAINWINDOW_H
