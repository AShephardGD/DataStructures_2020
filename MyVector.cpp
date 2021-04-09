#include "MyVector.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

MyVector::MyVector() {
    _size = 0;
    _data = nullptr;
}

MyVector::MyVector(size_t size) {
    if (size > 0) {
        _data = new ValueType[size];
        for (size_t i = 0; i < size; ++i) {
            _data[i] = 0;
        }
    }
    else {
        _data = nullptr;
    }
    _size = size;
}

MyVector::MyVector(const MyVector& other) {
    _size = other.size();
    if (size()) {
        _data = new ValueType[size()];
        for (size_t i = 0; i < size(); ++i) {
            _data[i] = other.at(i);
        }
    }
    else {
        _data = nullptr;
    }
}

MyVector::MyVector(MyVector&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
}



MyVector& MyVector::operator=(const MyVector& other) {
    _size = other.size();
    delete[] _data;
    if (size()) {
        _data = new ValueType[size()];
        for (size_t i = 0; i < size(); ++i) {
            _data[i] = other.at(i);
        }
    }
    else {
        _data = nullptr;
    }
    return *this;
}

MyVector& MyVector::operator=(MyVector&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    delete[] other._data;
    other._size = 0;
    return *this;
}

MyVector::~MyVector() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
}



void MyVector::insert(const ValueType& value, size_t idx) {
    if (idx > size()) {
        throw std::out_of_range("Called insert() - Out of MyVector's range");
    }
    size_t i = 0, newSize = size() + 1;
    ValueType* newVector = new ValueType[size() + 1];
    for (; i < idx; ++i) {
        newVector[i] = at(i);
    }
    newVector[i] = value;
    ++i;
    for (; i < newSize; ++i) {
        newVector[i] = at(i - 1);
    }
    delete[] _data;
    _data = newVector;
    _size = newSize;
}

void MyVector::pushBack(const ValueType& value) {
    insert(value, size());
}

void MyVector::pushFront(const ValueType& value) {
    insert(value, 0);
}



size_t MyVector::size() const{
    return _size;
}

ValueType& MyVector::at(size_t idx) {
    if (idx >= size()) {
        throw std::out_of_range("Called at() - Out of MyVector's range");
    }
    return _data[idx];
}

const ValueType& MyVector::at(size_t idx) const {
    if (idx >= size()) {
        throw std::out_of_range("Called at() Out of MyVector's range");
    }
    return _data[idx];
}

ValueType& MyVector::operator[](const size_t i) {
    return at(i);
}

const ValueType& MyVector::operator[](const size_t i) const {
    return at(i);
}



void MyVector::clear() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
}

void MyVector::erase(size_t i, size_t len) {
    if (i >= size()) {
        throw std::out_of_range("Called erase() - Out of MyString's range");
    }
    if (i + len > size()) {
        len = size() - i;
    }
    ValueType* newData = new ValueType[size() - len];
    size_t j = 0;
    for (; j < i; ++j) {
        newData[j] = at(j);
    }
    j += len;
    for (; j < size(); ++j) {
        newData[j - len] = at(j);
    }
    delete[] _data;
    _data = newData;
    _size = size() - len;
}

void MyVector::popBack() {
    erase(size() - 1, 1);
}



size_t MyVector::find(const ValueType& value, size_t pos) const {
     for (size_t i = pos; i < size(); ++i) {
        if (at(i) == value) {
            return i;
        }
     }
     return -1;
}



void MyVector::print(std::ostream& stream) const {
    size_t end = size() - 1;
    stream << "[";
    if (end != -1) {
        for (size_t i = 0; i < end; ++i) {
            stream << at(i) << ", ";
        }
        stream << at(end);
    }
    stream << "]";
}



std::ostream& operator<<(std::ostream& stream, const MyVector& myVector) {
    myVector.print(stream);
    return stream;
}
