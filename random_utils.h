#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#endif // RANDOM_UTILS_H

#define CHAR_MIN_INX 33
#define CHAR_MAX_INX 126

#include <QString>
#include <random>
#include <ctime>
#include <chrono>
#include <QVector>
#include <QDebug>

unsigned long int getRandomFromInterval(unsigned short minimal, unsigned short maximal);

QString getRandomString(unsigned short min_char_inx, unsigned short max_char_inx, const unsigned short size);

QString getMixedString(QVector<QString>& variants);
