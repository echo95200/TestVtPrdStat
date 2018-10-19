#include "dialogsetting.h"
#include "ui_dialogsetting.h"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);
    m_sIniFilePath = QApplication::applicationDirPath() + QDir::separator() + "VtPrdStat.ini";
    this->refreshPageSetting();
    ui->pushButtonConfirm->setFocus();
}

DialogSetting::~DialogSetting()
{
    delete ui;
}

void DialogSetting::on_pushButtonCancel_clicked()
{
    this->close();
    this->refreshPageSetting();
}

void DialogSetting::on_pushButtonConfirm_clicked()
{
    this->saveSettings();
    emit signalSettingConfirm();
    this->close();
}

void DialogSetting::saveSettings()
{
    m_StrList.clear();
    QString strHost = "";
    QString strAddress = "";

    strHost = ui->lineEditPosHost1->text();
    strAddress = ui->lineEditPosAddress1->text();
    QSettings settings(m_sIniFilePath,QSettings::IniFormat);
    settings.beginGroup("POS1");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditPosHost2->text();
    strAddress = ui->lineEditPosAddress2->text();
    settings.beginGroup("POS2");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditPosHost3->text();
    strAddress = ui->lineEditPosAddress3->text();
    settings.beginGroup("POS3");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditPosHost4->text();
    strAddress = ui->lineEditPosAddress4->text();
    settings.beginGroup("POS4");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditPosHost5->text();
    strAddress = ui->lineEditPosAddress5->text();
    settings.beginGroup("POS5");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditPosHost6->text();
    strAddress = ui->lineEditPosAddress6->text();
    settings.beginGroup("POS6");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditPosHost7->text();
    strAddress = ui->lineEditPosAddress7->text();
    settings.beginGroup("POS7");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

    strHost = ui->lineEditErpHost->text();
    strAddress = ui->lineEditErpAddress->text();
    settings.beginGroup("Erp");
    settings.setValue("Host",strHost);
    settings.setValue("Address",strAddress);
    settings.endGroup();
    m_StrList.append(strHost);
    m_StrList.append(strAddress);

}

void DialogSetting::refreshPageSetting()
{
    QString strHost = "";
    QString strAddress = "";
    QSettings settings(m_sIniFilePath,QSettings::IniFormat);

    settings.beginGroup("POS1");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost1->setText(strHost);
    ui->lineEditPosAddress1->setText(strAddress);

    settings.beginGroup("POS2");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost2->setText(strHost);
    ui->lineEditPosAddress2->setText(strAddress);

    settings.beginGroup("POS3");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost3->setText(strHost);
    ui->lineEditPosAddress3->setText(strAddress);

    settings.beginGroup("POS4");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost4->setText(strHost);
    ui->lineEditPosAddress4->setText(strAddress);

    settings.beginGroup("POS5");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost5->setText(strHost);
    ui->lineEditPosAddress5->setText(strAddress);

    settings.beginGroup("POS6");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost6->setText(strHost);
    ui->lineEditPosAddress6->setText(strAddress);

    settings.beginGroup("POS7");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditPosHost7->setText(strHost);
    ui->lineEditPosAddress7->setText(strAddress);

    settings.beginGroup("Erp");
    strHost = settings.value("Host").toString();
    strAddress = settings.value("Address").toString();
    settings.endGroup();
    ui->lineEditErpHost->setText(strHost);
    ui->lineEditErpAddress->setText(strAddress);

}
