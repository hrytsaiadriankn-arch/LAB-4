#include "pch.h"
#include "Complex.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

// Constructor
Complex::Complex(double real, double imaginary)
{
    a = real;
    b = imaginary;
}

// Addition
unique_ptr<Pair> Complex::add(const Pair& other) const
{
    const Complex& c = dynamic_cast<const Complex&>(other);

    return make_unique<Complex>(
        a + c.a,
        b + c.b
    );
}

// Subtraction
unique_ptr<Pair> Complex::sub(const Pair& other) const
{
    const Complex& c = dynamic_cast<const Complex&>(other);

    return make_unique<Complex>(
        a - c.a,
        b - c.b
    );
}

// Multiplication
unique_ptr<Pair> Complex::mul(const Pair& other) const
{
    const Complex& c = dynamic_cast<const Complex&>(other);

    return make_unique<Complex>(
        a * c.a - b * c.b,
        a * c.b + b * c.a
    );
}

// Division
unique_ptr<Pair> Complex::div(const Pair& other) const
{
    const Complex& c = dynamic_cast<const Complex&>(other);

    double denominator = c.a * c.a + c.b * c.b;

    if (denominator == 0)
        throw runtime_error("Division by zero!");

    return make_unique<Complex>(
        (a * c.a + b * c.b) / denominator,
        (b * c.a - a * c.b) / denominator
    );
}

// Comparison
bool Complex::equ(const Complex& other) const
{
    return fabs(a - other.a) < 1e-9 &&
        fabs(b - other.b) < 1e-9;
}

// Complex conjugate
Complex Complex::conj() const
{
    return Complex(a, -b);
}

// Display
void Complex::display() const
{
    cout << fixed << setprecision(2);

    cout << a;

    if (b >= 0)
        cout << " + " << b << "i";
    else
        cout << " - " << fabs(b) << "i";
}
