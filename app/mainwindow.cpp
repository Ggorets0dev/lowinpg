﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random_generator_class.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    software_info_action_ = new QAction("О программе", this);
    QMenu *menu = menuBar()->addMenu("Сведения");
    menu->addAction(software_info_action_);

    connect(ui_->startPushButton, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
    connect(ui_->exportPushButton, SIGNAL(clicked()), this, SLOT(handleExportButtonClicked()));
    connect(ui_->clearPushButton, SIGNAL(clicked()), this, SLOT(handleClearButtonClicked()));
    connect(ui_->copyPushButton, SIGNAL(clicked()), this, SLOT(handleCopyButtonClicked()));

    connect(ui_->literalsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));
    connect(ui_->numsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));
    connect(ui_->specsymbolsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));

    connect(ui_->passwordsTextEdit, SIGNAL(textChanged()), this, SLOT(handleTextChanged()));

    connect(software_info_action_, SIGNAL(triggered()), this, SLOT(handleSoftwareInfoActionClicked()));
}

CheckedOptions MainWindow::getCheckedOptions()
{
    const bool use_literals = ui_->literalsCheckBox->isChecked();
    const bool use_nums = ui_->numsCheckBox->isChecked();
    const bool use_specsymbols= ui_->specsymbolsCheckBox->isChecked();

    return std::make_tuple(use_literals, use_nums, use_specsymbols);
}

void MainWindow::handleStartButtonClicked()
{
    const ushort passwords_length = ui_->lenSpinBox->value();
    const ushort passwords_count = ui_->cntSpinBox->value();
    auto checked_options = getCheckedOptions();

    auto password_creator = new PasswordCreator();
    auto worker_thread = new QThread();

    password_creator->setParams(passwords_length, passwords_count, checked_options);
    password_creator->moveToThread(worker_thread);

    connect(worker_thread, SIGNAL(started()), password_creator, SLOT(createPasswords()));
    connect(password_creator, SIGNAL(created(QString)), this, SLOT(handlePasswordsCreated(QString)));

    connect(password_creator, SIGNAL(finished()), this, SLOT(handleWorkerFinished()));
    connect(password_creator, SIGNAL(finished()), worker_thread, SLOT(quit()));

    connect(password_creator, SIGNAL(finished()), password_creator, SLOT(deleteLater()));
    connect(worker_thread, SIGNAL(finished()), worker_thread, SLOT(deleteLater()));

    connect(worker_thread, SIGNAL(started()), this, SLOT(lockRunningState()));
    connect(worker_thread, SIGNAL(finished()), this, SLOT(unlockRunningState()));

    worker_thread->start();

    this->ui_->startPushButton->setEnabled(false);
}

void MainWindow::handleCopyButtonClicked()
{
    QClipboard *clipboard = QApplication::clipboard();

    QString passwords = ui_->passwordsTextEdit->toPlainText();

    clipboard->setText(passwords);

    ui_->statusbar->showMessage("Созданные пароли скопированы в буфер обмена", STATUSBAR_MESSAGE_TIMEOUT);
}

void MainWindow::handleExportButtonClicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    const QString file_path = dialog.getSaveFileName(nullptr, "Выберите место сохранения файла", "pswds.txt", "Текстовые файлы (*.txt)");

    if (file_path.length() == 0)
        return;

    QFile file_out(file_path);
    file_out.open(QIODevice::WriteOnly);

    if (file_out.isOpen())
    {
        QTextStream stream(&file_out);
        stream << ui_->passwordsTextEdit->toPlainText();
        file_out.close();

        QMessageBox::information(this, "Пароли записаны", "Пароли сохранены по выбранному пути");
        ui_->statusbar->showMessage("Пароли сохранены", STATUSBAR_MESSAGE_TIMEOUT);
    }
    else
    {
        QMessageBox::critical(this, "Ошибка открытия файла", "Не удалось открыть файл для сохранения паролей");
        ui_->statusbar->showMessage("Не удалось сохранить пароли", STATUSBAR_MESSAGE_TIMEOUT);
    }
}

void MainWindow::handleClearButtonClicked()
{
    ui_->passwordsTextEdit->clear();
    ui_->statusbar->showMessage("Созданные пароли удалены", STATUSBAR_MESSAGE_TIMEOUT);
}

void MainWindow::handleOptionChecked()
{
    auto checked_options = getCheckedOptions();

    bool use_literals, use_nums, use_specsymbols;
    std::tie(use_literals, use_nums, use_specsymbols) = checked_options;

    ui_->startPushButton->setEnabled((use_literals || use_nums || use_specsymbols) && !is_running_);
}

void MainWindow::handleTextChanged()
{
    const auto passwords = ui_->passwordsTextEdit->toPlainText();
    const bool is_full = passwords.length() > 0;

    ui_->clearPushButton->setEnabled(is_full);
    ui_->exportPushButton->setEnabled(is_full);
    ui_->copyPushButton->setEnabled(is_full);
}

void MainWindow::handleSoftwareInfoActionClicked()
{
    ui_->statusbar->showMessage("Сведения о программе отображены", STATUSBAR_MESSAGE_TIMEOUT);

    auto *dialog = new SoftwareInformationDialog(this);
    dialog->exec();

    delete dialog;
}

void MainWindow::handlePasswordsCreated(QString passwords)
{
    ui_->passwordsTextEdit->setText(passwords);
}

void MainWindow::handleWorkerFinished()
{
    this->ui_->startPushButton->setEnabled(true);
    ui_->statusbar->showMessage(QString("Пароли созданы"), STATUSBAR_MESSAGE_TIMEOUT);
}

void MainWindow::lockRunningState() { is_running_ = true; }

void MainWindow::unlockRunningState() { is_running_ = false; }
