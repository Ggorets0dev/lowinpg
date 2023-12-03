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

QString RandomGenerator::getRandomString(Symbols& source_chars, const ushort size)
{
    const ushort source_chars_max_inx = source_chars.size() - 1;
    QString result;

    for (ushort i(0); i < size; i++)
    {
        ushort random_num = getRandomFromInterval(0, source_chars_max_inx);
        result += source_chars[random_num];
    }

    return result;
}

Symbols RandomGenerator::getSymbols(ushort min_char_inx, ushort max_char_inx)
{
    Symbols characters;

    for (ushort i(min_char_inx); i <= max_char_inx; i++)
        characters.push_back(static_cast<char>(i));

    return characters;
}
