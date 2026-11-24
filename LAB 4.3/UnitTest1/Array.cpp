#include "pch.h"
#include "Array.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

// ==================== ARRAY ====================

bool Array::rangeCheck(int index) const
{
    return index >= 0 && index < count;
}

Array::Array(int size, unsigned char value)
{
    if (size < 0 || size > MAX_SIZE)
        throw out_of_range("Invalid array size!");

    count = size;
    elements = new unsigned char[count];

    for (int i = 0; i < count; i++)
        elements[i] = value;
}

Array::Array(const Array& other)
{
    count = other.count;
    elements = new unsigned char[count];

    for (int i = 0; i < count; i++)
        elements[i] = other.elements[i];
}

Array::~Array()
{
    delete[] elements;
}

Array& Array::operator=(const Array& other)
{
    if (this != &other)
    {
        delete[] elements;

        count = other.count;
        elements = new unsigned char[count];

        for (int i = 0; i < count; i++)
            elements[i] = other.elements[i];
    }

    return *this;
}

unsigned char& Array::operator[](int index)
{
    if (!rangeCheck(index))
        throw out_of_range("Array index out of range!");

    return elements[index];
}

const unsigned char& Array::operator[](int index) const
{
    if (!rangeCheck(index))
        throw out_of_range("Array index out of range!");

    return elements[index];
}

int Array::getSize() const
{
    return count;
}

void Array::addition(const Array& other)
{
    if (count != other.count)
        throw invalid_argument("Array sizes must be equal!");

    for (int i = 0; i < count; i++)
        elements[i] += other.elements[i];
}

void Array::Show() const
{
    cout << "Array: ";

    for (int i = 0; i < count; i++)
        cout << (int)elements[i] << " ";

    cout << endl;
}

// ==================== DECIMAL ====================

