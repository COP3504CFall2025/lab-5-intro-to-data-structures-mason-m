#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    LLDQ() = default;
    LLDQ(const LLDQ& other); // copy constructor
    LLDQ& operator=(const LLDQ& rhs); // copy assignement
    LLDQ(LLDQ&& other) noexcept; // move constructor
    LLDQ& operator=(LLDQ&& rhs) noexcept; // move assignement
    ~LLDQ() noexcept override = default; // destructor

    // Core Insertion Operations
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override;
    const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    void PrintForward();
    void PrintReverse();
};

template <typename T>
LLDQ<T>::LLDQ(const LLDQ<T>& other) : list(other.list) {} // copy constructor

template <typename T>
LLDQ<T>& LLDQ<T>::operator=(const LLDQ& rhs){
    if (this != &rhs){
        list = rhs.list;
    }
    return *this;
} // copy assignement

template <typename T>
LLDQ<T>::LLDQ(LLDQ<T>&& other) noexcept : list(std::move(other.list)){} // move constructor

template <typename T>
LLDQ<T>& LLDQ<T>::operator=(LLDQ<T>&& rhs) noexcept{
    if (this == &rhs){
        return *this;
    }

    list = LinkedList<T>(std::move(rhs.list));
    return *this;
} // move assignement

template<typename T>
void LLDQ<T>::pushFront(const T& item) {
    list.addHead(item);
}

template <typename T>
void LLDQ<T>::pushBack(const T& item) {
    list.addTail(item);
}

template <typename T>
T LLDQ<T>::popFront() {
    T val = list.getHead()->data;

    list.removeHead();

    return val;
};

template <typename T>
T LLDQ<T>::popBack() {
    T val = list.getTail()->data;

    list.removeTail;

    return val;
}

template <typename T>
const T& LLDQ<T>::front() const{
    return list.getHead()->data;
}

template <typename T>
const T& LLDQ<T>::back() const {
    return list.getTail()->data;
}

template <typename T>
 std::size_t LLDQ<T>::getSize() const noexcept {
    return list.getCount();
 }

template <typename T>
void LLDQ<T>::PrintForward(){
    list.printForward();
}

template <typename T>
void LLDQ<T>::PrintReverse(){
    list.printReverse();
}