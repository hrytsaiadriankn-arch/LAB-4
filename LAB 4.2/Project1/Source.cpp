
#include "Addition.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>
using namespace std;

int main()
{
    cout << fixed << setprecision(2);

    // Комплексні числа
    ComplexNumber c1(5, 2);
    ComplexNumber c2(4, 3);

    // Вектори
    double v1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    double v2[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    Vector10 vec1(v1);
    Vector10 vec2(v2);

    // Матриці
    double m1[2][2] = {
        { 1, 2 },
        { 3, 4 }
    };

    double m2[2][2] = {
        { 5, 6 },
        { 7, 8 }
    };

    Matrix2x2 mat1(m1);
    Matrix2x2 mat2(m2);

    // Масив вказівників на інтерфейс
    Addition* objects[6] = {
        &c1, &c2,
        &vec1, &vec2,
        &mat1, &mat2
    };

    cout << "========== LABORATORY WORK 4.2 ==========" << endl;
    cout << "Variant 14" << endl;

    // Визначення справжнього типу об'єктів
    cout << "\n========== OBJECT TYPES ==========" << endl;

    for (int i = 0; i < 6; i++)
    {
        cout << "\nObject " << i + 1 << ": ";

        if (typeid(*objects[i]) == typeid(ComplexNumber))
            cout << "ComplexNumber" << endl;
        else if (typeid(*objects[i]) == typeid(Vector10))
            cout << "Vector10" << endl;
        else if (typeid(*objects[i]) == typeid(Matrix2x2))
            cout << "Matrix2x2" << endl;

        objects[i]->Show();
    }

    // Додавання комплексних чисел
    cout << "\n========== COMPLEX NUMBERS ==========" << endl;

    cout << "First number: ";
    objects[0]->Show();

    cout << "Second number: ";
    objects[1]->Show();

    objects[0]->addition(*objects[1]);

    cout << "Result: ";
    objects[0]->Show();

    // Додавання векторів
    cout << "\n========== VECTORS ==========" << endl;

    cout << "First vector: ";
    objects[2]->Show();

    cout << "Second vector: ";
    objects[3]->Show();

    objects[2]->addition(*objects[3]);

    cout << "Result: ";
    objects[2]->Show();

    // Додавання матриць
    cout << "\n========== MATRICES ==========" << endl;

    cout << "First matrix:" << endl;
    objects[4]->Show();

    cout << "Second matrix:" << endl;
    objects[5]->Show();

    objects[4]->addition(*objects[5]);

    cout << "Result:" << endl;
    objects[4]->Show();

    cout << "\n========== PROGRAM FINISHED ==========" << endl;

    return 0;
}
