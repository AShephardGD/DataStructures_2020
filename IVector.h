#ifndef IVECTOR_H_INCLUDED
#define IVECTOR_H_INCLUDED

#include <cstdlib>
#include <iostream>

using ValueType = double;

class IVector
{
public:
	virtual void pushBack(const ValueType& value) = 0;
	virtual void pushFront(const ValueType& value) = 0;
	virtual void insert(const ValueType& value, size_t idx) = 0;

	virtual size_t size() const = 0;
	virtual ValueType& at(size_t idx) = 0;
	virtual const ValueType& at(size_t idx) const = 0;
    virtual ValueType& operator[](const size_t i) = 0;
    virtual const ValueType& operator[](const size_t i) const = 0;

	virtual void clear() = 0;
    virtual void erase(size_t i, size_t len = 1) = 0;
    virtual void popBack() = 0;

    virtual size_t find(const ValueType& value, size_t pos = 0) const = 0;

    virtual void print(std::ostream& stream = std::cout) const = 0;

	virtual ~IVector() = default;
protected:
    ValueType* _data;
    size_t _size;
};

#endif // IVECTOR_H_INCLUDED
