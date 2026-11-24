
#pragma once
#include "Pair.h"

class Money : public Pair
{
private:
    long hryvnias;
    unsigned char kopiykas;

    long long toKopiykas() const;
    void fromKopiykas(long long value);

public:
    Money(long h = 0, unsigned char k = 0);

    std::unique_ptr<Pair> add(const Pair& other) const override;
    std::unique_ptr<Pair> sub(const Pair& other) const override;
    std::unique_ptr<Pair> mul(const Pair& other) const override;
    std::unique_ptr<Pair> div(const Pair& other) const override;

    Money divideBy(double number) const;
    Money multiplyBy(double number) const;

    bool equ(const Money& other) const;
    bool greater(const Money& other) const;
    bool less(const Money& other) const;

    void display() const override;
};
