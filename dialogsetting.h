#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>
#include <QDir>
#include <QSettings>

namespace Ui {
class DialogSetting;
}

class DialogSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetting(QWidget *parent = 0);
    ~DialogSetting();

    void saveSettings();
    void refreshPageSetting();

signals:
    void signalSettingConfirm();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonConfirm_clicked();

private:
    Ui::DialogSetting *ui;

    QStringList m_StrList;
    QString m_sIniFilePath;
};

#endif // DIALOGSETTING_H
