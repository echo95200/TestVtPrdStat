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
#include "dialogsetting.h"

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
    QSqlQueryModel* execSqlVentap(QSqlDatabase database,QString sqlVentap,qint64 time_t1,qint64 time_t2,
                                 QSqlQueryModel *model,bool flag);
    QSqlQueryModel* execSqlErp(QSqlDatabase database,QString sqlErp,qint64 time_t1,qint64 time_t2,
                                 QSqlQueryModel *model,bool flag);
    void updateTableView(QList<QSqlQueryModel*> modelListVentap);
    void createNewTableErp(QList<QSqlQueryModel*> modelListVentap,QSqlQueryModel *pModelErpInv,QSqlQueryModel *pModelErpSup);


private slots:
    void on_pushButtonSetting_clicked();

    void slotCheckConnection();

    void on_pushButton_clicked();

    void on_pushButtonExport_clicked();

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

    QList<int> m_iIndexVentap;
    QStringList m_strListPrdRef;
    QStringList m_strListPrdDesc;
    QList<double> m_dListPrdCnt;
    QList<double> m_dListPrdTotal;
};

#endif // MAINWINDOW_H
