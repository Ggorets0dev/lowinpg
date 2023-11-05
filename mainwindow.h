#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include "software_information_dialog.h"

#define STATUSBAR_MESSAGE_TIMEOUT 2000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleStartButtonClicked();
    void handleExportButtonClicked();
    void handleClearButtonClicked();
    void handleTextChanged();
    void handleOptionChecked();
    void handleSoftwareInfoActionClicked();

private:
    Ui::MainWindow *ui;
    QAction *software_info_action;
    std::tuple<bool, bool, bool> getCheckedOptions();
};

#endif // MAINWINDOW_H
