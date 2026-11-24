
#include "pch.h"
#include "CppUnitTest.h"
#include "D:/2 курс 1 семестр/LAB 4.2/Project1/Addition.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace UnitTest42
{
    // Допоміжна функція для перехоплення Show()
    string GetOutput(const Addition& obj)
    {
        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        obj.Show();

        cout.rdbuf(oldBuffer);

        return output.str();
    }

    TEST_CLASS(ComplexNumberTests)
    {
    public:

        TEST_METHOD(TestComplexAddition)
        {
            ComplexNumber a(5, 2);
            ComplexNumber b(4, 3);

            a.addition(b);

            string result = GetOutput(a);

            Assert::AreEqual(string("9 + 5i\n"), result);
        }

        TEST_METHOD(TestComplexNegativeImaginary)
        {
            ComplexNumber a(5, 2);
            ComplexNumber b(1, -5);

            a.addition(b);

            string result = GetOutput(a);

            Assert::AreEqual(string("6 - 3i\n"), result);
        }

        TEST_METHOD(TestComplexZero)
        {
            ComplexNumber a(0, 0);
            ComplexNumber b(0, 0);

            a.addition(b);

            string result = GetOutput(a);

            Assert::AreEqual(string("0 + 0i\n"), result);
        }
    };

    TEST_CLASS(VectorTests)
    {
    public:

        TEST_METHOD(TestVectorAddition)
        {
            double arr1[10] =
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10
            };

            double arr2[10] =
            {
                10, 9, 8, 7, 6, 5, 4, 3, 2, 1
            };

            Vector10 a(arr1);
            Vector10 b(arr2);

            a.addition(b);

            string result = GetOutput(a);

            string expected =
                "[ 11 11 11 11 11 11 11 11 11 11 ]\n";

            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(TestVectorWithZeros)
        {
            double arr1[10] = {};
            double arr2[10] =
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10
            };

            Vector10 a(arr1);
            Vector10 b(arr2);

            a.addition(b);

            string result = GetOutput(a);

            string expected =
                "[ 1 2 3 4 5 6 7 8 9 10 ]\n";

            Assert::AreEqual(expected, result);
        }
    };

    TEST_CLASS(MatrixTests)
    {
    public:

        TEST_METHOD(TestMatrixAddition)
        {
            double arr1[2][2] =
            {
                { 1, 2 },
                { 3, 4 }
            };

            double arr2[2][2] =
            {
                { 5, 6 },
                { 7, 8 }
            };

            Matrix2x2 a(arr1);
            Matrix2x2 b(arr2);

            a.addition(b);

            string result = GetOutput(a);

            string expected =
                "       6       8\n"
                "      10      12\n";

            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(TestMatrixWithZeros)
        {
            double arr1[2][2] = {};
            double arr2[2][2] =
            {
                { 2, 4 },
                { 6, 8 }
            };

            Matrix2x2 a(arr1);
            Matrix2x2 b(arr2);

            a.addition(b);

            string result = GetOutput(a);

            string expected =
                "       2       4\n"
                "       6       8\n";

            Assert::AreEqual(expected, result);
        }
    };

    TEST_CLASS(PolymorphismTests)
    {
    public:

        TEST_METHOD(TestPolymorphismComplex)
        {
            ComplexNumber a(2, 3);
            ComplexNumber b(4, 5);

            Addition* ptr = &a;

            ptr->addition(b);

            Assert::AreEqual(
                string("6 + 8i"),
                GetOutput(*ptr).substr(0, 7)
            );
        }

        TEST_METHOD(TestPolymorphismVector)
        {
            double arr1[10] = {};
            double arr2[10] = {};

            Vector10 a(arr1);
            Vector10 b(arr2);

            Addition* ptr = &a;

            ptr->addition(b);

            string result = GetOutput(*ptr);

            Assert::IsTrue(
                result.find("[ 0 0 0 0 0 0 0 0 0 0 ]") != string::npos
            );
        }

        TEST_METHOD(TestPolymorphismMatrix)
        {
            double arr1[2][2] = {};
            double arr2[2][2] = {};

            Matrix2x2 a(arr1);
            Matrix2x2 b(arr2);

            Addition* ptr = &a;

            ptr->addition(b);

            string result = GetOutput(*ptr);

            Assert::IsTrue(
                result.find("0") != string::npos
            );
        }
    };

    TEST_CLASS(TypeCastingTests)
    {
    public:

        TEST_METHOD(TestDynamicCastComplex)
        {
            ComplexNumber obj(1, 2);

            Addition* ptr = &obj;

            ComplexNumber* converted =
                dynamic_cast<ComplexNumber*>(ptr);

            Assert::IsNotNull(converted);
        }

        TEST_METHOD(TestDynamicCastVector)
        {
            double arr[10] = {};

            Vector10 obj(arr);

            Addition* ptr = &obj;

            Vector10* converted =
                dynamic_cast<Vector10*>(ptr);

            Assert::IsNotNull(converted);
        }

        TEST_METHOD(TestDynamicCastMatrix)
        {
            double arr[2][2] = {};

            Matrix2x2 obj(arr);

            Addition* ptr = &obj;

            Matrix2x2* converted =
                dynamic_cast<Matrix2x2*>(ptr);

            Assert::IsNotNull(converted);
        }

        TEST_METHOD(TestInvalidDynamicCast)
        {
            ComplexNumber obj(1, 2);

            Addition* ptr = &obj;

            Vector10* converted =
                dynamic_cast<Vector10*>(ptr);

            Assert::IsNull(converted);
        }
    };
}
