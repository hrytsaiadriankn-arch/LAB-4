
#include "pch.h"
#include "CppUnitTest.h"

#include "D:/2 курс 1 семестр/LAB 4.4/Project1/Complex.h"
#include "D:/2 курс 1 семестр/LAB 4.4/Project1/Money.h"
#include "D:/2 курс 1 семестр/LAB 4.4/Project1/Pair.h"

#include <sstream>
#include <string>
#include <memory>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    // Function for capturing object output
    string CaptureDisplay(const Pair& obj)
    {
        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        obj.display();

        cout.rdbuf(oldBuffer);

        return output.str();
    }

    TEST_CLASS(UnitTest1)
    {
    public:

        // =====================================
        // MONEY TESTS
        // =====================================

        TEST_METHOD(TestMoneyAddition)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.add(m2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "200,75 UAH"
            );
        }

        TEST_METHOD(TestMoneySubtraction)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.sub(m2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "100,25 UAH"
            );
        }

        TEST_METHOD(TestMoneyMultiplication)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.mul(m2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "7562,63 UAH"
            );
        }

        TEST_METHOD(TestMoneyDivision)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.div(m2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "3,00 UAH"
            );
        }

        TEST_METHOD(TestMoneyDivideByFraction)
        {
            Money m1(150, 50);

            Money result = m1.divideBy(2.5);

            Assert::IsTrue(
                CaptureDisplay(result) == "60,20 UAH"
            );
        }

        TEST_METHOD(TestMoneyMultiplyByFraction)
        {
            Money m1(150, 50);

            Money result = m1.multiplyBy(2.5);

            Assert::IsTrue(
                CaptureDisplay(result) == "376,25 UAH"
            );
        }

        TEST_METHOD(TestMoneyComparison)
        {
            Money m1(150, 50);
            Money m2(50, 25);
            Money m3(150, 50);

            Assert::IsTrue(m1.greater(m2));
            Assert::IsTrue(m2.less(m1));
            Assert::IsTrue(m1.equ(m3));
            Assert::IsFalse(m1.equ(m2));
        }

        TEST_METHOD(TestMoneyDivisionByZero)
        {
            Money m1(150, 50);
            Money m2(0, 0);

            bool exceptionThrown = false;

            try
            {
                m1.div(m2);
            }
            catch (const runtime_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(TestMoneyDivideByZeroFraction)
        {
            Money m1(150, 50);

            bool exceptionThrown = false;

            try
            {
                m1.divideBy(0);
            }
            catch (const runtime_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        // =====================================
        // COMPLEX TESTS
        // =====================================

        TEST_METHOD(TestComplexAddition)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.add(c2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "9.00 + 5.00i"
            );
        }

        TEST_METHOD(TestComplexSubtraction)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.sub(c2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "1.00 - 1.00i"
            );
        }

        TEST_METHOD(TestComplexMultiplication)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.mul(c2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "14.00 + 23.00i"
            );
        }

        TEST_METHOD(TestComplexDivision)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.div(c2);

            Assert::IsTrue(
                CaptureDisplay(*result) == "1.04 - 0.28i"
            );
        }

        TEST_METHOD(TestComplexComparison)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);
            Complex c3(5, 2);

            Assert::IsTrue(c1.equ(c3));
            Assert::IsFalse(c1.equ(c2));
        }

        TEST_METHOD(TestComplexConjugate)
        {
            Complex c1(5, 2);

            Complex result = c1.conj();

            Assert::IsTrue(
                CaptureDisplay(result) == "5.00 - 2.00i"
            );
        }

        TEST_METHOD(TestComplexDivisionByZero)
        {
            Complex c1(5, 2);
            Complex c2(0, 0);

            bool exceptionThrown = false;

            try
            {
                c1.div(c2);
            }
            catch (const runtime_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        // =====================================
        // POLYMORPHISM TEST
        // =====================================

        TEST_METHOD(TestPolymorphism)
        {
            Money m1(150, 50);
            Complex c1(5, 2);

            Pair* objects[2];

            objects[0] = &m1;
            objects[1] = &c1;

            Assert::IsTrue(
                CaptureDisplay(*objects[0]) == "150,50 UAH"
            );

            Assert::IsTrue(
                CaptureDisplay(*objects[1]) == "5.00 + 2.00i"
            );
        }
    };
}
