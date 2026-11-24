
#pragma once
#include "Pair.h"

class Complex : public Pair
{
private:
    double a;
    double b;

public:
    Complex(double real = 0, double imaginary = 0);

    std::unique_ptr<Pair> add(const Pair& other) const override;
    std::unique_ptr<Pair> sub(const Pair& other) const override;
    std::unique_ptr<Pair> mul(const Pair& other) const override;
    std::unique_ptr<Pair> div(const Pair& other) const override;

    bool equ(const Complex& other) const;

    Complex conj() const;

    void display() const override;
};
