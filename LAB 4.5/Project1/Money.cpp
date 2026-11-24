
#include "Money.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

// Convert money to kopiykas
long long Money::toKopiykas() const
{
    return static_cast<long long>(hryvnias) * 100 + kopiykas;
}

// Convert kopiykas to money
void Money::fromKopiykas(long long value)
{
    hryvnias = static_cast<long>(value / 100);

    long long remainder = value % 100;

    if (remainder < 0)
    {
        hryvnias--;
        remainder += 100;
    }

    kopiykas = static_cast<unsigned char>(remainder);
}

// Constructor
Money::Money(long h, unsigned char k)
{
    fromKopiykas(static_cast<long long>(h) * 100 + k);
}

// Addition
unique_ptr<Pair> Money::add(const Pair& other) const
{
    const Money& m = dynamic_cast<const Money&>(other);

    long long result = toKopiykas() + m.toKopiykas();

    Money* temp = new Money();
    temp->fromKopiykas(result);

    return unique_ptr<Pair>(temp);
}

// Subtraction
unique_ptr<Pair> Money::sub(const Pair& other) const
{
    const Money& m = dynamic_cast<const Money&>(other);

    long long result = toKopiykas() - m.toKopiykas();

    Money* temp = new Money();
    temp->fromKopiykas(result);

    return unique_ptr<Pair>(temp);
}

// Multiplication
unique_ptr<Pair> Money::mul(const Pair& other) const
{
    const Money& m = dynamic_cast<const Money&>(other);

    long long result = llround(
        static_cast<double>(toKopiykas()) *
        m.toKopiykas() / 100.0
    );

    Money* temp = new Money();
    temp->fromKopiykas(result);

    return unique_ptr<Pair>(temp);
}

// Division
unique_ptr<Pair> Money::div(const Pair& other) const
{
    const Money& m = dynamic_cast<const Money&>(other);

    if (m.toKopiykas() == 0)
        throw runtime_error("Division by zero!");

    double result =
        static_cast<double>(toKopiykas()) /
        m.toKopiykas();

    long long kopiykasResult = llround(result * 100);

    Money* temp = new Money();
    temp->fromKopiykas(kopiykasResult);

    return unique_ptr<Pair>(temp);
}

// Division by fractional number
Money Money::divideBy(double number) const
{
    if (number == 0)
        throw runtime_error("Division by zero!");

    long long result = llround(toKopiykas() / number);

    Money temp;
    temp.fromKopiykas(result);

    return temp;
}

// Multiplication by fractional number
Money Money::multiplyBy(double number) const
{
    long long result = llround(toKopiykas() * number);

    Money temp;
    temp.fromKopiykas(result);

    return temp;
}

// Comparison
bool Money::equ(const Money& other) const
{
    return toKopiykas() == other.toKopiykas();
}

bool Money::greater(const Money& other) const
{
    return toKopiykas() > other.toKopiykas();
}

bool Money::less(const Money& other) const
{
    return toKopiykas() < other.toKopiykas();
}

// Display
void Money::display() const
{
    cout << hryvnias << ","
        << setw(2) << setfill('0')
        << static_cast<int>(kopiykas)
        << " UAH" << setfill(' ');
}
