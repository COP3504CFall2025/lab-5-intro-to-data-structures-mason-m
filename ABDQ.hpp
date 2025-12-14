#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
// Big 5
ABDQ();
explicit ABDQ(std::size_t capacity);
ABDQ(const ABDQ& other);
ABDQ(ABDQ&& other) noexcept;
ABDQ& operator=(const ABDQ& other);
ABDQ& operator=(ABDQ&& other) noexcept;
~ABDQ() override;

// Insertion
void pushFront(const T& item) override;
void pushBack(const T& item) override;

// Deletion
T popFront() override;
T popBack() override;

// Access
const T& front() const override;
const T& back() const override;

// Getters
std::size_t getSize() const noexcept override;
};

// Big 5
template <typename T>
ABDQ<T>::ABDQ() : capacity_(4), size_(0), front_(0), back_(0), data_(new T[capacity_]){}

template <typename T>
ABDQ<T>::ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity_]){}

template <typename T>
ABDQ<T>::ABDQ(const ABDQ<T>& other) : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
    data_ = new T[capacity_];

    for(int i = 0; i < size_; i++){
        data_[i] = other.data_[i];
    }
}

template <typename T>
ABDQ<T>::ABDQ(ABDQ<T>&& other) noexcept : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_), data_(other.data_){
    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
    other.data_ = nullptr;
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& other) {
    if (this == &other){
        return *this;
    }
    delete[] data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    
    data_ = new T[capacity_];

    for (int i = 0; i < size_; i++){
        data_[i] = other.data_[i];
    }

    return *this;
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& other) noexcept {
    if(this == &other){
        return *this;
    }
    delete[] data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    data_ = other.data_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
    other.data_ = nullptr;

    return *this;
}

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
}

// Insertion
template <typename T>
void ABDQ<T>::pushFront(const T& item){
    if(size_ == capacity_){
        capacity_ *= SCALE_FACTOR;
        T* newArray = new T[capacity_];

        for(int i = 0; i < size_; i++){
            newArray[i] = data_[(i + front_) % (capacity_/SCALE_FACTOR)];
        }
        front_ = 0;
        back_ = size_ - 1;
        delete[] data_;
        data_ = newArray;
    }
    if (size_ != 0){
        if(front_ == 0){
            front_ = capacity_-1;
        }
        else{
            front_--;
        }
    }
    data_[front_] = item;
    size_++;
}

template <typename T>
void ABDQ<T>::pushBack(const T& item){
        if(size_ == capacity_){
        capacity_ *= SCALE_FACTOR;
        T* newArray = new T[capacity_];

        for(int i = 0; i < size_; i++){
            newArray[i] = data_[(i + front_) % (capacity_/SCALE_FACTOR)];
        }
        front_ = 0;
        back_ = size_ - 1;
        delete[] data_;
        data_ = newArray;
    }
    if (size_ != 0){
        if (back_ == capacity_-1){
            back_ = 0;
        }
        else {
            back_++;
        }
    }
    data_[back_] = item;
    size_++;
}

// Deletion
template <typename T>
T ABDQ<T>::popFront(){
    T val = data_[front_];

    if(front_ == capacity_-1){
        front_ = 0;
    }
    else{
        front_++;
    }
    size_--;
    if (size_ == 0){
        front_ = 0;
        back_ = 0;
    }
    return val;
}

template <typename T>
T ABDQ<T>::popBack(){
    T val = data_[back_];

    if(back_ == 0){
        back_ = capacity_-1;
    }
    else{
        back_--;
    }
    size_--;
    return val;
}

// Access
template <typename T>
const T& ABDQ<T>::front() const {
    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const{
    return data_[back_];
}

// Getters
template <typename T>
std::size_t ABDQ<T>::getSize() const noexcept{
    return size_;
}