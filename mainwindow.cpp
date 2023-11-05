#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random_utils.h"

#include <QIODevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startPushButton, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
    connect(ui->exportPushButton, SIGNAL(clicked()), this, SLOT(handleExportButtonClicked()));
    connect(ui->clearPushButton, SIGNAL(clicked()), this, SLOT(handleClearButtonClicked()));

    connect(ui->literalsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));
    connect(ui->numsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));
    connect(ui->specsymbolsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));

    connect(ui->passwordsTextEdit, SIGNAL(textChanged()), this, SLOT(handleTextChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::tuple<bool, bool, bool> MainWindow::getCheckedOptions()
{
    const bool use_literals = ui->literalsCheckBox->isChecked();
    const bool use_nums = ui->numsCheckBox->isChecked();
    const bool use_specsymbols= ui->specsymbolsCheckBox->isChecked();

    return std::make_tuple(use_literals, use_nums, use_specsymbols);
}

void MainWindow::handleStartButtonClicked()
{
    const unsigned short password_len = ui->lenSpinBox->value();
    const unsigned short passwords_cnt = ui->cntSpinBox->value();

    auto checked_options = getCheckedOptions();

    bool use_literals, use_nums, use_specsymbols;
    std::tie(use_literals, use_nums, use_specsymbols) = checked_options;

    QVector<QString> generated_variants;
    generated_variants.reserve(static_cast<int>(use_literals) * 2 + static_cast<int>(use_nums) + static_cast<int>(use_specsymbols) * 4);

    QString passwords;

    for (short i(0); i < passwords_cnt; i++)
    {
        if (use_literals)
        {
            generated_variants.push_back(getRandomString(65, 90, password_len));
            generated_variants.push_back(getRandomString(97, 122, password_len));
        }

        if (use_nums)
        {
            generated_variants.push_back(getRandomString(48, 57, password_len));
        }

        if (use_specsymbols)
        {
            generated_variants.push_back(getRandomString(33, 47, password_len));
            generated_variants.push_back(getRandomString(58, 63, password_len));
            generated_variants.push_back(getRandomString(91, 96, password_len));
            generated_variants.push_back(getRandomString(123, 126, password_len));
        }

        passwords += getMixedString(generated_variants);
        passwords += '\n';

        generated_variants.clear();
    }

    ui->passwordsTextEdit->setText(passwords);
}

void MainWindow::handleExportButtonClicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    const QString file_path = dialog.getSaveFileName(nullptr, "Выберите место сохранения файла", "pswds.txt", "Текстовые файлы (*.txt)");

    QFile file_out(file_path);
    file_out.open(QIODevice::WriteOnly);

    if (file_out.isOpen())
    {
        QTextStream stream(&file_out);
        stream << ui->passwordsTextEdit->toPlainText();
        file_out.close();

        QMessageBox::information(this, "Пароли записаны", "Пароли сохранены по выбранному пути");
    }
    else
    {
        QMessageBox::critical(this, "Ошибка открытия файла", "Не удалось открыть файл для сохранения паролей");
    }
}

void MainWindow::handleClearButtonClicked()
{
    ui->passwordsTextEdit->clear();
}

void MainWindow::handleOptionChecked()
{
    auto checked_options = getCheckedOptions();

    bool use_literals, use_nums, use_specsymbols;
    std::tie(use_literals, use_nums, use_specsymbols) = checked_options;

    ui->startPushButton->setEnabled(use_literals || use_nums || use_specsymbols);
}

void MainWindow::handleTextChanged()
{
    const auto passwords = ui->passwordsTextEdit->toPlainText();
    const bool is_full = passwords.length() > 0;

    ui->clearPushButton->setEnabled(is_full);
    ui->exportPushButton->setEnabled(is_full);
}
