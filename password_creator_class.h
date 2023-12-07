#ifndef PasswordCreator_H
#define PasswordCreator_H

#include <QTextEdit>
#include <QString>
#include <QRegularExpression>
#include <random_generator_class.h>

typedef std::tuple<bool, bool, bool> CheckedOptions;

class PasswordCreator : public QObject
{
    Q_OBJECT

public:
    explicit PasswordCreator(QObject* parent = nullptr) : QObject(parent) { random_generator_ = new RandomGenerator(); };
    ~PasswordCreator();

    void setParams(ushort pswds_len, ushort pswds_cnt, CheckedOptions options);
    ushort getPasswordsCount();

signals:
    void created(QString);
    void finished(void);

public slots:
    void createPasswords();

private:
    ushort passwords_length_;
    ushort passwords_count_;
    CheckedOptions options_;

    RandomGenerator* random_generator_;
};

#endif // PasswordCreator_H
