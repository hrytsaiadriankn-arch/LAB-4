
#pragma once
#include <iostream>
using namespace std;

// Інтерфейс додавання
class Addition
{
protected:
    void* data;

public:
    Addition();

    virtual void addition(const Addition& other) = 0;
    virtual void Show() const = 0;

    virtual ~Addition() = 0;
};

// Клас комплексних чисел
class ComplexNumber : public Addition
{
private:
    double real;
    double imag;

public:
    ComplexNumber(double r = 0, double i = 0);

    void addition(const Addition& other) override;
    void Show() const override;
};

// Клас вектора з 10 елементів
class Vector10 : public Addition
{
private:
    double elements[10];

public:
    Vector10(const double arr[10]);

    void addition(const Addition& other) override;
    void Show() const override;
};

// Клас матриці 2x2
class Matrix2x2 : public Addition
{
private:
    double elements[2][2];

public:
    Matrix2x2(const double arr[2][2]);

    void addition(const Addition& other) override;
    void Show() const override;
};
