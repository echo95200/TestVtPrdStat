#include "threadsqlconnectionworker.h"

ThreadSQLConnectionWorker::ThreadSQLConnectionWorker(QObject *parent) : QObject(parent)
{

}

ThreadSQLConnectionWorker::~ThreadSQLConnectionWorker()
{
    m_DatabaseERP.close();
    m_DatabaseVentap1.close();
    m_DatabaseVentap2.close();
    m_DatabaseVentap3.close();
    m_DatabaseVentap4.close();
    m_DatabaseVentap5.close();
    m_DatabaseVentap6.close();
    m_DatabaseVentap7.close();
}

void ThreadSQLConnectionWorker::process()
{
    QString strHost = "";
    QString strAddress = "";
    QString strDatabaseName = "";
    QString m_sIniFilePath = QApplication::applicationDirPath() + QDir::separator() + "VtPrdStat.ini";
    QSettings settings(m_sIniFilePath,QSettings::IniFormat);

    //Check erp connection
    strDatabaseName = "Erp";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();

    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flagErp = false;
    } else {

        m_DatabaseERP = checkConnection(strHost,strAddress,m_DatabaseERP,strDatabaseName);
        if (m_DatabaseERP.isOpen()) {
            m_flagErp = true;
        } else {
            m_flagErp = false;
        }
    }
    emit signalSendResult(m_flagErp,0);


    strDatabaseName = "POS1";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag1 = false;
    } else {
        m_DatabaseVentap1 = checkConnection(strHost,strAddress,m_DatabaseVentap1,strDatabaseName);
        if (m_DatabaseVentap1.isOpen()) {
            m_flag1 = true;
        } else {
            m_flag1 = false;
        }
    }
    emit signalSendResult(m_flag1,1);

    strDatabaseName = "POS2";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag2 = false;
    } else {
        m_DatabaseVentap2 = checkConnection(strHost,strAddress,m_DatabaseVentap2,strDatabaseName);
        if (m_DatabaseVentap2.isOpen()) {
            m_flag2 = true;
        } else {
            m_flag2 = false;
        }
    }
    emit signalSendResult(m_flag2,2);

    strDatabaseName = "POS3";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag3 = false;
    } else {
        m_DatabaseVentap3 = checkConnection(strHost,strAddress,m_DatabaseVentap3,strDatabaseName);
        if (m_DatabaseVentap3.isOpen()) {
            m_flag3 = true;
        } else {
            m_flag3 = false;
        }
    }
    emit signalSendResult(m_flag3,3);

    strDatabaseName = "POS4";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag4 = false;
    } else {
        m_DatabaseVentap4 = checkConnection(strHost,strAddress,m_DatabaseVentap4,strDatabaseName);
        if (m_DatabaseVentap4.isOpen()) {
            m_flag4 = true;
        } else {
            m_flag4 = false;
        }
    }
    emit signalSendResult(m_flag4,4);

    strDatabaseName = "POS5";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag5 = false;
    } else {
        m_DatabaseVentap5 = checkConnection(strHost,strAddress,m_DatabaseVentap5,strDatabaseName);
        if (m_DatabaseVentap5.isOpen()) {
            m_flag5 = true;
        } else {
            m_flag5 = false;
        }
    }
    emit signalSendResult(m_flag5,5);

    strDatabaseName = "POS6";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag6 = false;
    } else {
        m_DatabaseVentap6 = checkConnection(strHost,strAddress,m_DatabaseVentap6,strDatabaseName);
        if (m_DatabaseVentap6.isOpen()) {
            m_flag6 = true;
        } else {
            m_flag6 = false;
        }
    }
    emit signalSendResult(m_flag6,6);

    strDatabaseName = "POS7";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    if (strHost.isEmpty() && strAddress.isEmpty()) {
        m_flag7 = false;
    } else {
        m_DatabaseVentap7 = checkConnection(strHost,strAddress,m_DatabaseVentap7,strDatabaseName);
        if (m_DatabaseVentap7.isOpen()) {
            m_flag7 = true;
        } else {
            m_flag7 = false;
        }
    }
    emit signalSendResult(m_flag7,7);

    emit finished();
    qDebug() << "Check the connection finished...";
}

QSqlDatabase ThreadSQLConnectionWorker::checkConnection(QString strDatabaseHost, QString strDatabaseAddress,QSqlDatabase database,QString mDatabaseName)
{
    QString strDatabaseDriver = "QIBASE";
    QString strDatabaseUserName = "SYSDBA";
    QString strDatabasePassword = "masterkey";
    int iDatabasePort = -1;

    //Check the connection
    QString strDatabaseFilePath = strDatabaseAddress;
    QFile dbFileErp(strDatabaseFilePath);
    if (QSqlDatabase::contains(mDatabaseName)) {
        database = QSqlDatabase::database(mDatabaseName);
    } else {
        database = QSqlDatabase::addDatabase(strDatabaseDriver,mDatabaseName);
    }
    database.setDatabaseName(dbFileErp.fileName());
    database.setUserName(strDatabaseUserName);
    database.setPassword(strDatabasePassword);
    database.setHostName(strDatabaseHost);
    database.setPort(iDatabasePort);
    database.open();
    return database;
}
