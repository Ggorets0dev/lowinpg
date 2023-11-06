#pragma once

#define CHAR_MIN_INX 33
#define CHAR_MAX_INX 126

#include <QString>
#include <random>
#include <ctime>
#include <chrono>
#include <QVector>
#include <QDebug>

class RandomGenerator
{
private:
    std::mt19937 *generator_;

public:
    RandomGenerator();
    ~RandomGenerator();

    ushort getRandomFromInterval(ushort minimal, ushort maximal);

    QString getRandomString(ushort min_char_inx, ushort max_char_inx, const ushort size);

    QString getMixedString(QVector<QString>& variants);
};
