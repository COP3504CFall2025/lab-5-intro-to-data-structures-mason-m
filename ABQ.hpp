#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

};

//Constuctor
template <typename T>
ABQ<T>::ABQ()
    : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}

//Parameterizer Constructor
template <typename T>
ABQ<T>::ABQ(const size_t capacity)
    : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

//Copy Assignement Operator
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs){
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
ABQ<T>::ABQ(ABQ&& other) noexcept{
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;

    other.array_ = nullptr;
    other.capacity_ = 0;
    other.curr_size_ = 0;
}

// Move Assignement Operator
template <typename T>
ABQ<T>& ABQ<T>::operator=(ABQ<T>&& rhs) noexcept {
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
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
    curr_size_ = 0;
    capacity_ = 0;
}

template <typename T>
[[nodiscard]] size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}

template <typename T>
[[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template <typename T>
[[nodiscard]] T* ABQ<T>::getData() const noexcept {
    return array_;
}

template <typename T>
void ABQ<T>::enqueue(const T& data)  {
    if (curr_size_ == capacity_){
        capacity_ *= scale_factor_;
        
        T* old = new T[capacity_];

        for(int i = 0; i < curr_size_; i++){
            old[i] = array_[i];
        }

        delete[] array_;
        array_ = old;
    }
    array_[curr_size_] = data;
    curr_size_++;
}

template <typename T>
T ABQ<T>::dequeue() {
    T val = array_[0];

    for (int i = 1; i < curr_size_; i++){
        array_[i-1] = array_[i];
    }
    curr_size_--;

    return val;
}

template <typename T>
T ABQ<T>::peek() const {
    return array_[0];
}