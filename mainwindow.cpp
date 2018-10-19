#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_1->setObjectName("button1");
    ui->pushButton_2->setObjectName("button2");
    ui->pushButton_3->setObjectName("button3");
    ui->pushButton_4->setObjectName("button4");
    ui->pushButton_5->setObjectName("button5");
    ui->pushButton_6->setObjectName("button6");
    ui->pushButton_7->setObjectName("button7");
    ui->pushButton->setEnabled(true);
    ui->pushButtonExport->setEnabled(false);

    ui->dateEdit->setDisplayFormat("yyyy/MM/dd");
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate().addDays(-QDateTime::currentDateTime().date().day() + 1));
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit_2->setDisplayFormat("yyyy/MM/dd");
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_2->setMaximumDate(QDate::currentDate());
    ui->dateEdit_2->setCalendarPopup(true);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->verticalHeader()->hide();

    m_pDialogSetting = new DialogSetting();
    m_sIniFilePath = QApplication::applicationDirPath() + QDir::separator() + "VtPrdStat.ini";
    connect(m_pDialogSetting,SIGNAL(signalSettingConfirm()),this,SLOT(slotCheckConnection()));

    this->slotCheckConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pDialogSetting;
    m_DatabaseVentap1.close();
    m_DatabaseVentap2.close();
    m_DatabaseVentap3.close();
    m_DatabaseVentap4.close();
    m_DatabaseVentap5.close();
    m_DatabaseVentap6.close();
    m_DatabaseVentap7.close();
}

void MainWindow::on_pushButtonSetting_clicked()
{
    m_pDialogSetting->show();
}

//The methode for checking the connection of the database and return the QSqlDatabase
QSqlDatabase MainWindow::checkConnection(QString strDatabaseHost, QString strDatabaseAddress,QSqlDatabase database,QString mDatabaseName)
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

