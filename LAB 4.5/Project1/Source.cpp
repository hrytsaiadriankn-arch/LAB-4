
#include <iostream>
#include <typeinfo>

#include "Pair.h"
#include "Money.h"
#include "Complex.h"

using namespace std;

// Function receiving the interface by reference
void printPair(const Pair& obj)
{
    cout << "Value: ";
    obj.display();
    cout << endl;
}

int main()
{
    cout << "========== LABORATORY WORK 4.5 ==========\n";
    cout << "Variant 14\n\n";

    // ======================================
    // MONEY
    // ======================================

    cout << "========== MONEY ==========\n";

    Money m1(150, 50);
    Money m2(50, 25);

    Pair* p1 = &m1;
    Pair* p2 = &m2;

    cout << "Money 1: ";
    p1->display();

    cout << "\nMoney 2: ";
    p2->display();

    cout << "\n\nArithmetic operations:\n";

    cout << "Addition: ";
    p1->add(*p2)->display();

    cout << "\nSubtraction: ";
    p1->sub(*p2)->display();

    cout << "\nMultiplication: ";
    p1->mul(*p2)->display();

    cout << "\nDivision: ";
    p1->div(*p2)->display();

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

    Pair* p3 = &c1;
    Pair* p4 = &c2;

    cout << "Complex 1: ";
    p3->display();

    cout << "\nComplex 2: ";
    p4->display();

    cout << "\n\nArithmetic operations:\n";

    cout << "Addition: ";
    p3->add(*p4)->display();

    cout << "\nSubtraction: ";
    p3->sub(*p4)->display();

    cout << "\nMultiplication: ";
    p3->mul(*p4)->display();

    cout << "\nDivision: ";
    p3->div(*p4)->display();

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

    Pair* objects[4];

    objects[0] = &m1;
    objects[1] = &m2;
    objects[2] = &c1;
    objects[3] = &c2;

    for (int i = 0; i < 4; i++)
    {
        cout << "\nObject " << i + 1 << ":\n";

        cout << "Real type: "
            << typeid(*objects[i]).name() << endl;

        printPair(*objects[i]);
    }

    // ======================================
    // VIRTUAL FUNCTION CALLS
    // ======================================

    cout << "\n========== INTERFACE CALLS ==========\n";

    for (int i = 0; i < 4; i++)
    {
        cout << "\nObject " << i + 1 << ":\n";

        objects[i]->display();
        cout << endl;
    }

    cout << "\n========== PROGRAM FINISHED ==========\n";

    return 0;
}
