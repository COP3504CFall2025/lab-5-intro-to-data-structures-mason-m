#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;
    LLQ(const LLQ& other); // copy constructor
    LLQ& operator=(const LLQ& rhs); // copy assignement
    LLQ(LLQ&& other) noexcept; // move constructor
    LLQ& operator=(LLQ&& rhs) noexcept; // move assignement
    ~LLQ() noexcept override = default; // destructor

    // Insertion
    void enqueue(const T& item) override;

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    //printers
    void PrintForward();
    void PrintReverse();

};

template <typename T>
LLQ<T>::LLQ(const LLQ<T>& other) : list(other.list) {} // copy constructor

template <typename T>
LLQ<T>& LLQ<T>::operator=(const LLQ& rhs){
    if (this != &rhs){
        list = rhs.list;
    }
    return *this;
} // copy assignement

template <typename T>
LLQ<T>::LLQ(LLQ<T>&& other) noexcept : list(std::move(other.list)){} // move constructor

template <typename T>
LLQ<T>& LLQ<T>::operator=(LLQ<T>&& rhs) noexcept{
    if (this == &rhs){
        return *this;
    }

    list = LinkedList<T>(std::move(rhs.list));
    return *this;
} // move assignement

template <typename T>
void LLQ<T>::enqueue(const T& item) {
    list.addTail(item);
}

template <typename T>
T LLQ<T>::dequeue() {
    T val = list.getHead()->data;

    list.removeHead();

    return val;
}

template <typename T>
T LLQ<T>::peek() const {
    return list.getHead()->data;
}

template <typename T>
std::size_t LLQ<T>::getSize() const noexcept {
    return list.getCount();
}

template <typename T>
void LLQ<T>::PrintForward(){
    list.printForward();
}

template <typename T>
void LLQ<T>::PrintReverse(){
    list.printReverse();
}
