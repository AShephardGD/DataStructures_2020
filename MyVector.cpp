#include "MyVector.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

MyVector::VectorIterator::VectorIterator(ValueType* ptr, size_t index) : _ptr(ptr), _index(index) {}

ValueType& MyVector::VectorIterator::operator*() {
    return *(_ptr);
}

ValueType* MyVector::VectorIterator::operator->() {
    return _ptr;
}

MyVector::VectorIterator& MyVector::VectorIterator::operator++() {
    ++_ptr;
    ++_index;
    return *(this);
}

MyVector::VectorIterator MyVector::VectorIterator::operator++(int notUsed) {
    VectorIterator temp = *this;
    ++(*this);
    return temp;
}

bool MyVector::VectorIterator::operator!=(const MyVector::VectorIterator& other) {
    return _ptr != other._ptr;
}

bool MyVector::VectorIterator::operator==(const MyVector::VectorIterator& other) {
    return _ptr == other._ptr;
}

std::ptrdiff_t MyVector::VectorIterator::operator-(const MyVector::VectorIterator& other) {
    return _ptr - other._ptr;
}

size_t MyVector::VectorIterator::getIndex() const {
    return _index;
}



MyVector::ConstVectorIterator::ConstVectorIterator(const ValueType* ptr) : _ptr(ptr) {}

const ValueType& MyVector::ConstVectorIterator::operator*() {
    return *(_ptr);
}

const ValueType* MyVector::ConstVectorIterator::operator->() {
    return _ptr;
}

MyVector::ConstVectorIterator& MyVector::ConstVectorIterator::operator++() {
    ++_ptr;
    return *(this);
}

MyVector::ConstVectorIterator MyVector::ConstVectorIterator::operator++(int notUsed) {
    ConstVectorIterator temp = *(this);
    ++(*this);
    return temp;
}

bool MyVector::ConstVectorIterator::operator!=(const MyVector::ConstVectorIterator& other) {
    return _ptr != other._ptr;
}

bool MyVector::ConstVectorIterator::operator==(const MyVector::ConstVectorIterator& other) {
    return _ptr == other._ptr;
}

std::ptrdiff_t MyVector::ConstVectorIterator::operator-(const MyVector::ConstVectorIterator& other) {
    return _ptr - other._ptr;
}


MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    if (_size) {
        _data = new ValueType[size];
    }
    else {
        _data = nullptr;
    }
    _resizeCoef = coef;
    _strategy = strategy;
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    if (_size) {
        _data = new ValueType[size];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = value;
        }
    }
    else {
        _data = nullptr;
    }
    _resizeCoef = coef;
    _strategy = strategy;
}

MyVector::MyVector(const MyVector& copy) {
    _size = copy.size();
    _capacity = copy.size();
    if (size()) {
        _data = new ValueType[size()];
        for (size_t i = 0; i < size(); ++i) {
            _data[i] = copy[i];
        }
    }
    else {
        _data = nullptr;
    }
    _resizeCoef = copy._resizeCoef;
    _strategy = copy._strategy;
}

MyVector::MyVector(MyVector&& other) noexcept {
    _data = nullptr;
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    std::swap(_capacity, other._capacity);
    std::swap(_resizeCoef, other._resizeCoef);
    std::swap(_strategy, other._strategy);
}



MyVector& MyVector::operator=(const MyVector& other) {
    _size = other.size();
    delete[] _data;
    resizeVector(size());
    if (size()) {
        for (size_t i = 0; i < size(); ++i) {
            _data[i] = other[i];
        }
    }
    return *this;
}

MyVector& MyVector::operator=(MyVector&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    std::swap(_capacity, other._capacity);
    std::swap(_resizeCoef, other._resizeCoef);
    std::swap(_strategy, other._strategy);
    delete[] other._data;
    other._size = 0;
    other._capacity = 0;
    return *this;
}

MyVector::~MyVector() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}



size_t MyVector::capacity() const {
    return _capacity;
}

size_t MyVector::size() const{
    return _size;
}

float MyVector::loadFactor() const {
    if (capacity()) {
        return ((float) size()) / ((float) capacity());
    }
    else {
        return 1;
    }
}



MyVector::VectorIterator MyVector::begin() {
    return MyVector::VectorIterator(_data, 0);
}

MyVector::ConstVectorIterator MyVector::begin() const {
    return MyVector::ConstVectorIterator(_data);
}

