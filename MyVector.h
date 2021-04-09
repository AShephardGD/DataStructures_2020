#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include "IVector.h"

#include <iostream>

class MyVector : public IVector {
public:
    MyVector();
    MyVector(size_t size);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;

    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;

    ~MyVector();

    void pushBack(const ValueType& value) override;
    void pushFront(const ValueType& value) override;
    void insert(const ValueType& value, size_t idx) override;

    size_t size() const override;
    ValueType& at(size_t idx) override;
    const ValueType& at(size_t) const override;
    ValueType& operator[](const size_t i) override;
    const ValueType& operator[](const size_t i) const override;

    void clear() override;
    void erase(size_t i, size_t len = 1) override;
    void popBack() override;

    size_t find(const ValueType& value, size_t pos = 0) const override;

    void print(std::ostream& stream = std::cout) const override;

    friend std::ostream& operator<<(std::ostream& stream, const MyVector& myVector);
};

#endif // MYVECTOR_H_INCLUDED
