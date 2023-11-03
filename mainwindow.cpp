#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random_utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->start_push_button, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
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
            generated_variants.push_back(getRandomString(48, 59, password_len));
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
