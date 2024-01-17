#include "password_creator_class.h"

PasswordCreator::~PasswordCreator()
{
    delete random_generator_;
}

ushort PasswordCreator::getPasswordsCount()
{
    return this->passwords_count_;
}

void PasswordCreator::setParams(ushort pswds_len, ushort pswds_cnt, CheckedOptions options)
{
    this->passwords_length_ = pswds_len;
    this->passwords_count_ = pswds_cnt;
    this->options_ = options;
}

void PasswordCreator::createPasswords()
{
    bool use_literals, use_nums, use_specsymbols;
    std::tie(use_literals, use_nums, use_specsymbols) = this->options_;

    Symbols all_source_symbols;

    QString passwords;

    if (use_literals)
    {
        all_source_symbols += this->random_generator_->getSymbols(65, 90);
        all_source_symbols += this->random_generator_->getSymbols(97, 122);
    }

    if (use_nums)
    {
        all_source_symbols += this->random_generator_->getSymbols(48, 57);
    }

    if (use_specsymbols)
    {
        all_source_symbols += this->random_generator_->getSymbols(33, 47);
        all_source_symbols += this->random_generator_->getSymbols(58, 63);
        all_source_symbols += this->random_generator_->getSymbols(91, 96);
        all_source_symbols += this->random_generator_->getSymbols(123, 126);
    }

    ushort i(0);
    while (i < this->passwords_count_)
    {
        auto password = this->random_generator_->getRandomString(all_source_symbols, this->passwords_length_);

        const bool have_literals = password.contains(QRegularExpression("[A-Za-z]"));
        const bool have_nums = password.contains(QRegularExpression("[0-9]"));
        const bool have_specsymbols = password.contains(QRegularExpression("[^A-Za-z0-9]"));

        if ((use_literals && !have_literals) || (use_nums && !have_nums) || (use_specsymbols && !have_specsymbols))
            continue;

        passwords += password;
        passwords += '\n';
        i++;
    }

    passwords.chop(1);

    emit created(passwords);
    emit finished();
}
