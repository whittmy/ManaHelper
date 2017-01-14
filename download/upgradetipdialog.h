#ifndef UPGRADETIPDIALOG_H
#define UPGRADETIPDIALOG_H

#include <QDialog>
#include "util/logme.h"
#include "util/xml_parser_upgrade.h"
#include "util/appendix.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class UpgradeTipDialog;
}

class UpgradeTipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpgradeTipDialog(QWidget *parent = 0);
    ~UpgradeTipDialog();

    void setData(REQ_TYPE type, Xml_Parser_Upgrade *dp);

private slots:
    void on__btnUpgrade_clicked();
    void on__btnCancel_clicked();

    void dl_finished();
    void dl_progress(qint64 recv, qint64 total);
    void dl_error(QNetworkReply::NetworkError err);
    void dl_readReady(QNetworkReply* reply);

protected:
    void closeEvent(QCloseEvent * event);
private:
    QNetworkAccessManager *mNetMgr;
    QNetworkReply* mReply;

    Ui::UpgradeTipDialog *ui;
    LogMe *_logger;
    REQ_TYPE mType;
    Xml_Parser_Upgrade *_dp;
};

#endif // UPGRADETIPDIALOG_H
