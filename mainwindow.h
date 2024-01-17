#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <QClipboard>
#include "software_information_dialog.h"
#include "password_creator_class.h"

#define STATUSBAR_MESSAGE_TIMEOUT 2000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Главная форма приложения
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Создание и настройка главной формы приложения
     */
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

signals:
    /**
     * @brief Сигнал для запуска стороннего потока по созданию паролей
     */
    void start_creation(void);

private slots:
    void handleStartButtonClicked();
    void handleExportButtonClicked();
    void handleClearButtonClicked();
    void handleCopyButtonClicked();
    void handleTextChanged();
    void handleOptionChecked();
    void handleSoftwareInfoActionClicked();
    void handlePasswordsCreated(QString passwords);
    void handleWorkerFinished();

private:
    Ui::MainWindow *ui_;
    QAction *software_info_action_;
    PasswordCreator* password_creator_;
    QThread* worker_thread_;

    std::tuple<bool, bool, bool> getCheckedOptions();
};

#endif // MAINWINDOW_H
