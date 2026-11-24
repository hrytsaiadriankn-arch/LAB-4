
#pragma once
#include <iostream>
#include <memory>

class Pair
{
public:
    virtual std::unique_ptr<Pair> add(const Pair& other) const = 0;
    virtual std::unique_ptr<Pair> sub(const Pair& other) const = 0;
    virtual std::unique_ptr<Pair> mul(const Pair& other) const = 0;
    virtual std::unique_ptr<Pair> div(const Pair& other) const = 0;

    virtual void display() const = 0;

    virtual ~Pair() {}
};
