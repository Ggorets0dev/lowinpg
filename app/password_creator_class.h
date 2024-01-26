#ifndef PasswordCreator_H
#define PasswordCreator_H

#include <QTextEdit>
#include <QString>
#include <QRegularExpression>
#include <random_generator_class.h>

typedef std::tuple<bool, bool, bool> CheckedOptions;

/**
 * @brief Класс-обработчик для стороннего потока. Отвечает за создание паролей с определенными характеристиками
 */
class PasswordCreator : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Инициализация требующихся для создания случайных значений переменных
     */
    explicit PasswordCreator(QObject* parent = nullptr) : QObject(parent) { random_generator_ = new RandomGenerator(); };

    ~PasswordCreator();

    /**
     * @brief Установить параметры для обработичка потока (создание паролей)
     * @param Длина пароля
     * @param Количество паролей
     * @param Список опций, которые должен содержать пароль (буквы, цифры, специальные символы)
     */
    void setParams(ushort pswds_len, ushort pswds_cnt, CheckedOptions options);

signals:
    /**
     * @brief Сигнал для отправки созданных паролей
     */
    void created(QString);

    /**
     * @brief Сигнал, сообщающий о завершении запрошенной операции
     */
    void finished();

public slots:
    /**
     * @brief Слот для создания паролей по установленным через setParams характеристикам
     */
    void createPasswords();

private:
    ushort passwords_length_;
    ushort passwords_count_;
    CheckedOptions options_;

    RandomGenerator* random_generator_;
};

#endif // PasswordCreator_H
