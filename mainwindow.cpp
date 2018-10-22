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
    ui->pushButton->setEnabled(false);
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
    //ui->tableView->verticalHeader()->hide();

    ui->progressBar->hide();

    m_pDialogSetting = new DialogSetting();
    m_sIniFilePath = QApplication::applicationDirPath() + QDir::separator() + "VtPrdStat.ini";
    connect(m_pDialogSetting,SIGNAL(signalSettingConfirm()),this,SLOT(slotSettingConfirm()));

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

//Everytime the configuration of the setting has changed
void MainWindow::slotSettingConfirm()
{
    ui->pushButton->setEnabled(false);
}

//When the button setting is clicked
void MainWindow::on_pushButtonSetting_clicked()
{
    m_pDialogSetting->show();
}

//When the button start is clicked
void MainWindow::on_pushButtonCheck_clicked()
{
    m_iThreadFinishedCount = 0;
    m_iThreadNumber = 0;
    ui->labelInfo->setText("Ready to Start!");
    QCoreApplication::processEvents();
    this->slotCheckConnection();
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

//Everytime click the button start, check the connection with the database
void MainWindow::slotCheckConnection(bool flag,int index)
{
    ui->labelInfo->setText("Checking the connection with database, please wait a minute!");
    if (index == 0) {
        m_flagErp = flag;
        ui->labelInfo->setText("Checking the connection with Pos1");
        QCoreApplication::processEvents();
    }
    if (index == 1) {
        m_flag1 = flag;
        ui->labelInfo->setText("Checking the connection with Pos2");
        QCoreApplication::processEvents();
    }
    if (index == 2) {
        m_flag2 = flag;
        ui->labelInfo->setText("Checking the connection with Pos3");
        QCoreApplication::processEvents();
    }
    if (index == 3) {
        m_flag3 = flag;
        ui->labelInfo->setText("Checking the connection with Pos4");
        QCoreApplication::processEvents();
    }
    if (index == 4) {
        m_flag4 = flag;
        ui->labelInfo->setText("Checking the connection with Pos5");
        QCoreApplication::processEvents();
    }
    if (index == 5) {
        m_flag5 = flag;
        ui->labelInfo->setText("Checking the connection with Pos6");
        QCoreApplication::processEvents();
    }
    if (index == 6) {
        m_flag6 = flag;
        ui->labelInfo->setText("Checking the connection with Pos7");
        QCoreApplication::processEvents();
    }
    if (index == 7) {
        m_flag7 = flag;
        ui->labelInfo->setText("Checking the connection with database finished!");
        QCoreApplication::processEvents();
    }
}

void MainWindow::slotCheckConnectionFinished()
{
    QString strHost = "";
    QString strAddress = "";
    QString strDatabaseName = "";
    QSettings settings(m_sIniFilePath,QSettings::IniFormat);

    if (m_flagErp) {
        strDatabaseName = "Erp";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the Erp");
        QCoreApplication::processEvents();
        m_DatabaseERP = checkConnection(strHost,strAddress,m_DatabaseERP,strDatabaseName);
        if (m_DatabaseERP.isOpen()) {
            m_flagErp = this->initDatabase();
            if (m_flagErp) {
                ui->pushButton->setEnabled(true);
                ui->labelInfo->setText("Connecting with the Erp successful");
                QCoreApplication::processEvents();
            } else {
                ui->labelInfo->setText("Initialization of the database failed");
                QCoreApplication::processEvents();
            }
        } else {
            m_flagErp = false;
            ui->pushButton->setEnabled(false);
            ui->labelInfo->setText("Connecting the Erp failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag1) {
        strDatabaseName = "POS1";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap1 = checkConnection(strHost,strAddress,m_DatabaseVentap1,strDatabaseName);
        if (m_DatabaseVentap1.isOpen()) {
            m_flag1 = true;
            ui->pushButton_1->setStyleSheet("#button1 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag1 = false;
            ui->pushButton_1->setStyleSheet("#button1 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag2) {
        strDatabaseName = "POS2";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap2 = checkConnection(strHost,strAddress,m_DatabaseVentap2,strDatabaseName);
        if (m_DatabaseVentap2.isOpen()) {
            m_flag2 = true;
            ui->pushButton_2->setStyleSheet("#button2 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag2 = false;
            ui->pushButton_2->setStyleSheet("#button2 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag3) {
        strDatabaseName = "POS3";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap3 = checkConnection(strHost,strAddress,m_DatabaseVentap3,strDatabaseName);
        if (m_DatabaseVentap3.isOpen()) {
            m_flag3 = true;
            ui->pushButton_3->setStyleSheet("#button3 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag3 = false;
            ui->pushButton_3->setStyleSheet("#button3 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag4) {
        strDatabaseName = "POS4";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap4 = checkConnection(strHost,strAddress,m_DatabaseVentap4,strDatabaseName);
        if (m_DatabaseVentap4.isOpen()) {
            m_flag4 = true;
            ui->pushButton_4->setStyleSheet("#button4 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag4 = false;
            ui->pushButton_4->setStyleSheet("#button4 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag5) {
        strDatabaseName = "POS5";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap5 = checkConnection(strHost,strAddress,m_DatabaseVentap5,strDatabaseName);
        if (m_DatabaseVentap5.isOpen()) {
            m_flag5 = true;
            ui->pushButton_5->setStyleSheet("#button5 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag5 = false;
            ui->pushButton_5->setStyleSheet("#button5 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag6) {
        strDatabaseName = "POS6";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connecting with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap6 = checkConnection(strHost,strAddress,m_DatabaseVentap6,strDatabaseName);
        if (m_DatabaseVentap6.isOpen()) {
            m_flag6 = true;
            ui->pushButton_6->setStyleSheet("#button6 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag6 = false;
            ui->pushButton_6->setStyleSheet("#button6 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    if (m_flag7) {
        strDatabaseName = "POS7";
        settings.beginGroup(strDatabaseName);
        strHost = settings.value("Host").toString();
        strAddress = settings.value("Address").toString();
        settings.endGroup();
        ui->labelInfo->setText("Connect with the " + strDatabaseName);
        QCoreApplication::processEvents();
        m_DatabaseVentap7 = checkConnection(strHost,strAddress,m_DatabaseVentap7,strDatabaseName);
        if (m_DatabaseVentap7.isOpen()) {
            m_flag7 = true;
            ui->pushButton_7->setStyleSheet("#button7 {border:1px solid rgb(0,255,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " successful");
            QCoreApplication::processEvents();
        } else {
            m_flag7 = false;
            ui->pushButton_7->setStyleSheet("#button7 {border:1px solid rgb(255,0,0)}");
            ui->labelInfo->setText("Connect with the " + strDatabaseName + " failed");
            QCoreApplication::processEvents();
        }
    }

    QString strResult = "Connection finished : ";
    if (m_flag1) {strResult.append(" Pos1");}
    if (m_flag2) {strResult.append(" Pos2");}
    if (m_flag3) {strResult.append(" Pos3");}
    if (m_flag4) {strResult.append(" Pos4");}
    if (m_flag5) {strResult.append(" Pos5");}
    if (m_flag6) {strResult.append(" Pos6");}
    if (m_flag7) {strResult.append(" Pos7");}
    strResult.append(" successful. Ready to search...");
    ui->labelInfo->setText(strResult);
    QCoreApplication::processEvents();
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);

}

//Check every connection of the database
void MainWindow::slotCheckConnection()
{
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    QCoreApplication::processEvents();
    m_flag1 = false;
    m_flag2 = false;
    m_flag3 = false;
    m_flag4 = false;
    m_flag5 = false;
    m_flag6 = false;
    m_flag7 = false;

    //Add the thread to check the connection with the database
    QThread *thread = new QThread();
    ThreadSQLConnectionWorker *worker = new ThreadSQLConnectionWorker();
    worker->moveToThread(thread);
    connect(thread,SIGNAL(started()),worker,SLOT(process()));
    connect(worker,SIGNAL(finished()),thread,SLOT(quit()));
    connect(worker,SIGNAL(finished()),worker,SLOT(deleteLater()));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(worker,SIGNAL(signalSendResult(bool,int)),this,SLOT(slotCheckConnection(bool,int)));
    connect(worker,SIGNAL(finished()),this,SLOT(slotCheckConnectionFinished()));
    thread->start();

}

//Once the button Search is clicked
void MainWindow::on_pushButton_clicked()
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    QCoreApplication::processEvents();

    //Get the datetime limited
    QDate date1 = ui->dateEdit->date();
    QDate date2 = ui->dateEdit_2->date();

    //******************************ERP********************************************
    //Invoice
    QString sqlErpInv = "INSERT INTO T_VT_PRD_STAT (PRD_ID, PRD_REF, PRD_DESC, INV_CNT, INV_TOTAL) "
                        "SELECT PRODUCT.PRODUCT_ID,PRODUCT.PRODUCT_REFERENCE,PRODUCT.PRODUCT_NAME_1, "
                        "CUS_INVOICE_DETAIL.INVOICE_COUNT * CUS_INVOICE_DETAIL.INVOICE_UNIT_COUNT, "
                        "CUS_INVOICE_DETAIL.INVOICE_COUNT * CUS_INVOICE_DETAIL.INVOICE_UNIT_COUNT * CUS_INVOICE_DETAIL.INVOICE_FIN_PRICE "
                        "FROM CUS_INVOICE_BILL "
                        "INNER JOIN CUS_INVOICE_DETAIL ON CUS_INVOICE_DETAIL.INVOICE_ID = CUS_INVOICE_BILL.INVOICE_ID "
                        "INNER JOIN PRODUCT ON PRODUCT.PRODUCT_ID = CUS_INVOICE_DETAIL.PRODUCT_ID "
                        "WHERE CUS_INVOICE_BILL.INVOICE_DATE BETWEEN ? AND ?";
    ui->labelInfo->setText("Read the data from Erp Invoice...");
    QCoreApplication::processEvents();
    bool flagErpInv = this->execSqlErp(m_DatabaseERP,sqlErpInv,date1,date2);
    if (flagErpInv) {
        ui->labelInfo->setText("Read the data from Erp Invoice successful");
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(100);
        QCoreApplication::processEvents();
    } else {
        ui->labelInfo->setText("Read the data from Erp Invoice failed");
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(0);
        QCoreApplication::processEvents();
        return;
    }

    //Supplier
    QString sqlErpSup = "INSERT INTO T_VT_PRD_STAT (PRD_ID, PRD_REF, PRD_DESC, SUP_CNT, SUP_TOTAL) "
                        "SELECT PRODUCT.PRODUCT_ID,PRODUCT.PRODUCT_REFERENCE,PRODUCT.PRODUCT_NAME_1, "
                        "SUP_DELIVERY_DETAIL.DELIVERY_COUNT * SUP_DELIVERY_DETAIL.DELIVERY_UNIT_COUNT , "
                        "SUP_DELIVERY_DETAIL.DELIVERY_COUNT * SUP_DELIVERY_DETAIL.DELIVERY_UNIT_COUNT * SUP_DELIVERY_DETAIL.DELIVERY_FIN_PRICE "
                        "FROM SUP_DELIVERY_BILL "
                        "INNER JOIN SUP_DELIVERY_DETAIL ON SUP_DELIVERY_DETAIL.DELIVERY_ID = SUP_DELIVERY_BILL.DELIVERY_ID "
                        "INNER JOIN PRODUCT ON PRODUCT.PRODUCT_ID = SUP_DELIVERY_DETAIL.PRODUCT_ID "
                        "WHERE SUP_DELIVERY_BILL.DELIVERY_DATE BETWEEN ? AND ?";
    ui->labelInfo->setText("Read the data from Erp Invoice...");
    QCoreApplication::processEvents();
    bool flagErpSup = this->execSqlErp(m_DatabaseERP,sqlErpSup,date1,date2);
    if (flagErpSup) {
        ui->labelInfo->setText("Read the data from Sup Invoice successful");
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(100);
        QCoreApplication::processEvents();
    } else {
        ui->labelInfo->setText("Read the data from Sup Invoice failed");
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(0);
        QCoreApplication::processEvents();
        return;
    }

    ui->labelInfo->setText("Read... the data from Ventap");
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    QCoreApplication::processEvents();

    //******************************Ventap*****************************************
    if (m_flag1) {this->createThread(m_DatabaseVentap1,date1,date2,1);}
    if (m_flag2) {this->createThread(m_DatabaseVentap2,date1,date2,2);}
    if (m_flag3) {this->createThread(m_DatabaseVentap3,date1,date2,3);}
    if (m_flag4) {this->createThread(m_DatabaseVentap4,date1,date2,4);}
    if (m_flag5) {this->createThread(m_DatabaseVentap5,date1,date2,5);}
    if (m_flag6) {this->createThread(m_DatabaseVentap6,date1,date2,6);}
    if (m_flag7) {this->createThread(m_DatabaseVentap7,date1,date2,7);}

    if (m_iThreadNumber == 0) {
        this->showTableview();
    }
}

QThread* MainWindow::createThread(QSqlDatabase database,QDate date1,QDate date2,int iIndex)
{
    ui->labelInfo->setText("Create the thread" + QString::number(iIndex) + " to read the data from ventap" + QString::number(iIndex));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    QCoreApplication::processEvents();

    m_iThreadNumber++;
    QThread *pThread = new QThread();
    ThreadWorker *pWorker = new ThreadWorker(database,date1,date2,iIndex,m_DatabaseERP);
    pWorker->moveToThread(pThread);
    connect(pThread,SIGNAL(started()),pWorker,SLOT(slotProcess()));
    connect(pWorker,SIGNAL(signalFinished()),pWorker,SLOT(deleteLater()));
    connect(pWorker,SIGNAL(signalFinished()),pThread,SLOT(quit()));
    connect(pThread,SIGNAL(finished()),pThread,SLOT(deleteLater()));
    connect(pWorker,SIGNAL(signalSend(QSqlQueryModel *,int)),this,SLOT(slotRecevied(QSqlQueryModel *,int)));
    pThread->start();
    return pThread;
}

//Count the number of the thread finished
void MainWindow::slotRecevied(QSqlQueryModel *pModel,int index)
{
    m_iThreadFinishedCount++;
    if (m_iThreadFinishedCount == m_iThreadNumber) {
        this->showTableview();
        ui->labelInfo->setText("All threads are finished......");
        QCoreApplication::processEvents();
    } else {
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(m_iThreadNumber);
        ui->progressBar->setValue(m_iThreadFinishedCount);
        ui->labelInfo->setText("Read the data from ventap" + QString::number(index) + " finished!");
        QCoreApplication::processEvents();
    }
}

void MainWindow::showTableview()
{
    ui->labelInfo->setText("Reading the data from Table T_VT_PRD_STAT......");
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    QCoreApplication::processEvents();
    QSqlQuery query(m_DatabaseERP);
    QString sql = "SELECT PRD_DESC, SUM(SUP_CNT) AS SUP_CNT, "
          "SUM(SUP_TOTAL) AS SUP_TOTAL, "
          "SUM(INV_CNT) AS INV_CNT, "
          "SUM(INV_TOTAL) AS INV_TOTAL, "
          "SUM(TCK_CNT) AS TCK_CNT, "
          "SUM(TCK_TOTAL) AS TCK_TOTAL,"
          "SUM(SUP_CNT - INV_CNT - TCK_CNT) AS STOCK "
          "FROM T_VT_PRD_STAT "
          "GROUP BY PRD_DESC" ;
    query.prepare(sql);
    bool flagResult = query.exec();
    if (flagResult) {
        ui->labelInfo->setText("Read the data from Table T_VT_PRD_STAT successful!");
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(100);
        QCoreApplication::processEvents();
    } else {
        ui->labelInfo->setText("Read the data from Table T_VT_PRD_STAT failed!");
    }
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    while (model->canFetchMore()) {
        model->fetchMore();
    }
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,250);
    ui->labelInfo->setText("Search finished!");
    QCoreApplication::processEvents();
    ui->pushButton->setEnabled(false);
    ui->pushButtonExport->setEnabled(true);
}

//Initialization of the database
bool MainWindow::initDatabase()
{
    bool flag = false;
    QSqlQuery query(m_DatabaseERP);
    QString sqlCheckTableExists = "SELECT * FROM T_VT_PRD_STAT";
    QString sqlDeleteTable = "DELETE FROM T_VT_PRD_STAT";
    QString sqlCreateTable = "CREATE TABLE T_VT_PRD_STAT ( "
                "PRD_ID CHAR(32), "
                "PRD_REF VARCHAR(20), "
                "PRD_DESC VARCHAR(200), "
                "SUP_CNT DECIMAL(15,4) default 0.0000, "
                "SUP_TOTAL DECIMAL(9,2) default 0.00, "
                "INV_CNT DECIMAL(15,4) default 0.0000, "
                "INV_TOTAL DECIMAL(9,2) default 0.00, "
                "TCK_CNT DECIMAL(15,4) default 0.0000, "
                "TCK_TOTAL DECIMAL(9,2) default 0.00 "
            ")";
    query.prepare(sqlCheckTableExists);
    flag = query.exec();
    if (flag) {
        query.prepare(sqlDeleteTable);
        flag = query.exec();
        if (flag) {
            ui->labelInfo->setText("SQL Table was deleted successful!");
            QCoreApplication::processEvents();
            flag = true;
        } else {
            ui->labelInfo->setText("SQL Table was deleted failed!");
            QCoreApplication::processEvents();
            QMessageBox::about(NULL,"Error",query.lastError().text());
        }
    } else {
            query.prepare(sqlCreateTable);
            flag = query.exec();
            if (flag) {
                ui->labelInfo->setText("SQL Table was created successful!");
                QCoreApplication::processEvents();
                flag = true;
            } else {
                ui->labelInfo->setText("SQL Table was created failed!" + query.lastError().text());
                QCoreApplication::processEvents();
                QMessageBox::about(NULL,"Error",query.lastError().text());
            }
    }
    return flag;
}

bool MainWindow::execSqlErp(QSqlDatabase database,QString sqlErp,QDate date1,QDate date2)
{
    bool flag = false;
    QSqlQuery query(database);
    query.prepare(sqlErp);
    query.bindValue(0,date1);
    query.bindValue(1,date2);
    flag = query.exec();
    if (!flag) {
        QMessageBox::about(NULL,"Error",query.lastError().text());
    }
    return flag;
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
        doc.write("A1","Product Desc");
        doc.write("B1","Sup Cnt");
        doc.write("C1","Sup Total");
        doc.write("D1","Invoice Cnt");
        doc.write("E1","Invoice Total");
        doc.write("F1","Ticket Cnt");
        doc.write("G1","Ticket Total");
        doc.write("H1","Stock");
        for (int row = 0; row < rows; row++){
            for (int column = 0; column < columns; column++) {
                strRow = QString::number(row + 2);
                strColumn = QString(column + 65);
                if (column < 1) {
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
    } else {
        QMessageBox::about(NULL,"INFO","File saved failed!");
    }
}


