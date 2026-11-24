#include <iostream>
#include "pch.h"
#include "CppUnitTest.h"
#include "D:/2 курс 1 семестр/LAB 4.5/Project1/Complex.h"
#include "D:/2 курс 1 семестр/LAB 4.5/Project1/Money.h"
#include "D:/2 курс 1 семестр/LAB 4.5/Project1/Pair.h"
#include <sstream>
#include <string>
#include <memory>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    string CaptureDisplay(const Pair& obj)
    {
        ostringstream output;
        streambuf* oldBuffer = std::cout.rdbuf(output.rdbuf());

        obj.display();

        std::cout.rdbuf(oldBuffer);

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

            Assert::AreEqual(
                string("200,75 UAH"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestMoneySubtraction)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.sub(m2);

            Assert::AreEqual(
                string("100,25 UAH"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestMoneyMultiplication)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.mul(m2);

            Assert::AreEqual(
                string("7562,63 UAH"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestMoneyDivision)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            unique_ptr<Pair> result = m1.div(m2);

            Assert::AreEqual(
                string("3,00 UAH"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestMoneyDivideByFraction)
        {
            Money m1(150, 50);

            Money result = m1.divideBy(2.5);

            Assert::AreEqual(
                string("60,20 UAH"),
                CaptureDisplay(result)
            );
        }

        TEST_METHOD(TestMoneyMultiplyByFraction)
        {
            Money m1(150, 50);

            Money result = m1.multiplyBy(2.5);

            Assert::AreEqual(
                string("376,25 UAH"),
                CaptureDisplay(result)
            );
        }

        TEST_METHOD(TestMoneyComparison)
        {
            Money m1(150, 50);
            Money m2(50, 25);
            Money m3(150, 50);

            Assert::IsTrue(m1.equ(m3));
            Assert::IsTrue(m1.greater(m2));
            Assert::IsTrue(m2.less(m1));
            Assert::IsFalse(m1.equ(m2));
        }

        TEST_METHOD(TestMoneyDivisionByZero)
        {
            Money m1(150, 50);
            Money m2(0, 0);

            Assert::ExpectException<runtime_error>(
                [&]() { m1.div(m2); }
            );
        }

        // =====================================
        // COMPLEX TESTS
        // =====================================

        TEST_METHOD(TestComplexAddition)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.add(c2);

            Assert::AreEqual(
                string("9.00 + 5.00i"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestComplexSubtraction)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.sub(c2);

            Assert::AreEqual(
                string("1.00 - 1.00i"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestComplexMultiplication)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.mul(c2);

            Assert::AreEqual(
                string("14.00 + 23.00i"),
                CaptureDisplay(*result)
            );
        }

        TEST_METHOD(TestComplexDivision)
        {
            Complex c1(5, 2);
            Complex c2(4, 3);

            unique_ptr<Pair> result = c1.div(c2);

            Assert::AreEqual(
                string("1.04 - 0.28i"),
                CaptureDisplay(*result)
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

            Assert::AreEqual(
                string("5.00 - 2.00i"),
                CaptureDisplay(result)
            );
        }

        TEST_METHOD(TestComplexDivisionByZero)
        {
            Complex c1(5, 2);
            Complex c2(0, 0);

            Assert::ExpectException<runtime_error>(
                [&]() { c1.div(c2); }
            );
        }

        // =====================================
        // INTERFACE AND POLYMORPHISM TESTS
        // =====================================

        TEST_METHOD(TestPolymorphism)
        {
            Money m1(150, 50);
            Complex c1(5, 2);

            Pair* objects[2] = { &m1, &c1 };

            Assert::AreEqual(
                string("150,50 UAH"),
                CaptureDisplay(*objects[0])
            );

            Assert::AreEqual(
                string("5.00 + 2.00i"),
                CaptureDisplay(*objects[1])
            );
        }

        TEST_METHOD(TestInterfaceAddition)
        {
            Money m1(150, 50);
            Money m2(50, 25);

            Pair* p1 = &m1;
            Pair* p2 = &m2;

            unique_ptr<Pair> result = p1->add(*p2);

            Assert::AreEqual(
                string("200,75 UAH"),
                CaptureDisplay(*result)
            );
        }
    };
}