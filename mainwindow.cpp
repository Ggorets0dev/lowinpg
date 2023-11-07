#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random_generator_class.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    this->random_ = new RandomGenerator();

    this->ui_->setupUi(this);

    this->software_info_action_ = new QAction("О программе", this);
    QMenu *menu = menuBar()->addMenu("Сведения");
    menu->addAction(this->software_info_action_);

    connect(ui_->startPushButton, SIGNAL(clicked()), this, SLOT(handleStartButtonClicked()));
    connect(ui_->exportPushButton, SIGNAL(clicked()), this, SLOT(handleExportButtonClicked()));
    connect(ui_->clearPushButton, SIGNAL(clicked()), this, SLOT(handleClearButtonClicked()));

    connect(ui_->literalsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));
    connect(ui_->numsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));
    connect(ui_->specsymbolsCheckBox, SIGNAL(clicked()), this, SLOT(handleOptionChecked()));

    connect(ui_->passwordsTextEdit, SIGNAL(textChanged()), this, SLOT(handleTextChanged()));

    connect(this->software_info_action_, SIGNAL(triggered()), this, SLOT(handleSoftwareInfoActionClicked()));
}

MainWindow::~MainWindow()
{
    delete random_;
    delete ui_;
}

std::tuple<bool, bool, bool> MainWindow::getCheckedOptions()
{
    const bool use_literals = ui_->literalsCheckBox->isChecked();
    const bool use_nums = ui_->numsCheckBox->isChecked();
    const bool use_specsymbols= ui_->specsymbolsCheckBox->isChecked();

    return std::make_tuple(use_literals, use_nums, use_specsymbols);
}

void MainWindow::handleStartButtonClicked()
{
    const ushort password_len = ui_->lenSpinBox->value();
    const ushort passwords_cnt = ui_->cntSpinBox->value();

    auto checked_options = getCheckedOptions();

    bool use_literals, use_nums, use_specsymbols;
    std::tie(use_literals, use_nums, use_specsymbols) = checked_options;

    QVector<QString> generated_variants;
    generated_variants.reserve(static_cast<int>(use_literals) * 2 + static_cast<int>(use_nums) + static_cast<int>(use_specsymbols) * 4);

    QString passwords;

    for (ushort i(0); i < passwords_cnt; i++)
    {
        if (use_literals)
        {
            generated_variants.push_back(this->random_->getRandomString(65, 90, password_len));
            generated_variants.push_back(this->random_->getRandomString(97, 122, password_len));
        }

        if (use_nums)
        {
            generated_variants.push_back(this->random_->getRandomString(48, 57, password_len));
        }

        if (use_specsymbols)
        {
            generated_variants.push_back(this->random_->getRandomString(33, 47, password_len));
            generated_variants.push_back(this->random_->getRandomString(58, 63, password_len));
            generated_variants.push_back(this->random_->getRandomString(91, 96, password_len));
            generated_variants.push_back(this->random_->getRandomString(123, 126, password_len));
        }

        passwords += this->random_->getMixedString(generated_variants);
        passwords += '\n';

        generated_variants.clear();
    }

    ui_->passwordsTextEdit->setText(passwords);
    ui_->statusbar->showMessage(QString("Пароли (%1 шт.) созданы").arg(passwords_cnt), STATUSBAR_MESSAGE_TIMEOUT);
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

    ui_->startPushButton->setEnabled(use_literals || use_nums || use_specsymbols);
}

void MainWindow::handleTextChanged()
{
    const auto passwords = ui_->passwordsTextEdit->toPlainText();
    const bool is_full = passwords.length() > 0;

    ui_->clearPushButton->setEnabled(is_full);
    ui_->exportPushButton->setEnabled(is_full);
}

void MainWindow::handleSoftwareInfoActionClicked()
{
    ui_->statusbar->showMessage("Сведения о программе отображены", STATUSBAR_MESSAGE_TIMEOUT);

    auto *dialog = new SoftwareInformationDialog(this);
    dialog->exec();
    delete dialog;
}
