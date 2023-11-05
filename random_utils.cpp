#include "random_utils.h"


unsigned long int getRandomFromInterval(unsigned short minimal, unsigned short maximal)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);

    unsigned long int random_num;
    random_num = mt();

    return minimal + random_num % (maximal + 1 - minimal);
}

QString getRandomString(unsigned short min_char_inx, unsigned short max_char_inx, const unsigned short size)
{
    QString result;
    char symbol;
    unsigned long int random_num;

    for (short i(0); i < size; i++)
    {
        random_num = getRandomFromInterval(min_char_inx, max_char_inx);
        symbol = static_cast<char>(random_num);
        result += symbol;
    }

    return result;
}

QString getMixedString(QVector<QString>& variants)
{
    const unsigned short vec_size = variants.size();
    const unsigned short str_size = variants.at(0).length();
    unsigned short var_inx;

    QString result;

    for (short i(0); i < str_size; i++)
    {
        var_inx = getRandomFromInterval(0, vec_size - 1);
        result += variants.at(var_inx).at(i);
    }

    return result;
}
