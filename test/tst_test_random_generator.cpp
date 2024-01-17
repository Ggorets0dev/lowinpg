#include <QtTest>
#include <QDebug>

#include "../app/random_generator_class.h"

class Test_RandomGenerator : public QObject
{
    Q_OBJECT

public:
    Test_RandomGenerator();
    ~Test_RandomGenerator();

private slots:
    void Test_GetRandomFromInterval();
    void Test_GetSymbols();
    void Test_GetRandomString();
};

Test_RandomGenerator::Test_RandomGenerator() {}

Test_RandomGenerator::~Test_RandomGenerator() {}

void Test_RandomGenerator::Test_GetRandomFromInterval()
{
    RandomGenerator rg;

    ushort left(0);
    ushort right(10);

    ushort num = rg.getRandomFromInterval(left, right);

    bool is_num_fit = left <= num && num <= right;

    // DEBUG MSG SECTION
    qDebug() << "left: " + QString::number(left);
    qDebug() << "right: " + QString::number(right);
    qDebug() << "random: " + QString::number(num);
    // DEBUG MSG SECTION

    QVERIFY(is_num_fit);
}

void Test_RandomGenerator::Test_GetSymbols()
{
    RandomGenerator rg;

    ushort left(48);
    ushort right(53);

    Symbols test_symbols = Symbols {'0', '1', '2', '3', '4', '5'};
    Symbols collected_symbols = rg.getSymbols(left, right);

    bool is_symbols_fit = test_symbols == collected_symbols;

    // DEBUG MSG SECTION
    qDebug() << "left (code): " + QString::number(left);
    qDebug() << "right (code): " + QString::number(right);
    qDebug() << "test (string): " + QString::fromLatin1(test_symbols.data(), test_symbols.size());
    qDebug() << "random (string): " + QString::fromLatin1(collected_symbols.data(), collected_symbols.size());
    // DEBUG MSG SECTION

    QVERIFY(is_symbols_fit);
}

void Test_RandomGenerator::Test_GetRandomString()
{
    RandomGenerator rg;

    ushort size(10);
    Symbols test_symbols = Symbols {'0', '1', '2', '3', '4', '5'};

    QString random_string = rg.getRandomString(test_symbols, size);

    bool is_string_size_fit = random_string.length() == size;

    // DEBUG MSG SECTION
    qDebug() << "fixed size: " + QString::number(size);
    qDebug() << "random size: " + QString::number(random_string.length());
    // DEBUG MSG SECTION

    QVERIFY(is_string_size_fit);
}

QTEST_APPLESS_MAIN(Test_RandomGenerator)

#include "tst_test_random_generator.moc"
