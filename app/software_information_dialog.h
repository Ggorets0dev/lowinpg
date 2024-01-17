#ifndef SOFTWARE_INFORMATION_DIALOG_H
#define SOFTWARE_INFORMATION_DIALOG_H

#define VERSION "1.3.0"
#define DEVELOPER "Ggorets0dev"
#define REPOSITORY "https://github.com/Ggorets0dev/lowinpg"

#include <QDialog>

namespace Ui {
class SoftwareInformationDialog;
}

class SoftwareInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SoftwareInformationDialog(QWidget *parent = nullptr);
    ~SoftwareInformationDialog();

private:
    Ui::SoftwareInformationDialog *ui;
};

#endif // SOFTWARE_INFORMATION_DIALOG_H
