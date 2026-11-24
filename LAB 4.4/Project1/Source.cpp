
#include <iostream>
#include <typeinfo>

#include "Pair.h"
#include "Money.h"
#include "Complex.h"

using namespace std;

int main()
{
    cout << "========== LABORATORY WORK 4.4 ==========\n";
    cout << "Variant 14\n\n";

    // ======================================
    // MONEY
    // ======================================

    cout << "========== MONEY ==========\n";

    Money m1(150, 50);
    Money m2(50, 25);

    cout << "Money 1: ";
    m1.display();

    cout << "\nMoney 2: ";
    m2.display();

    cout << "\n\nArithmetic operations:\n";

    cout << "Addition: ";
    m1.add(m2)->display();

    cout << "\nSubtraction: ";
    m1.sub(m2)->display();

    cout << "\nMultiplication: ";
    m1.mul(m2)->display();

    cout << "\nDivision: ";
    m1.div(m2)->display();

    cout << "\nDivision by 2.5: ";
    m1.divideBy(2.5).display();

    cout << "\nMultiplication by 2.5: ";
    m1.multiplyBy(2.5).display();

    cout << "\n\nComparison:\n";

    cout << "Money 1 == Money 2: "
        << (m1.equ(m2) ? "true" : "false");

    cout << "\nMoney 1 > Money 2: "
        << (m1.greater(m2) ? "true" : "false");

    cout << "\nMoney 1 < Money 2: "
        << (m1.less(m2) ? "true" : "false");

    // ======================================
    // COMPLEX
    // ======================================

    cout << "\n\n========== COMPLEX ==========\n";

    Complex c1(5, 2);
    Complex c2(4, 3);

    cout << "Complex 1: ";
    c1.display();

    cout << "\nComplex 2: ";
    c2.display();

    cout << "\n\nArithmetic operations:\n";

    cout << "Addition: ";
    c1.add(c2)->display();

    cout << "\nSubtraction: ";
    c1.sub(c2)->display();

    cout << "\nMultiplication: ";
    c1.mul(c2)->display();

    cout << "\nDivision: ";
    c1.div(c2)->display();

    cout << "\n\nComparison:\n";

    cout << "Complex 1 == Complex 2: "
        << (c1.equ(c2) ? "true" : "false");

    cout << "\n\nComplex conjugate:\n";

    cout << "Conjugate of Complex 1: ";
    c1.conj().display();

    // ======================================
    // POLYMORPHISM
    // ======================================

    cout << "\n\n========== POLYMORPHISM ==========\n";

    Pair* objects[2];

    objects[0] = &m1;
    objects[1] = &c1;

    for (int i = 0; i < 2; i++)
    {
        cout << "\nObject " << i + 1 << ":\n";

        cout << "Real type: "
            << typeid(*objects[i]).name() << endl;

        cout << "Value: ";
        objects[i]->display();

        cout << endl;
    }

    cout << "\n========== PROGRAM FINISHED ==========\n";

    return 0;
}