MyVector::VectorIterator MyVector::end() {
    return MyVector::VectorIterator(_data + size() - 1, size() - 1);
}

MyVector::ConstVectorIterator MyVector::end() const {
    return MyVector::ConstVectorIterator(_data + size() - 1);
}



ValueType& MyVector::operator[](const size_t i) {
    if (i >= size()) {
        throw std::out_of_range("Called [] - Out of MyVector's range");
    }
    return _data[i];
}

const ValueType& MyVector::operator[](const size_t i) const {
    if (i >= size()) {
        throw std::out_of_range("Called [] - Out of MyVector's range");
    }
    return _data[i];
}



void MyVector::pushBack(const ValueType& value) {
    insert(size(), value);
}

void MyVector::insert(size_t i, const ValueType& value) {
    if (i > size()) {
        i = size();
    }
    size_t newSize = size() + 1;
    resizeVector(newSize);
    for (size_t idx = size(); idx > i; --idx) {
        _data[idx] = _data[idx - 1];
    }
    _data[i] = value;
    _size = newSize;
}

void MyVector::insert(size_t i, const MyVector& value) {
    if (i > size()) {
        i = size();
    }
    size_t newSize = size() + value.size(), forEnd = i + value.size() - 1;
    resizeVector(newSize);
    for (size_t idx = newSize - 1; idx > forEnd; --idx) {
        _data[idx] = _data[idx - value.size()];
    }
    for (size_t idx = i; idx <= forEnd; ++idx) {
        _data[idx] = value[idx - i];
    }
    _size = newSize;
}

void MyVector::insert(MyVector::VectorIterator it, const ValueType& value) {
    insert(it.getIndex(), value);
}

void MyVector::insert(MyVector::VectorIterator it, const MyVector& value) {
    insert(it.getIndex(), value);
}



void MyVector::popBack() {
    --_size;
}

void MyVector::erase(const size_t i) {
    erase(i, 1);
}

void MyVector::erase(const size_t i,  size_t len) {
    if (i >= size()) {
        throw std::out_of_range("Called erase() - Out of MyString's range");
    }
    if (i + len > size()) {
        len = size() - i;
    }
    _size = size() - len;
    for (size_t index = i; index < _size; ++index) {
        _data[index] = _data[index + len];
    }
}



MyVector::VectorIterator MyVector::find(const ValueType& value, bool isBegin) {
    VectorIterator it(_data, 0);
    if (isBegin) {
        for (; it != end(); ++it) {
            if (*it == value) {
                return it;
            }
        }
        return it;
    }
    else {
        VectorIterator res(_data, 0);
        for (; it != end(); ++it) {
            if (*it == value) {
                res = it;
            }
        }
        if (it == end()) {
            return it;
        }
        return res;
    }
}



void MyVector::reserve(const size_t capacity) {
    if (!capacity) {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = capacity;
        return;
    }
    ValueType* newData = new ValueType[capacity];
    _capacity = capacity;
    if (capacity < size()) {
        for (size_t i = 0; i < capacity; ++i) {
            newData[i] = _data[i];
        }
        _size = capacity;
    }
    else {
        for (size_t i = 0; i < size(); ++i) {
            newData[i] = _data[i];
        }
    }
    delete[] _data;
    _data = newData;
}

void MyVector::resize(const size_t size, const ValueType& value) {
    if (size > _size) {
        resizeVector(size);
        for (size_t i = _size; i < size; ++i) {
            _data[i] = value;
        }
    }
    _size = size;
}

void MyVector::clear() {
    _size = 0;
}



void MyVector::print(std::ostream& stream) const {
    ConstVectorIterator it(_data);
    stream << "[";
    if (size()) {
        for (; it != end(); ++it) {
            stream << *it << ", ";
        }
        stream << *it;
    }
    stream << "]";
}



std::ostream& operator<<(std::ostream& stream, const MyVector& myVector) {
    myVector.print(stream);
    return stream;
}



void MyVector::resizeVector(size_t size) {
    if (size > capacity()) {
        switch (_strategy) {
            case ResizeStrategy::Additive:
                _capacity += _resizeCoef;
                break;
            case ResizeStrategy::Multiplicative:
                if (_capacity <= 1) {
                    _capacity += 5 * _resizeCoef;
                    break;
                }
                _capacity *= _resizeCoef;
                break;
        }
        ValueType* newData = new ValueType[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
        resizeVector(size);
    }
}
