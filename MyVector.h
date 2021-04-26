#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <iostream>

// ��������� ��������� capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

// ��� �������� � �������
// ����� ����� ������� �� ������
using ValueType = double;

class MyVector
{
public:
    // ����������� ���������
    class VectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = ValueType;
        using pointer           = ValueType*;
        using reference         = ValueType&;

        VectorIterator(ValueType* ptr, size_t index);

        ValueType& operator*();
        ValueType* operator->();
        VectorIterator& operator++();
        VectorIterator operator++(int notUsed);
        bool operator!=(const VectorIterator& other);
        bool operator==(const VectorIterator& other);
        std::ptrdiff_t operator-(const VectorIterator& other);

        size_t getIndex() const;
    private:
        ValueType* _ptr;
        size_t _index;
    };
    class ConstVectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const ValueType;
        using pointer           = const ValueType*;
        using reference         = const ValueType&;

        ConstVectorIterator(const ValueType* ptr);

        const ValueType& operator*();
        const ValueType* operator->();
        ConstVectorIterator& operator++();
        ConstVectorIterator operator++(int notUsed);
        bool operator!=(const ConstVectorIterator& other);
        bool operator==(const ConstVectorIterator& other);
        std::ptrdiff_t operator-(const ConstVectorIterator& other);
    private:
        const ValueType* _ptr;
    };

    // ��������� ������ ���������� ValueType()
    MyVector(size_t size = 0,
             ResizeStrategy strategy = ResizeStrategy::Multiplicative,
             float coef = 1.5f);
    // ��������� ������ ���������� value
    MyVector(size_t size,
             ValueType value,
             ResizeStrategy strategy = ResizeStrategy::Multiplicative,
             float coef = 1.5f);

    MyVector(const MyVector& copy);
    MyVector& operator=(const MyVector& copy);

    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    size_t capacity() const;
    size_t size() const;
    float loadFactor() const;

    VectorIterator begin();
    ConstVectorIterator begin() const;
    VectorIterator end();
    ConstVectorIterator end() const;

    // ������ � ��������,
    // ������ �������� �� O(1)
    ValueType& operator[](const size_t i);
    const ValueType& operator[](const size_t i) const;

    // �������� � �����,
    // ������ �������� �� amort(O(1))
    void pushBack(const ValueType& value);
    // ��������,
    // ������ �������� �� O(n)
    void insert(size_t i, const ValueType& value);     // ������ ��� ������ ��������
    void insert(size_t i, const MyVector& value);      // ������ ��� �������
    void insert(VectorIterator it, const ValueType& value);  // ������ ��� ������ ��������
    void insert(VectorIterator it, const MyVector& value);   // ������ ��� �������

    // ������� � �����,
    // ������ �������� �� amort(O(1))
    void popBack();
    // �������
    // ������ �������� �� O(n)
    void erase(const size_t i);
    void erase(const size_t i, size_t len);            // ������� len ��������� ������� � i

    // ����� �������,
    // ������ �������� �� O(n)
    // ���� isBegin == true, ����� ������ ������� ��������, ������� value, ����� ����������
    // ���� �������� �������� ���, ������� end
    VectorIterator find(const ValueType& value, bool isBegin = true);

    // ��������������� ������ (������������� ������ capacity)
    void reserve(const size_t capacity);

    // �������� ������
    // ���� ����� ������ ������ ��������, �� ����� �������� ���������� value
    // ���� ������ - �������� ������
    void resize(const size_t size, const ValueType& value = ValueType());

    // ������� �������, ��� ��������� capacity
    void clear();

    void print(std::ostream& stream = std::cout) const;
    friend std::ostream& operator<<(std::ostream& stream, const MyVector& myVector);
private:
    void resizeVector(size_t size);
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    float _resizeCoef;
    ResizeStrategy _strategy;
};

#endif // MYVECTOR_H_INCLUDED
