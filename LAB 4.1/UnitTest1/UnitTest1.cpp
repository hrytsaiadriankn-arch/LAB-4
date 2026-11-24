
#include "pch.h"
#include "CppUnitTest.h"
#include "Addition.h"
#include <sstream>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    // Отримання результату методу Show()
    string CaptureOutput(const Addition& obj)
    {
        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        obj.Show();

        cout.rdbuf(oldBuffer);

        return output.str();
    }

    TEST_CLASS(UnitTest1)
    {
    public:

        // Тест додавання комплексних чисел
        TEST_METHOD(TestComplexAddition)
        {
            ComplexNumber c1(5, 2);
            ComplexNumber c2(4, 3);

            c1.addition(c2);

            string result = CaptureOutput(c1);

            Assert::AreEqual(string("9 + 5i\n"), result);
        }

        // Тест додавання векторів
        TEST_METHOD(TestVectorAddition)
        {
            double v1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            double v2[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

            Vector10 vec1(v1);
            Vector10 vec2(v2);

            vec1.addition(vec2);

            string result = CaptureOutput(vec1);
            istringstream input(result);

            char bracket;
            double value;

            input >> bracket;

            Assert::AreEqual('[', bracket);

            for (int i = 0; i < 10; i++)
            {
                input >> value;
                Assert::AreEqual(11.0, value, 0.001);
            }

            input >> bracket;
            Assert::AreEqual(']', bracket);
        }

        // Тест додавання матриць
        TEST_METHOD(TestMatrixAddition)
        {
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

            mat1.addition(mat2);

            string result = CaptureOutput(mat1);
            istringstream input(result);

            double expected[2][2] = {
                { 6, 8 },
                { 10, 12 }
            };

            double value;

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    input >> value;

                    Assert::AreEqual(
                        expected[i][j],
                        value,
                        0.001
                    );
                }
            }
        }
    };
}