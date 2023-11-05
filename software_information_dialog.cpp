#include "software_information_dialog.h"
#include "ui_software_information_dialog.h"


SoftwareInformationDialog::SoftwareInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoftwareInformationDialog)
{
    ui->setupUi(this);

    ui->version_label->setText(VERSION);
    ui->developer_label->setText(DEVELOPER);
    ui->repository_label->setText(REPOSITORY);
}

SoftwareInformationDialog::~SoftwareInformationDialog()
{
    delete ui;
}
