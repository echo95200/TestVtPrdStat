#include "threadworker.h"

ThreadWorker::ThreadWorker(QObject *parent) : QObject(parent)
{

}

ThreadWorker::ThreadWorker(QSqlDatabase database,
                           QDate date1,
                           QDate date2,
                           int index,
                           QSqlDatabase databaseErp)
{
    m_Database = database;
    m_dDate1 = date1;
    m_dDate2 = date2;
    m_iIndex = index;
    m_DatabaseErp = databaseErp;
    m_sSql = "SELECT T_TICKET_DETAIL.PRD_REF,T_TICKET_DETAIL.PRD_ORG,SUM(T_TICKET_DETAIL.CNT) AS CNT,SUM(T_TICKET_DETAIL.TOTAL_TTC) AS TOTAL "
             "FROM T_TICKET "
             "INNER JOIN T_TICKET_DETAIL ON T_TICKET.ID = T_TICKET_DETAIL.TICKET_ID "
             "WHERE CAST (T_TICKET.OPER_DATETIME AS DATE ) BETWEEN ? AND ? "
             "GROUP BY T_TICKET_DETAIL.PRD_REF,T_TICKET_DETAIL.PRD_ORG";
}

ThreadWorker::~ThreadWorker()
{
    m_Database.close();
    m_pModel->deleteLater();
    m_sSql.clear();
}

void ThreadWorker::slotProcess()
{
    m_pModel = new QSqlQueryModel();
    QSqlQuery query(m_Database);
    query.prepare(m_sSql);
    query.bindValue(0,m_dDate1);
    query.bindValue(1,m_dDate2);
    query.exec();
    m_pModel->setQuery(query);
    while (m_pModel->canFetchMore()) {
        m_pModel->fetchMore();
    }
    insertIntoDatabase();
    emit signalSend(m_pModel,m_iIndex);
    emit signalFinished();
}

void ThreadWorker::insertIntoDatabase()
{
    //Insert the infos of the ventaps into the database
    bool flag = false;
    QString temp = "";
    double dTemp = 0.00;
    QSqlQuery query(m_DatabaseErp);
    QString sql = "INSERT INTO T_VT_PRD_STAT "
          "(PRD_ID, PRD_REF, PRD_DESC, SUP_CNT, SUP_TOTAL, INV_CNT, INV_TOTAL, TCK_CNT, TCK_TOTAL) "
          "VALUES('', ?, ?, 0, 0, 0, 0, ?, ?)";
    QList<QString> qList;
    int rows = m_pModel->rowCount();
    for (int row = 0; row < rows; row++) {
        qList.clear();
        for (int column = 0; column < 4; column++) {
            if (column < 2) {
                temp = m_pModel->data(m_pModel->index(row,column)).toString();
            } else {
                dTemp = m_pModel->data(m_pModel->index(row,column)).toDouble();
                temp = QString::number(dTemp,10,2);
            }
            qList.append(temp);
        }
        query.prepare(sql);
        query.bindValue(0,qList.at(0));
        query.bindValue(1,qList.at(1));
        query.bindValue(2,qList.at(2).toDouble());
        query.bindValue(3,qList.at(3).toDouble());
        flag = query.exec();
        if (!flag) {
            QMessageBox::about(NULL,"Error",query.lastError().text());
        }
    }
}
