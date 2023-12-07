#pragma once

#include <QString>
#include <random>
#include <chrono>
#include <QVector>

#define CHAR_MIN_INX 33
#define CHAR_MAX_INX 126

typedef QVector<char> Symbols;

class RandomGenerator
{
private:
    std::mt19937 *generator_;

public:
    RandomGenerator();
    ~RandomGenerator();

    ushort getRandomFromInterval(ushort minimal, ushort maximal);

    Symbols getSymbols(ushort min_char_inx, ushort max_char_inx);

    QString getRandomString(Symbols& source_chars, const ushort size);
};
