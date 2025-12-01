#pragma once
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iostream>

class Vector {
    private:
        size_t size_ = 0;
        size_t capacity_ = 0;
        int* arr_ = nullptr;
    public:
        Vector();
        Vector(size_t);
        Vector(std::initializer_list<int>);
        Vector(const Vector&);
        Vector& operator= (const Vector&);
        ~Vector();
        void Swap(Vector&);
        int& operator[](size_t);
        const int& operator[](size_t) const;
        int& At(size_t);
        const int& At(size_t) const;
        size_t Size() const;
        size_t Capacity() const;
        void PushBack(int);
        void PopBack();
        void Clear();
        void Reserve(size_t);
        friend std::ostream& operator<<(std::ostream& os, const Vector& vector);
};