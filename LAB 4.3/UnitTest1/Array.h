
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== BASE CLASS ARRAY ====================

class Array
{
protected:
    static const int MAX_SIZE = 256;

    unsigned char* elements;
    int count;

    bool rangeCheck(int index) const;

public:
    Array(int size, unsigned char value = 0);
    Array(const Array& other);
    virtual ~Array();

    Array& operator=(const Array& other);

    unsigned char& operator[](int index);
    const unsigned char& operator[](int index) const;

    int getSize() const;

    virtual void addition(const Array& other);
    virtual void Show() const;
};

// ==================== CLASS DECIMAL ====================

class Decimal : public Array
{
private:
    int sign;

    void removeZeros();

    static int compareAbs(const Decimal& a, const Decimal& b);

    static vector<unsigned char> addAbs(
        const Decimal& a, const Decimal& b);

    static vector<unsigned char> subtractAbs(
        const Decimal& a, const Decimal& b);

    static Decimal fromDigits(
        const vector<unsigned char>& digits, int resultSign);

public:
    Decimal(const string& number = "0");
    Decimal(const Decimal& other);

    Decimal& operator=(const Decimal& other);

    string toString() const;
    void Show() const override;

    void addition(const Array& other) override;

    Decimal operator-() const;

    Decimal operator+(const Decimal& other) const;
    Decimal operator-(const Decimal& other) const;
    Decimal operator*(const Decimal& other) const;
    Decimal operator/(const Decimal& other) const;
    Decimal operator%(const Decimal& other) const;

    bool operator==(const Decimal& other) const;
    bool operator!=(const Decimal& other) const;
    bool operator<(const Decimal& other) const;
    bool operator>(const Decimal& other) const;
    bool operator<=(const Decimal& other) const;
    bool operator>=(const Decimal& other) const;
};

// ==================== CLASS STRING ====================

class String : public Array
{
public:
    String(int maxLength = 255, const string& text = "");
    String(const String& other);

    string toString() const;
    int length() const;

    void Show() const override;
    void addition(const Array& other) override;

    int find(const string& substring) const;

    void eraseSubstring(const string& substring);

    void insertSubstring(
        int position, const string& substring);

    String operator+(const String& other) const;
};