//Check every connection of the database
void MainWindow::slotCheckConnection()
{
    QString strHost = "";
    QString strAddress = "";
    QString strDatabaseName = "";
    QSettings settings(m_sIniFilePath,QSettings::IniFormat);

    strDatabaseName = "Erp";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseERP = checkConnection(strHost,strAddress,m_DatabaseERP,strDatabaseName);
    if (m_DatabaseERP.isOpen()) {
        m_flagErp = true;
        ui->pushButton->setEnabled(true);
    } else {
        m_flagErp = false;
        ui->pushButton->setEnabled(false);
    }

    strDatabaseName = "POS1";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap1 = checkConnection(strHost,strAddress,m_DatabaseVentap1,strDatabaseName);
    if (m_DatabaseVentap1.isOpen()) {
        m_flag1 = true;
        ui->pushButton_1->setStyleSheet("#button1 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag1 = false;
        ui->pushButton_1->setStyleSheet("#button1 {border:1px solid rgb(255,0,0)}");
    }

    strDatabaseName = "POS2";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap2 = checkConnection(strHost,strAddress,m_DatabaseVentap2,strDatabaseName);
    if (m_DatabaseVentap2.isOpen()) {
        m_flag2 = true;
        ui->pushButton_2->setStyleSheet("#button2 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag2 = false;
        ui->pushButton_2->setStyleSheet("#button2 {border:1px solid rgb(255,0,0)}");
    }

    strDatabaseName = "POS3";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap3 = checkConnection(strHost,strAddress,m_DatabaseVentap3,strDatabaseName);
    if (m_DatabaseVentap3.isOpen()) {
        m_flag3 = true;
        ui->pushButton_3->setStyleSheet("#button3 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag3 = false;
        ui->pushButton_3->setStyleSheet("#button3 {border:1px solid rgb(255,0,0)}");
    }

    strDatabaseName = "POS4";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap4 = checkConnection(strHost,strAddress,m_DatabaseVentap4,strDatabaseName);
    if (m_DatabaseVentap4.isOpen()) {
        m_flag4 = true;
        ui->pushButton_4->setStyleSheet("#button4 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag4 = false;
        ui->pushButton_4->setStyleSheet("#button4 {border:1px solid rgb(255,0,0)}");
    }

    strDatabaseName = "POS5";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap5 = checkConnection(strHost,strAddress,m_DatabaseVentap5,strDatabaseName);
    if (m_DatabaseVentap5.isOpen()) {
        m_flag5 = true;
        ui->pushButton_5->setStyleSheet("#button5 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag5 = false;
        ui->pushButton_5->setStyleSheet("#button5 {border:1px solid rgb(255,0,0)}");
    }

    strDatabaseName = "POS6";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap6 = checkConnection(strHost,strAddress,m_DatabaseVentap6,strDatabaseName);
    if (m_DatabaseVentap6.isOpen()) {
        m_flag6 = true;
        ui->pushButton_6->setStyleSheet("#button6 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag6 = false;
        ui->pushButton_6->setStyleSheet("#button6 {border:1px solid rgb(255,0,0)}");
    }

    strDatabaseName = "POS7";
    settings.beginGroup(strDatabaseName);
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    m_DatabaseVentap7 = checkConnection(strHost,strAddress,m_DatabaseVentap7,strDatabaseName);
    if (m_DatabaseVentap7.isOpen()) {
        m_flag7 = true;
        ui->pushButton_7->setStyleSheet("#button7 {border:1px solid rgb(0,255,0)}");
    } else {
        m_flag7 = false;
        ui->pushButton_7->setStyleSheet("#button7 {border:1px solid rgb(255,0,0)}");
    }

}

//Once the button Search is clicked
void MainWindow::on_pushButton_clicked()
{
    //Clean the data
    m_iIndexVentap.clear();
    m_strListPrdRef.clear();
    m_strListPrdDesc.clear();
    m_dListPrdCnt.clear();
    m_dListPrdTotal.clear();

    //Get the datetime limited
    QDateTime dateTime1 = ui->dateEdit->dateTime();
    qint64 time_t1 = dateTime1.toTime_t();
    QDateTime dateTime2 = ui->dateEdit_2->dateTime();
    qint64 time_t2 = dateTime2.toTime_t();

    //Initialization of the parameters
    QString productRef = "";
    QString productDesc = "";

    //******************************ERP********************************************
    //Invoice
    QSqlQueryModel *pModelErpInv = new QSqlQueryModel();
//    QString sqlErpInv = "SELECT VIEW_VT_PRD.ID,VIEW_VT_PRD.REFERENCE,VIEW_VT_PRD.DESCRIPTION, "
//            "SUM(CUS_INVOICE_DETAIL.INVOICE_COUNT) AS CNT,SUM(CUS_INVOICE_DETAIL.INVOICE_FIN_PRICE) AS TOTAL "
//            "FROM CUS_INVOICE_BILL "
//            "INNER JOIN CUS_INVOICE_DETAIL ON CUS_INVOICE_DETAIL.INVOICE_ID = CUS_INVOICE_BILL.INVOICE_ID "
//            "INNER JOIN VIEW_VT_PRD ON VIEW_VT_PRD.ID = CUS_INVOICE_DETAIL.PRODUCT_ID "
//            "WHERE DATEDIFF(second, timestamp '1/1/1970 00:00:00', CUS_INVOICE_BILL.INVOICE_DATE) > ? "
//            "AND DATEDIFF(second, timestamp '1/1/1970 00:00:00', CUS_INVOICE_BILL.INVOICE_DATE) < ? "
//            "GROUP BY VIEW_VT_PRD.ID,VIEW_VT_PRD.REFERENCE,VIEW_VT_PRD.DESCRIPTION";
    QString sqlErpInv = "SELECT VIEW_VT_PRD.ID,VIEW_VT_PRD.REFERENCE,VIEW_VT_PRD.DESCRIPTION, "
                        "CUS_INVOICE_DETAIL.INVOICE_COUNT,CUS_INVOICE_DETAIL.INVOICE_UNIT_COUNT,CUS_INVOICE_DETAIL.INVOICE_FIN_PRICE "
                        "FROM CUS_INVOICE_BILL "
                        "INNER JOIN CUS_INVOICE_DETAIL ON CUS_INVOICE_DETAIL.INVOICE_ID = CUS_INVOICE_BILL.INVOICE_ID "
                        "INNER JOIN VIEW_VT_PRD ON VIEW_VT_PRD.ID = CUS_INVOICE_DETAIL.PRODUCT_ID "
                        "WHERE DATEDIFF(second, timestamp '1/1/1970 00:00:00', CUS_INVOICE_BILL.INVOICE_DATE) > ? "
                        "AND DATEDIFF(second, timestamp '1/1/1970 00:00:00', CUS_INVOICE_BILL.INVOICE_DATE) < ?";
    pModelErpInv = this->execSqlErp(m_DatabaseERP,sqlErpInv,time_t1,time_t2,pModelErpInv,m_flagErp);

    //Supplier
    QSqlQueryModel *pModelErpSup = new QSqlQueryModel();
    QString sqlErpSup = "SELECT VIEW_VT_PRD.ID,VIEW_VT_PRD.REFERENCE,VIEW_VT_PRD.DESCRIPTION, "
                        "SUP_DELIVERY_DETAIL.DELIVERY_COUNT,SUP_DELIVERY_DETAIL.DELIVERY_UNIT_COUNT,SUP_DELIVERY_DETAIL.DELIVERY_FIN_PRICE "
                        "FROM SUP_DELIVERY_BILL "
                        "INNER JOIN SUP_DELIVERY_DETAIL ON SUP_DELIVERY_DETAIL.DELIVERY_ID = SUP_DELIVERY_BILL.DELIVERY_ID "
                        "INNER JOIN VIEW_VT_PRD ON VIEW_VT_PRD.ID = SUP_DELIVERY_DETAIL.PRODUCT_ID "
                        "WHERE DATEDIFF(second, timestamp '1/1/1970 00:00:00', SUP_DELIVERY_BILL.DELIVERY_DATE) > ? "
                        "AND DATEDIFF(second, timestamp '1/1/1970 00:00:00', SUP_DELIVERY_BILL.DELIVERY_DATE) < ? ";

    pModelErpSup = this->execSqlErp(m_DatabaseERP,sqlErpSup,time_t1,time_t2,pModelErpSup,m_flagErp);

    //******************************Ventap*****************************************
    QSqlQueryModel *pModel1 = new QSqlQueryModel();
    QSqlQueryModel *pModel2 = new QSqlQueryModel();
    QSqlQueryModel *pModel3 = new QSqlQueryModel();
    QSqlQueryModel *pModel4 = new QSqlQueryModel();
    QSqlQueryModel *pModel5 = new QSqlQueryModel();
    QSqlQueryModel *pModel6 = new QSqlQueryModel();
    QSqlQueryModel *pModel7 = new QSqlQueryModel();
    QString sqlVentap = "SELECT T_TICKET_DETAIL.PRD_REF,T_TICKET_DETAIL.PRD_ORG,SUM(T_TICKET_DETAIL.CNT) AS CNT,SUM(T_TICKET_DETAIL.TOTAL_TTC) AS TOTAL "
                  "FROM T_TICKET "
                  "INNER JOIN T_TICKET_DETAIL ON T_TICKET.ID = T_TICKET_DETAIL.TICKET_ID "
                  "WHERE DATEDIFF(second, timestamp '1/1/1970 00:00:00', T_TICKET.order_datetime) > ? "
                  "AND DATEDIFF(second, timestamp '1/1/1970 00:00:00', T_TICKET.order_datetime) <= ? "
                  "GROUP BY T_TICKET_DETAIL.PRD_REF,T_TICKET_DETAIL.PRD_ORG";

    pModel1 = this->execSqlVentap(m_DatabaseVentap1,sqlVentap,time_t1,time_t2,pModel1,m_flag1);
    pModel2 = this->execSqlVentap(m_DatabaseVentap2,sqlVentap,time_t1,time_t2,pModel2,m_flag2);
    pModel3 = this->execSqlVentap(m_DatabaseVentap3,sqlVentap,time_t1,time_t2,pModel3,m_flag3);
    pModel4 = this->execSqlVentap(m_DatabaseVentap4,sqlVentap,time_t1,time_t2,pModel4,m_flag4);
    pModel5 = this->execSqlVentap(m_DatabaseVentap5,sqlVentap,time_t1,time_t2,pModel5,m_flag5);
    pModel6 = this->execSqlVentap(m_DatabaseVentap6,sqlVentap,time_t1,time_t2,pModel6,m_flag6);
    pModel7 = this->execSqlVentap(m_DatabaseVentap7,sqlVentap,time_t1,time_t2,pModel7,m_flag7);

    QList<QSqlQueryModel*> modelListVentap;
    modelListVentap.clear();
    if (m_flag1) {modelListVentap.append(pModel1);}
    if (m_flag2) {modelListVentap.append(pModel2);}
    if (m_flag3) {modelListVentap.append(pModel3);}
    if (m_flag4) {modelListVentap.append(pModel4);}
    if (m_flag5) {modelListVentap.append(pModel5);}
    if (m_flag6) {modelListVentap.append(pModel6);}
    if (m_flag7) {modelListVentap.append(pModel7);}

    //this->updateTableView(modelListVentap);

    //Create a new table T_VT_PRD_STAT and put the infos in the database
    this->createNewTableErp(modelListVentap,pModelErpInv,pModelErpSup);

    ui->pushButtonExport->setEnabled(true);
}

//Create a new table T_VT_PRD_STAT
void MainWindow::createNewTableErp(QList<QSqlQueryModel*> modelListVentap,QSqlQueryModel *pModelErpInv,QSqlQueryModel *pModelErpSup)
{
    QSqlQuery query(m_DatabaseERP);
    QString sql = "CREATE TABLE T_VT_PRD_STAT ( "
                "PRD_ID CHAR(32), "
                "PRD_REF VARCHAR(20), "
                "PRD_DESC VARCHAR(200), "
                "SUP_CNT DECIMAL(15,4), "
                "SUP_TOTAL DECIMAL(9,2), "
                "INV_CNT DECIMAL(15,4), "
                "INV_TOTAL DECIMAL(9,2), "
                "TCK_CNT DECIMAL(15,4), "
                "TCK_TOTAL DECIMAL(9,2) "
            ")";
    query.prepare(sql);

    sql = "DELETE FROM T_VT_PRD_STAT";
    query.prepare(sql);

    //Insert the infos of the ventaps into the database
    QString temp = "";
    double dTemp = 0.00;
    sql = "INSERT INTO T_VT_PRD_STAT "
          "(PRD_ID, PRD_REF, PRD_DESC, SUP_CNT, SUP_TOTAL, INV_CNT, INV_TOTAL, TCK_CNT, TCK_TOTAL) "
          "VALUES('', ?, ?, 0, 0, 0, 0, ?, ?)";
    QList<QString> qList;
    for (int i = 0;i < modelListVentap.size(); i++) {
        QSqlQueryModel *pModel = modelListVentap.at(i);
        int rows = pModel->rowCount();
        for (int row = 0; row < rows; row++) {
            qList.clear();
            for (int column = 0; column < 4; column++) {
                if (column < 2) {
                    temp = pModel->data(pModel->index(row,column)).toString();
                } else {
                    dTemp = pModel->data(pModel->index(row,column)).toDouble();
                    temp = QString::number(dTemp,10,2);
                }
                qList.append(temp);
            }
            query.prepare(sql);
            query.bindValue(0,qList.at(0));
            query.bindValue(1,qList.at(1));
            query.bindValue(2,qList.at(2).toDouble());
            query.bindValue(3,qList.at(3).toDouble());
            query.exec();
        }
    }

    //Insert the infos of the Erp invoice into the database
    temp = "";
    dTemp = 0.00;
    double dCount = 0.00;
    double dUnitCount = 0.00;
    double dFinPrice = 0.00;
    sql = "INSERT INTO T_VT_PRD_STAT "
          "(PRD_ID, PRD_REF, PRD_DESC, SUP_CNT, SUP_TOTAL, INV_CNT, INV_TOTAL, TCK_CNT, TCK_TOTAL) "
          "VALUES(?, ?, ?, 0, 0, ?, ?, 0, 0)";
    int rows = pModelErpInv->rowCount();
    for (int row = 0; row < rows;row++) {
        qList.clear();
        for (int column = 0; column < 5; column++) {
            if (column < 3) {
                temp = pModelErpInv->data(pModelErpInv->index(row,column)).toString();
            } else {
                if (column == 3) {
                    dCount = pModelErpInv->data(pModelErpInv->index(row,column)).toDouble();
                    dUnitCount = pModelErpInv->data(pModelErpInv->index(row,column+1)).toDouble();
                    dTemp = dCount * dUnitCount;
                    temp = QString::number(dTemp,10,2);
                }
                if (column == 4) {
                    dCount = pModelErpInv->data(pModelErpInv->index(row,column - 1)).toDouble();
                    dUnitCount = pModelErpInv->data(pModelErpInv->index(row,column)).toDouble();
                    dFinPrice = pModelErpInv->data(pModelErpInv->index(row,column+1)).toDouble();
                    dTemp = dCount * dUnitCount * dFinPrice;
                    temp = QString::number(dTemp,10,2);
                }
            }
            qList.append(temp);
        }
        query.prepare(sql);
        query.bindValue(0,qList.at(0));
        query.bindValue(1,qList.at(1));
        query.bindValue(2,qList.at(2));
        query.bindValue(3,qList.at(3).toDouble());
        query.bindValue(4,qList.at(4).toDouble());
        query.exec();
    }

    //Insert the infos of the Erp Supplier into the database
    temp = "";
    dTemp = 0.00;
    sql = "INSERT INTO T_VT_PRD_STAT "
          "(PRD_ID, PRD_REF, PRD_DESC, SUP_CNT, SUP_TOTAL, INV_CNT, INV_TOTAL, TCK_CNT, TCK_TOTAL) "
          "VALUES(?, ?, ?, ?, ?, 0, 0, 0, 0)";
    rows = pModelErpSup->rowCount();
    for (int row = 0; row < rows;row++) {
        qList.clear();
        for (int column = 0; column < 5; column++) {
            if (column < 3) {
                temp = pModelErpSup->data(pModelErpSup->index(row,column)).toString();
            } else {
                if (column == 3) {
                    dCount = pModelErpInv->data(pModelErpInv->index(row,column)).toDouble();
                    dUnitCount = pModelErpInv->data(pModelErpInv->index(row,column+1)).toDouble();
                    dTemp = dCount * dUnitCount;
                    temp = QString::number(dTemp,10,2);
                }
                if (column == 4) {
                    dCount = pModelErpInv->data(pModelErpInv->index(row,column - 1)).toDouble();
                    dUnitCount = pModelErpInv->data(pModelErpInv->index(row,column)).toDouble();
                    dFinPrice = pModelErpInv->data(pModelErpInv->index(row,column+1)).toDouble();
                    dTemp = dCount * dUnitCount * dFinPrice;
                    temp = QString::number(dTemp,10,2);
                }
            }
            qList.append(temp);
        }
        query.prepare(sql);
        query.bindValue(0,qList.at(0));
        query.bindValue(1,qList.at(1));
        query.bindValue(2,qList.at(2));
        query.bindValue(3,qList.at(3).toDouble());
        query.bindValue(4,qList.at(4).toDouble());
        query.exec();
    }


    sql = "SELECT PRD_REF, PRD_DESC, SUM(SUP_CNT) AS SUP_CNT, "
          "SUM(SUP_TOTAL) AS SUP_TOTAL, "
          "SUM(INV_CNT) AS INV_CNT, "
          "SUM(INV_TOTAL) AS INV_TOTAL, "
          "SUM(TCK_CNT) AS TCK_CNT, "
          "SUM(TCK_TOTAL) AS TCK_TOTAL "
          "FROM T_VT_PRD_STAT "
          "GROUP BY PRD_REF, PRD_DESC" ;
    query.prepare(sql);
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setHeaderData(2,Qt::Horizontal,"SUP_CNT");
    model->setHeaderData(3,Qt::Horizontal,"SUP_TOTAL");
    model->setHeaderData(4,Qt::Horizontal,"INV_CNT");
    model->setHeaderData(5,Qt::Horizontal,"INV_TOTAL");
    model->setHeaderData(6,Qt::Horizontal,"TCK_CNT");
    model->setHeaderData(7,Qt::Horizontal,"TCK_TOTAL");
    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(1,250);
}

//Update the tableView, not used in this programme now
void MainWindow::updateTableView(QList<QSqlQueryModel*> modelListVentap)
{
    QString temp = "";
    double dTemp = 0.00;
    int rowsTotal = 0;
    QList<int> iListRowsVentap;

    //Get the rows totals
    for (int i=0;i < modelListVentap.size();i++){
        QSqlQueryModel *pModelTemp = modelListVentap.at(i);
        int row = pModelTemp->rowCount();
        iListRowsVentap.append(row);
        rowsTotal = rowsTotal + row;
    }

    int rowsTemp = 0;
    QStandardItemModel *tableModel = new QStandardItemModel(rowsTotal,4);
    tableModel->setHeaderData(0,Qt::Horizontal,"PRD_REF");
    tableModel->setHeaderData(1,Qt::Horizontal,"PRD_DESC");
    tableModel->setHeaderData(2,Qt::Horizontal,"PRD_CNT");
    tableModel->setHeaderData(3,Qt::Horizontal,"PRD_TOTAL");
    for (int i = 0;i < modelListVentap.size(); i++) {
        QSqlQueryModel *pModel = modelListVentap.at(i);
        int rows = pModel->rowCount();
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < 4; column++) {
                if (column < 2) {
                    temp = pModel->data(pModel->index(row,column)).toString();
                } else {
                    dTemp = pModel->data(pModel->index(row,column)).toDouble();
                    temp = QString::number(dTemp,10,2);
                }
                QStandardItem *item = new QStandardItem(temp);
                tableModel->setItem(row + rowsTemp,column,item);
            }
        }
        rowsTemp = rowsTemp + rows;
    }
    //ui->tableView->setModel(tableModel);
    //ui->tableView_2->setModel(tableModel);
}

QSqlQueryModel* MainWindow::execSqlErp(QSqlDatabase database,QString sqlErp,qint64 time_t1,qint64 time_t2,
                                       QSqlQueryModel *model,bool flag)
{
    QString productRef = "";
    QString productDesc = "";
    double productCnt = 0.00;
    double productTotal = 0.00;
    int i = 0;

    QStringList strListPrdRef,strListPrdDesc;
    QList<double> dListPrdCnt,dListPrdTotal;
    QList<int> iIndexVentap;
    if (flag) {
        QSqlQuery query(database);
        query.prepare(sqlErp);
        query.bindValue(0,time_t1);
        query.bindValue(1,time_t2);
        query.exec();
        while (query.next()) {
            iIndexVentap.append(i);
            productRef = query.value(1).toString();
            strListPrdRef.append(productRef);
            productDesc = query.value(2).toString();
            strListPrdDesc.append(productDesc);
            productCnt = query.value(3).toDouble();
            dListPrdCnt.append(productCnt);
            productTotal = query.value(4).toDouble();
            dListPrdTotal.append(productTotal);
            i++;
        }
        model->setQuery(query);
        return model;
    } else {
        return NULL;
    }
}

//For every ventap, get the infos of the product
QSqlQueryModel* MainWindow::execSqlVentap(QSqlDatabase database,QString sqlVentap,qint64 time_t1,qint64 time_t2,
                                         QSqlQueryModel *model,bool flag)
{
    QString productRef = "";
    QString productDesc = "";
    double productCnt = 0.00;
    double productTotal = 0.00;
    int i = 0;

    QStringList strListPrdRef,strListPrdDesc;
    QList<double> dListPrdCnt,dListPrdTotal;
    QList<int> iIndexVentap;
    if (flag) {
        QSqlQuery query(database);
        query.prepare(sqlVentap);
        query.bindValue(0,time_t1);
        query.bindValue(1,time_t2);
        query.exec();
        while (query.next()) {
            iIndexVentap.append(i);
            productRef = query.value(0).toString();
            strListPrdRef.append(productRef);
            productDesc = query.value(1).toString();
            strListPrdDesc.append(productDesc);
            productCnt = query.value(2).toDouble();
            dListPrdCnt.append(productCnt);
            productTotal = query.value(3).toDouble();
            dListPrdTotal.append(productTotal);
            i++;
        }
        model->setQuery(query);
        return model;
    } else {
        return NULL;
    }
}

//Export the data into the file .xlsx
void MainWindow::on_pushButtonExport_clicked()
{
    QString strFilePath = "";
    bool flag = false;
    QFileDialog *pFileDialog = new QFileDialog(this);
    pFileDialog->setWindowTitle(tr("Save As"));
    pFileDialog->setAcceptMode(QFileDialog::AcceptSave);
    pFileDialog->setViewMode(QFileDialog::Detail);
    pFileDialog->setDirectory(".");
    pFileDialog->setNameFilter(tr("Xlsx Files(*.xlsx)"));
    if (pFileDialog->exec() == QDialog::Accepted) {
        strFilePath = pFileDialog->selectedFiles().at(0);
        QFile file(strFilePath);
        if (file.exists()) {
            file.remove();
        }
        QAbstractItemModel *pModel = ui->tableView->model();
        int rows = pModel->rowCount();
        int columns = pModel->columnCount();
        QString strRow = "";
        QString strColumn = "";
        QString temp = "";
        double dTemp = 0.00;
        QXlsx::Document doc(strFilePath);
        doc.write("A1","Product Ref");
        doc.write("B1","Product Desc");
        doc.write("C1","Sup Cnt");
        doc.write("D1","Sup Total");
        doc.write("E1","Invoice Cnt");
        doc.write("F1","Invoice Total");
        doc.write("G1","Ticket Cnt");
        doc.write("H1","Ticket Total");
        for (int row = 0; row < rows; row++){
            for (int column = 0; column < columns; column++) {
                strRow = QString::number(row + 2);
                strColumn = QString(column + 65);
                if (column < 2) {
                    temp = pModel->data(pModel->index(row,column)).toString();
                    doc.write(strColumn + strRow,temp);
                } else {
                    dTemp = pModel->data(pModel->index(row,column)).toDouble();
                    doc.write(strColumn + strRow,dTemp);
                }
            }
        }
        flag = doc.save();
    }
    if (flag) {
        QMessageBox::about(NULL,"INFO","File saved successfully!");
    }
}
