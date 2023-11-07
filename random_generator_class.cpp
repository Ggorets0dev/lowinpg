#include "random_generator_class.h"


RandomGenerator::RandomGenerator()
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    this->generator_ = new std::mt19937(seed);
}

RandomGenerator::~RandomGenerator()
{
    delete this->generator_;
}

ushort RandomGenerator::getRandomFromInterval(ushort minimal, ushort maximal)
{
    ushort random_num;
    random_num = this->generator_->operator()();

    return minimal + random_num % (maximal + 1 - minimal);
}

QString RandomGenerator::getRandomString(ushort min_char_inx, ushort max_char_inx, const ushort size)
{
    QString result;

    for (ushort i(0); i < size; i++)
    {
        ushort random_num = getRandomFromInterval(min_char_inx, max_char_inx);
        char symbol = static_cast<char>(random_num);
        result += symbol;
    }

    return result;
}

QString RandomGenerator::getMixedString(QVector<QString>& variants)
{
    const ushort vec_size = variants.size();
    const ushort str_size = variants.at(0).length();

    ushort var_inx;
    QString result;

    for (ushort i(0); i < str_size; i++)
    {
        var_inx = getRandomFromInterval(0, vec_size - 1);
        result += variants.at(var_inx).at(i);
    }

    return result;
}
