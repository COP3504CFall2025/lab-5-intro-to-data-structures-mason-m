#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;
    LLS(const LLS& other); // copy constructor
    LLS& operator=(const LLS& rhs); // copy assignement
    LLS(LLS&& other) noexcept; // move constructor
    LLS& operator=(LLS&& rhs) noexcept; // move assignement
    ~LLS() noexcept override = default; // destructor

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;

    //output
    void PrintForward() const;
    void PrintReverse() const;
};

template <typename T>
LLS<T>::LLS(const LLS<T>& other) : list(other.list) {} // copy constructor

template <typename T>
LLS<T>& LLS<T>::operator=(const LLS& rhs){
    if (this != &rhs){
        list = rhs.list;
    }
    return *this;
} // copy assignement

template <typename T>
LLS<T>::LLS(LLS<T>&& other) noexcept : list(std::move(other.list)){} // move constructor

template <typename T>
LLS<T>& LLS<T>::operator=(LLS<T>&& rhs) noexcept{
    if (this == &rhs){
        return *this;
    }

    list = LinkedList<T>(std::move(rhs.list));
    return *this;
} // move assignement

template <typename T>
void LLS<T>::push(const T& item) {
    list.addHead(item);
}

template <typename T>
T LLS<T>::pop() {
    T val = list.getHead()->data;

    list.removeHead();

    return val;
}

template <typename T>
T LLS<T>::peek() const {
    return list.getHead()->data;
}

template <typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}

template <typename T>
void LLS<T>::PrintForward() const{
    list.printForward();
}

template <typename T>
void LLS<T>::PrintReverse() const{
    list.printReverse();
}