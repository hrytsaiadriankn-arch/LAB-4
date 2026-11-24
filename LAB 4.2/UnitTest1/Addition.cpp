#include "pch.h"
#include "Addition.h"
#include <iomanip>
#include <typeinfo>

// ================= INTERFACE =================

Addition::Addition()
{
    data = nullptr;
}

Addition::~Addition()
{
}

// ================= COMPLEX NUMBER =================

ComplexNumber::ComplexNumber(double r, double i)
{
    real = r;
    imag = i;
    data = &real;
}

void ComplexNumber::addition(const Addition& other)
{
    const ComplexNumber* obj =
        dynamic_cast<const ComplexNumber*>(&other);

    if (obj != nullptr)
    {
        real += obj->real;
        imag += obj->imag;
    }
    else
    {
        cout << "Invalid addition of complex numbers!" << endl;
    }
}

void ComplexNumber::Show() const
{
    cout << real;

    if (imag >= 0)
        cout << " + " << imag << "i";
    else
        cout << " - " << -imag << "i";

    cout << endl;
}

// ================= VECTOR =================

Vector10::Vector10(const double arr[10])
{
    for (int i = 0; i < 10; i++)
        elements[i] = arr[i];

    data = elements;
}

void Vector10::addition(const Addition& other)
{
    const Vector10* obj =
        dynamic_cast<const Vector10*>(&other);

    if (obj != nullptr)
    {
        for (int i = 0; i < 10; i++)
            elements[i] += obj->elements[i];
    }
    else
    {
        cout << "Invalid addition of vectors!" << endl;
    }
}

void Vector10::Show() const
{
    cout << "[ ";

    for (int i = 0; i < 10; i++)
        cout << elements[i] << " ";

    cout << "]" << endl;
}

// ================= MATRIX =================

Matrix2x2::Matrix2x2(const double arr[2][2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            elements[i][j] = arr[i][j];
    }

    data = elements;
}

void Matrix2x2::addition(const Addition& other)
{
    const Matrix2x2* obj =
        dynamic_cast<const Matrix2x2*>(&other);

    if (obj != nullptr)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                elements[i][j] += obj->elements[i][j];
        }
    }
    else
    {
        cout << "Invalid addition of matrices!" << endl;
    }
}

void Matrix2x2::Show() const
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            cout << setw(8) << elements[i][j];

        cout << endl;
    }
}
