#include "vector_impl.h"

Vector::Vector() {}

Vector::Vector(size_t size) : size_(size), capacity_(size_), arr_(new int [size_]) {
    for (size_t i = 0; i < size_; i++) {
        arr_[i] = 0;
    }
}
Vector::Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(size_), arr_(new int [size_])  {
    for (size_t i = 0; i < size_; i++) {
        arr_[i] = *(list.begin() + i);
    }
}

Vector::Vector(const Vector& rhs) : size_(rhs.size_), capacity_(size_), arr_(new int [size_]) {
    std::copy(rhs.arr_, rhs.arr_ + size_, arr_);
}

Vector& Vector::operator=(const Vector& rhs) {
    if (this == &rhs) {
        return *this;
    }
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    delete [] arr_;
    arr_ = new int [size_];
    std::copy(rhs.arr_, rhs.arr_ + size_, arr_);
    return *this;
}

Vector::~Vector() {
    delete [] arr_;
}

void Vector::Swap(Vector& rhs) {
    std::swap(arr_, rhs.arr_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
}

int& Vector::operator[](size_t index) {
    return arr_[index];
}

const int& Vector::operator[](size_t index) const {
    return arr_[index];
}

int& Vector::At(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Error: index is out of range");
    }
    return arr_[index];
}

const int& Vector::At(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Error: index is out of range");
    }
    return arr_[index];
}

size_t Vector::Size() const {
    return size_;
}

size_t Vector::Capacity() const {
    return capacity_;
}

void Vector::PushBack(int element) {
    if (size_ == capacity_) {
        size_t new_capacity;
        if (capacity_ == 0) {
            new_capacity = 1;
        }
        else {
            new_capacity = capacity_ * 2;
        }
        int* new_arr = new int [new_capacity];
        std::copy(arr_, arr_ + size_, new_arr);
        delete [] arr_;
        arr_ = new_arr;
        capacity_ = new_capacity;
    }
    arr_[size_++] = element;
}
        
void Vector::PopBack() {
    if (size_ == 0) {
        throw std::out_of_range("Error: you cannot delete element from an empty vector");
    }
    size_--;
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        int * new_arr = new int [new_capacity];
        std::copy(arr_, arr_ + size_, new_arr);
        delete [] arr_;
        arr_ = new_arr;
        capacity_ = new_capacity;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    os << "[";
    for (size_t i = 0; i < vector.size_; i++) {
        os << vector.arr_[i];
        if (i + 1 < vector.size_) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}