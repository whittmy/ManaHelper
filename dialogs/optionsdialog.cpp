#include "dialogs/optionsdialog.h"
#include "dialogs/ui_optionsdialog.h"
#include <QFileDialog>
#include <QString>
#include <QSettings>
#include <QVariant>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    readSettings();
    ui->optionStacks->setCurrentIndex(0);
    ui->listWidget->setCurrentRow(0);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

//切换页面
void OptionsDialog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui->optionStacks->setCurrentIndex(ui->listWidget->row(current));
}

void OptionsDialog::on_pushButton_clicked()
{
    //general
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->generalDirectoryEdit->setText(seldir.first());
}

void OptionsDialog::on_pushButton_2_clicked()
{
    //documents
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->DocumentsDirectoryEdit->setText(seldir.first());
}

void OptionsDialog::on_pushButton_3_clicked()
{
    //music
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->MusicDirectoryEdit->setText(seldir.first());
}

void OptionsDialog::on_pushButton_5_clicked()
{
    //programs
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->ProgramsDirectoryEdit->setText(seldir.first());
}

void OptionsDialog::on_pushButton_4_clicked()
{
    //video
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->VideoDirectoryEdit->setText(seldir.first());
}

void OptionsDialog::readSettings()
{
    QSettings settings(this);
    //general start
    int maxRunningDownloads= settings.value("maxRunningDownloads").toInt();
    ui->maxTasksSpinBox->setValue(maxRunningDownloads);

    int ConnectionsPerDownload = settings.value("ConnectionsPerDownload").toInt();
    ui->ConnectionsPerDownloadSpinBox->setValue(ConnectionsPerDownload);

    bool showDownloadsComplete = settings.value("showDownloadsCompleteDialog").toBool();
    ui->showDownloadsCompleteDialogCheckbox->setChecked(showDownloadsComplete);

    bool  EnableSounds = settings.value("EnableSounds").toBool();
    ui->EnableSoundsCheckBox->setChecked(EnableSounds);
    //general end

    //saveto start
    QString generalLocation = settings.value("generalDirectory").toString();
    ui->generalDirectoryEdit->setText(generalLocation);

    QString CompressedLocation = settings.value("compressedDirectory").toString();
    ui->CompressedDirectoryEdit->setText(CompressedLocation);

    QString documentLocation = settings.value("documentDirectory").toString();
    ui->DocumentsDirectoryEdit->setText(documentLocation);

    QString musicLocation = settings.value("musicDirectory").toString();
    ui->MusicDirectoryEdit->setText(musicLocation);

    QString programLocation = settings.value("programDirectory").toString();
    ui->ProgramsDirectoryEdit->setText(programLocation);

    QString videoLocation = settings.value("videoDirectory").toString();
    ui->VideoDirectoryEdit->setText(videoLocation);
    //saveto end
    //categories start
    QString CompressedExtension = settings.value("CompressedFileExtensions").toString();
    ui->CompressedExtensionsEdit->setText(CompressedExtension);

    QString DocumentsExtension = settings.value("DocumentsFileExtensions").toString();
    ui->DocumentsExtensionsEdit->setText(DocumentsExtension);

    QString MusicExtension = settings.value("MusicFileExtensions").toString();
    ui->MusicExtensionsEdit->setText(MusicExtension);

    QString ProgramsExtension = settings.value("ProgramsExtensions").toString();
    ui->ProgramsExtensionsEdit->setText(ProgramsExtension);

    QString VideoExtension = settings.value("VideoFileExtensions").toString();
    ui->VideoExtensionsEdit->setText(VideoExtension);

    //categories end

    //network start
    settings.beginGroup(QLatin1String("proxy"));
    ui->proxySupport->setChecked(false);
    if (settings.value(QLatin1String("enabled"), false).toBool()) {
        ui->proxySupport->setChecked(true);
        if (settings.value(QLatin1String("type"), 0).toInt() == 0)
            ui->proxyType->setCurrentIndex(0);
        else
            ui->proxyType->setCurrentIndex(0);
        ui->proxyHostName->setText(settings.value(QLatin1String("hostName")).toString());
        ui->proxyPort->setValue(settings.value(QLatin1String("port"), 1080).toInt());
        ui->proxyUserName->setText(settings.value(QLatin1String("userName")).toString());
        ui->proxyPassword->setText(settings.value(QLatin1String("password")).toString());
    }
    //setProxy(proxy);
    //network end
}

void OptionsDialog::writeSettings()
{
    QSettings settings(this);
    //general start
    settings.setValue("maxRunningDownloads",ui->maxTasksSpinBox->value());
    settings.setValue("ConnectionsPerDownload",ui->ConnectionsPerDownloadSpinBox->value());
    settings.setValue("showDownloadsCompleteDialog",ui->showDownloadsCompleteDialogCheckbox->isChecked());
    settings.setValue("EnableSounds",ui->EnableSoundsCheckBox->isChecked());
    //general end

    //saveto start
    settings.setValue("generalDirectory",ui->generalDirectoryEdit->text());
    settings.setValue("compressedDirectory",ui->CompressedDirectoryEdit->text());
    settings.setValue("documentDirectory",ui->DocumentsDirectoryEdit->text());
    settings.setValue("musicDirectory",ui->MusicDirectoryEdit->text());
    settings.setValue("programDirectory",ui->ProgramsDirectoryEdit->text());
    settings.setValue("videoDirectory",ui->VideoDirectoryEdit->text());
    //saveto end

    //categories start
    settings.setValue("CompressedFileExtensions",ui->CompressedExtensionsEdit->text());
    settings.setValue("DocumentsFileExtensions",ui->DocumentsExtensionsEdit->text());
    settings.setValue("MusicFileExtensions",ui->MusicExtensionsEdit->text());
    settings.setValue("ProgramsExtensions",ui->ProgramsExtensionsEdit->text());
    settings.setValue("VideoFileExtensions",ui->VideoExtensionsEdit->text());
    //categories end

    //network start
    settings.beginGroup(QLatin1String("proxy"));
    settings.setValue(QLatin1String("enabled"), ui->proxySupport->isChecked());
    settings.setValue(QLatin1String("type"), ui->proxyType->currentIndex());
    settings.setValue(QLatin1String("hostName"), ui->proxyHostName->text());
    settings.setValue(QLatin1String("port"), ui->proxyPort->text());
    settings.setValue(QLatin1String("userName"), ui->proxyUserName->text());
    settings.setValue(QLatin1String("password"), ui->proxyPassword->text());
    settings.endGroup();
    //network end
}

void OptionsDialog::on_buttonBox_accepted()
{
    writeSettings();
}

void OptionsDialog::on_pushButton_6_clicked()
{
    //compressed
    //video
    QFileDialog filedialog(this);
    filedialog.setFileMode(filedialog.Directory);
    QStringList seldir;
    if(filedialog.exec())
        seldir = filedialog.selectedFiles();
    ui->CompressedDirectoryEdit->setText(seldir.first());
}