Decimal::Decimal(const string& number)
    : Array(1, 0), sign(1)
{
    if (number.empty())
        throw invalid_argument("Empty decimal number!");

    int start = 0;

    if (number[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    else if (number[0] == '+')
    {
        start = 1;
    }

    if (start == (int)number.size())
        throw invalid_argument("Invalid decimal number!");

    int digitsCount = (int)number.size() - start;

    if (digitsCount > 100)
        throw out_of_range("Decimal supports maximum 100 digits!");

    for (int i = start; i < (int)number.size(); i++)
    {
        if (number[i] < '0' || number[i] > '9')
            throw invalid_argument("Invalid decimal digit!");
    }

    delete[] elements;

    count = digitsCount;
    elements = new unsigned char[count];

    for (int i = 0; i < count; i++)
    {
        char ch = number[number.size() - 1 - i];
        elements[i] = ch - '0';
    }

    removeZeros();
}

Decimal::Decimal(const Decimal& other)
    : Array(other), sign(other.sign)
{
}

Decimal& Decimal::operator=(const Decimal& other)
{
    if (this != &other)
    {
        Array::operator=(other);
        sign = other.sign;
    }

    return *this;
}

void Decimal::removeZeros()
{
    while (count > 1 && elements[count - 1] == 0)
        count--;

    if (count == 1 && elements[0] == 0)
        sign = 1;
}

string Decimal::toString() const
{
    string result;

    if (sign < 0)
        result += '-';

    for (int i = count - 1; i >= 0; i--)
        result += char('0' + elements[i]);

    return result;
}

void Decimal::Show() const
{
    cout << "Decimal: " << toString() << endl;
}

void Decimal::addition(const Array& other)
{
    const Decimal* number = dynamic_cast<const Decimal*>(&other);

    if (number == nullptr)
        throw invalid_argument("Cannot add different object types!");

    *this = *this + *number;
}

int Decimal::compareAbs(const Decimal& a, const Decimal& b)
{
    if (a.count > b.count) return 1;
    if (a.count < b.count) return -1;

    for (int i = a.count - 1; i >= 0; i--)
    {
        if (a.elements[i] > b.elements[i]) return 1;
        if (a.elements[i] < b.elements[i]) return -1;
    }

    return 0;
}

vector<unsigned char> Decimal::addAbs(
    const Decimal& a, const Decimal& b)
{
    vector<unsigned char> result;

    int carry = 0;
    int n = max(a.count, b.count);

    for (int i = 0; i < n; i++)
    {
        int sum = carry;

        if (i < a.count)
            sum += a.elements[i];

        if (i < b.count)
            sum += b.elements[i];

        result.push_back(sum % 10);
        carry = sum / 10;
    }

    if (carry)
        result.push_back(carry);

    return result;
}

vector<unsigned char> Decimal::subtractAbs(
    const Decimal& a, const Decimal& b)
{
    vector<unsigned char> result;

    int borrow = 0;

    for (int i = 0; i < a.count; i++)
    {
        int digit = a.elements[i] - borrow;
        int sub = (i < b.count) ? b.elements[i] : 0;

        if (digit < sub)
        {
            digit += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result.push_back(digit - sub);
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    return result;
}

Decimal Decimal::fromDigits(
    const vector<unsigned char>& digits, int resultSign)
{
    Decimal result("0");

    delete[] result.elements;

    result.count = (int)digits.size();
    result.elements = new unsigned char[result.count];

    for (int i = 0; i < result.count; i++)
        result.elements[i] = digits[i];

    result.sign = resultSign;
    result.removeZeros();

    return result;
}

Decimal Decimal::operator-() const
{
    Decimal result(*this);

    result.sign *= -1;

    if (result.count == 1 && result.elements[0] == 0)
        result.sign = 1;

    return result;
}

Decimal Decimal::operator+(const Decimal& other) const
{
    if (sign == other.sign)
        return fromDigits(addAbs(*this, other), sign);

    int comparison = compareAbs(*this, other);

    if (comparison == 0)
        return Decimal("0");

    if (comparison > 0)
        return fromDigits(subtractAbs(*this, other), sign);

    return fromDigits(subtractAbs(other, *this), other.sign);
}

Decimal Decimal::operator-(const Decimal& other) const
{
    return *this + (-other);
}

Decimal Decimal::operator*(const Decimal& other) const
{
    vector<unsigned char> result(count + other.count, 0);

    for (int i = 0; i < count; i++)
    {
        int carry = 0;

        for (int j = 0; j < other.count; j++)
        {
            int current = result[i + j]
                + elements[i] * other.elements[j] + carry;

            result[i + j] = current % 10;
            carry = current / 10;
        }

        int pos = i + other.count;

        while (carry > 0 && pos < (int)result.size())
        {
            int current = result[pos] + carry;

            result[pos] = current % 10;
            carry = current / 10;
            pos++;
        }
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    return fromDigits(result, sign * other.sign);
}

Decimal Decimal::operator/(const Decimal& other) const
{
    if (other.count == 1 && other.elements[0] == 0)
        throw runtime_error("Division by zero!");

    Decimal remainder("0");
    vector<unsigned char> quotient(count, 0);

    for (int i = count - 1; i >= 0; i--)
    {
        vector<unsigned char> shifted;

        shifted.push_back(elements[i]);

        for (int j = 0; j < remainder.count; j++)
            shifted.push_back(remainder.elements[j]);

        remainder = fromDigits(shifted, 1);

        int digit = 0;

        while (compareAbs(remainder, other) >= 0)
        {
            remainder = fromDigits(
                subtractAbs(remainder, other), 1);

            digit++;
        }

        quotient[i] = digit;
    }

    while (quotient.size() > 1 && quotient.back() == 0)
        quotient.pop_back();

    return fromDigits(quotient, sign * other.sign);
}

Decimal Decimal::operator%(const Decimal& other) const
{
    if (other.count == 1 && other.elements[0] == 0)
        throw runtime_error("Division by zero!");

    Decimal quotient = *this / other;

    return *this - quotient * other;
}

bool Decimal::operator==(const Decimal& other) const
{
    return sign == other.sign &&
        compareAbs(*this, other) == 0;
}

bool Decimal::operator!=(const Decimal& other) const
{
    return !(*this == other);
}

bool Decimal::operator<(const Decimal& other) const
{
    if (sign != other.sign)
        return sign < other.sign;

    int comparison = compareAbs(*this, other);

    return sign > 0 ? comparison < 0 : comparison > 0;
}

bool Decimal::operator>(const Decimal& other) const
{
    return other < *this;
}

bool Decimal::operator<=(const Decimal& other) const
{
    return !(*this > other);
}

bool Decimal::operator>=(const Decimal& other) const
{
    return !(*this < other);
}

// ==================== STRING ====================

String::String(int maxLength, const string& text)
    : Array(maxLength + 1, 0)
{
    if (maxLength < 0 || maxLength > 255)
        throw out_of_range("Maximum string length must be 0..255!");

    if ((int)text.length() > maxLength)
        throw out_of_range("Text is longer than maximum length!");

    elements[0] = (unsigned char)text.length();

    for (int i = 0; i < (int)text.length(); i++)
        elements[i + 1] = (unsigned char)text[i];
}

String::String(const String& other)
    : Array(other)
{
}

string String::toString() const
{
    string result;

    for (int i = 1; i <= elements[0]; i++)
        result += (char)elements[i];

    return result;
}

int String::length() const
{
    return elements[0];
}

void String::Show() const
{
    cout << "String: " << toString()
        << " (length = " << length() << ")" << endl;
}

void String::addition(const Array& other)
{
    const String* str = dynamic_cast<const String*>(&other);

    if (str == nullptr)
        throw invalid_argument("Cannot add different object types!");

    *this = *this + *str;
}

int String::find(const string& substring) const
{
    if (substring.empty())
        return 0;

    string source = toString();

    size_t position = source.find(substring);

    if (position == string::npos)
        return -1;

    return (int)position;
}

void String::eraseSubstring(const string& substring)
{
    if (substring.empty())
        return;

    string source = toString();

    size_t position = source.find(substring);

    if (position == string::npos)
        return;

    source.erase(position, substring.length());

    if ((int)source.length() > count - 1)
        throw out_of_range("String is too long!");

    elements[0] = (unsigned char)source.length();

    for (int i = 0; i < (int)source.length(); i++)
        elements[i + 1] = (unsigned char)source[i];
}

void String::insertSubstring(
    int position, const string& substring)
{
    string source = toString();

    if (position < 0 || position >(int)source.length())
        throw out_of_range("Invalid insertion position!");

    if ((int)(source.length() + substring.length()) > count - 1)
        throw out_of_range("String is too long!");

    source.insert(position, substring);

    elements[0] = (unsigned char)source.length();

    for (int i = 0; i < (int)source.length(); i++)
        elements[i + 1] = (unsigned char)source[i];
}

String String::operator+(const String& other) const
{
    string result = toString() + other.toString();

    if ((int)result.length() > 255)
        throw out_of_range("Maximum string length exceeded!");

    return String(255, result);
}
