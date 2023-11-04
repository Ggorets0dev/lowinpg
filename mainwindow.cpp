#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random_utils.h"

#include <QIODevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->start_push_button, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
    connect(ui->export_txt_push_button, SIGNAL(clicked()), this, SLOT(handleExportButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleStartButtonClicked()
{
    const unsigned short password_len = ui->password_len_spin_box->value();
    const unsigned short passwords_cnt = ui->passwords_cnt_spin_box->value();

    const bool use_literals = ui->literals_check_box->isChecked();
    const bool use_nums = ui->nums_check_box->isChecked();
    const bool use_specsymbols= ui->specsymbs_check_box->isChecked();

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

    ui->generation_results_text_edit->setText(passwords);
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
        stream << ui->generation_results_text_edit->toPlainText();
        file_out.close();

        QMessageBox::information(this, "ОПароли записаны", "Пароли сохранены по выбранному пути");
    }
    else
    {
        QMessageBox::critical(this, "Ошибка открытия файла", "Не удалось открыть файл для сохранения паролей");
    }
}
