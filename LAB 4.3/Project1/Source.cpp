
#include "Array.h"

#include <iostream>
#include <typeinfo>
#include <stdexcept>

using namespace std;

int main()
{
    try
    {
        cout << "========== LABORATORY WORK 4.3 ==========" << endl;
        cout << "Variant 14" << endl;

        // ================= DECIMAL =================

        cout << "\n========== DECIMAL ==========" << endl;

        Decimal a("12345678901234567890");
        Decimal b("987654321");

        a.Show();
        b.Show();

        cout << "\nArithmetic operations:" << endl;

        cout << "Addition:       " << (a + b).toString() << endl;
        cout << "Subtraction:    " << (a - b).toString() << endl;
        cout << "Multiplication: " << (a * b).toString() << endl;
        cout << "Division:       " << (a / b).toString() << endl;
        cout << "Remainder:      " << (a % b).toString() << endl;

        cout << "\nComparison:" << endl;

        cout << "a == b: " << (a == b) << endl;
        cout << "a != b: " << (a != b) << endl;
        cout << "a > b:  " << (a > b) << endl;
        cout << "a < b:  " << (a < b) << endl;

        Decimal negative("-12345");
        Decimal positive("6789");

        cout << "\nSigned numbers:" << endl;

        cout << negative.toString() << " + "
            << positive.toString() << " = "
            << (negative + positive).toString() << endl;

        // ================= STRING =================

        cout << "\n========== STRING ==========" << endl;

        String first(100, "Hello");
        String second(100, " World");

        first.Show();
        second.Show();

        cout << "\nString operations:" << endl;

        cout << "Length: " << first.length() << endl;

        cout << "Find 'ell': "
            << first.find("ell") << endl;

        String edited(100, "Hello beautiful World");

        edited.eraseSubstring("beautiful ");

        cout << "After deletion: "
            << edited.toString() << endl;

        edited.insertSubstring(5, " wonderful");

        cout << "After insertion: "
            << edited.toString() << endl;

        String combined = first + second;

        cout << "Concatenation: "
            << combined.toString() << endl;

        // ================= POLYMORPHISM =================

        cout << "\n========== POLYMORPHISM ==========" << endl;

        Decimal d1("12345");
        Decimal d2("67890");

        String s1(100, "First");
        String s2(100, "Second");

        Array* objects[4];

        objects[0] = &d1;
        objects[1] = &d2;
        objects[2] = &s1;
        objects[3] = &s2;

        cout << "\nReal object types:" << endl;

        for (int i = 0; i < 4; i++)
        {
            cout << "\nObject " << i + 1 << ": "
                << typeid(*objects[i]).name() << endl;

            objects[i]->Show();
        }

        // Virtual function through base pointer

        cout << "\nVirtual addition through base pointer:" << endl;

        objects[0]->addition(*objects[1]);
        objects[2]->addition(*objects[3]);

        objects[0]->Show();
        objects[2]->Show();

        // Virtual function through base reference

        cout << "\nVirtual function through base reference:" << endl;

        Array& reference = d1;
        reference.Show();

        // Direct call

        cout << "\nDirect virtual function call:" << endl;

        d2.Show();
        s2.Show();

        // ================= INDEXING =================

        cout << "\n========== INDEXING ==========" << endl;

        cout << "First digit of Decimal: "
            << (int)d2[0] << endl;

        cout << "First character of String: "
            << (char)s2[1] << endl;

        cout << "\nProgram completed successfully." << endl;
    }
    catch (const exception& e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
