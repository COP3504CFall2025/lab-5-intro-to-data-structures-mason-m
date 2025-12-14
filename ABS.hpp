#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

//Constuctor
template <typename T>
ABS<T>::ABS()
    : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}

//Parameterizer Constructor
template <typename T>
ABS<T>::ABS(const size_t capacity)
    : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

//Copy Assignement Operator
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs){
    if (this = &rhs){
        return *this;
    }

    delete[] array_;

    capacity_ = rhs.capacity_;
    curr_size_ = rhs.capacity_;
    array_ = new T[capacity_];

    for(int i = 0; i < curr_size_; i++){
        array_[i] = rhs.array_[i];
    }

    return *this;
}

// Move
template <typename T>
ABS<T>::ABS(ABS&& other) noexcept{
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;

    other.array_ = nullptr;
    other.capacity_ = 0;
    other.curr_size_ = 0;
}

// Move Assignement Operator
template <typename T>
ABS<T>& ABS<T>::operator=(ABS<T>&& rhs) noexcept {
    if(this = &rhs){
        return *this;
    }

    delete[] array_;

    curr_size_ = rhs.curr_size_;
    capacity_ = rhs.capacity_;
    array_ = rhs.array_;

    rhs.array_ = nullptr;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
}

// Destructor
template <typename T>
ABS<T>::~ABS() noexcept {
    delete[] array_;
    curr_size_ = 0;
    capacity_ = 0;
}
template <typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

template <typename T>
[[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template <typename T>
[[nodiscard]] T* ABS<T>::getData() const noexcept {
    return array_;
}

template <typename T>
void ABS<T>::push(const T& data) {
    if (capacity_ == curr_size_){
        std::size_t newCapacity_ = capacity_ * scale_factor_;
        T* newArray = new T[newCapacity_];

        for(int i = 0; i < curr_size_; i++){
            newArray[i] = array_[i];
        }
        delete[] array_;    

        array_ = newArray;
        capacity_ = newCapacity_;
    }
    array_[curr_size_] = data;
    curr_size_++;
}

template <typename T>
T ABS<T>::peek() const {
    return array_[curr_size_-1];
}

template <typename T>
T ABS<T>::pop() {
    curr_size_--;
    return array_[curr_size_];
}