#pragma once

#include <QString>
#include <random>
#include <chrono>
#include <QVector>

#define CHAR_MIN_INX 33
#define CHAR_MAX_INX 126

typedef QVector<char> Symbols;

/**
 * @brief Класс для генерации случайных величин с различными характеристиками
 */
class RandomGenerator
{
private:
    std::mt19937 *generator_;

public:
    RandomGenerator();
    ~RandomGenerator();

    /**
     * @brief Получить случайное число из интервала
     * @param Левая граница интервала
     * @param Правая граница интервала
     * @return Случайное число в заданном интервале
     */
    ushort getRandomFromInterval(ushort minimal, ushort maximal);

    /**
     * @brief Получить последовательность из случайно подобранных символов, коды которых находятся в заданном промежутке
     * @param Левая граница символов (код)
     * @param Правая граница символов (код)
     * @return Последовательность случайных символов
     */
    Symbols getSymbols(ushort min_char_inx, ushort max_char_inx);

    /**
     * @brief Получить случайную строку из заданной последовательности символов
     * @param Последовательность символов
     * @param Размер выходной строки
     * @return Случайная строка
     */
    QString getRandomString(Symbols& source_chars, const ushort size);
};
