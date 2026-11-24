
#include "pch.h"
#include "CppUnitTest.h"
#include "Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab43Tests
{
    TEST_CLASS(ArrayTests)
    {
    public:

        // ================= DECIMAL =================

        TEST_METHOD(DecimalConstructor)
        {
            Decimal a("12345");

            Assert::AreEqual(string("12345"), a.toString());
        }

        TEST_METHOD(DecimalNegativeNumber)
        {
            Decimal a("-12345");

            Assert::AreEqual(string("-12345"), a.toString());
        }

        TEST_METHOD(DecimalAddition)
        {
            Decimal a("12345");
            Decimal b("6789");

            Decimal result = a + b;

            Assert::AreEqual(string("19134"), result.toString());
        }

        TEST_METHOD(DecimalSubtraction)
        {
            Decimal a("12345");
            Decimal b("6789");

            Decimal result = a - b;

            Assert::AreEqual(string("5556"), result.toString());
        }

        TEST_METHOD(DecimalMultiplication)
        {
            Decimal a("12345");
            Decimal b("6789");

            Decimal result = a * b;

            Assert::AreEqual(string("83810205"), result.toString());
        }

        TEST_METHOD(DecimalDivision)
        {
            Decimal a("10000");
            Decimal b("100");

            Decimal result = a / b;

            Assert::AreEqual(string("100"), result.toString());
        }

        TEST_METHOD(DecimalRemainder)
        {
            Decimal a("1000");
            Decimal b("300");

            Decimal result = a % b;

            Assert::AreEqual(string("100"), result.toString());
        }

        TEST_METHOD(DecimalComparison)
        {
            Decimal a("1000");
            Decimal b("500");

            Assert::IsTrue(a > b);
            Assert::IsTrue(b < a);
            Assert::IsTrue(a != b);
            Assert::IsTrue(a == Decimal("1000"));
        }

        TEST_METHOD(DecimalNegativeAddition)
        {
            Decimal a("-12345");
            Decimal b("6789");

            Decimal result = a + b;

            Assert::AreEqual(string("-5556"), result.toString());
        }

        TEST_METHOD(DecimalDivisionByZero)
        {
            Decimal a("100");
            Decimal b("0");

            bool exceptionThrown = false;

            try
            {
                Decimal result = a / b;
            }
            catch (const runtime_error&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        // ================= STRING =================

        TEST_METHOD(StringConstructor)
        {
            String text(100, "Hello");

            Assert::AreEqual(string("Hello"), text.toString());
            Assert::AreEqual(5, text.length());
        }

        TEST_METHOD(StringLength)
        {
            String text(100, "Programming");

            Assert::AreEqual(11, text.length());
        }

        TEST_METHOD(StringFind)
        {
            String text(100, "Hello World");

            Assert::AreEqual(6, text.find("World"));
            Assert::AreEqual(-1, text.find("Test"));
        }

        TEST_METHOD(StringDelete)
        {
            String text(100, "Hello World");

            text.eraseSubstring(" World");

            Assert::AreEqual(string("Hello"), text.toString());
        }

        TEST_METHOD(StringInsert)
        {
            String text(100, "Hello");

            text.insertSubstring(5, " World");

            Assert::AreEqual(string("Hello World"), text.toString());
        }

        TEST_METHOD(StringConcatenation)
        {
            String a(100, "Hello");
            String b(100, " World");

            String result = a + b;

            Assert::AreEqual(string("Hello World"), result.toString());
        }

        // ================= ARRAY INDEXING =================

        TEST_METHOD(DecimalIndexing)
        {
            Decimal a("12345");

            Assert::AreEqual((unsigned char)5, a[0]);
            Assert::AreEqual((unsigned char)4, a[1]);
        }

        TEST_METHOD(StringIndexing)
        {
            String text(100, "Hello");

            Assert::AreEqual((unsigned char)5, text[0]);
            Assert::AreEqual((unsigned char)'H', text[1]);
        }

        TEST_METHOD(ArrayInvalidIndex)
        {
            Decimal a("12345");

            bool exceptionThrown = false;

            try
            {
                a[100];
            }
            catch (const out_of_range&)
            {
                exceptionThrown = true;
            }

            Assert::IsTrue(exceptionThrown);
        }

        // ================= POLYMORPHISM =================

        TEST_METHOD(PolymorphismDecimal)
        {
            Decimal a("100");
            Decimal b("200");

            Array* ptr = &a;

            ptr->addition(b);

            Assert::AreEqual(string("300"), a.toString());
        }

        TEST_METHOD(PolymorphismString)
        {
            String a(100, "Hello");
            String b(100, " World");

            Array* ptr = &a;

            ptr->addition(b);

            Assert::AreEqual(string("Hello World"), a.toString());
        }

        TEST_METHOD(PolymorphismType)
        {
            Decimal a("123");
            String b(100, "Test");

            Array* ptr1 = &a;
            Array* ptr2 = &b;

            Assert::IsTrue(dynamic_cast<Decimal*>(ptr1) != nullptr);
            Assert::IsTrue(dynamic_cast<String*>(ptr2) != nullptr);
        }
    };
}
