#include <random>
#include <ctime>
#include <chrono>

#include "random_utils.h"

unsigned long int getRandomFromInterval(unsigned short minimal, unsigned short maximal)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);

    unsigned long int random_num;
    random_num = mt();

    return minimal + random_num % (maximal - minimal);
}

QString getRandomString(unsigned short min_char_inx, unsigned short max_char_inx, unsigned short size)
{
    QString result;
    char symbol;
    unsigned long int random_num;

    for (int i(0); i < size; i++)
    {
        random_num = getRandomFromInterval(min_char_inx, max_char_inx);
        symbol = static_cast<char>(random_num);
        result += symbol;
    }

    return result;
}
