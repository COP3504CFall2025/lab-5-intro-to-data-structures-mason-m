#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node() : next(nullptr), prev(nullptr) {}
		Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	};
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node* getHead();
	const Node* getHead() const;
	Node* getTail();
	const Node* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();
	private:
		// Stores pointers to first and last nodes and count
		Node* head;
		Node* tail;
		unsigned int count;
};

template <typename T>
void LinkedList<T>::addHead(const T& data){
	count++;
	Node* newHead = new Node(data);
	newHead->next = head;
	if (head != nullptr){
		head->prev = newHead;
	}
	else{
		tail = newHead;
	}
	head = newHead;
}

template <typename T>
void LinkedList<T>::addTail(const T& data){
	count++;
	Node* newTail = new Node(data);
	if (tail != nullptr){
		tail->next = newTail;
	}
	else {
		head = newTail;
	}
	newTail->prev = tail;
	tail = newTail;
}

template <typename T>
bool LinkedList<T>::removeHead() {
	if (head != nullptr){
		Node* temp = head;
		head = head->next;
		if (head){
			head->prev = nullptr;
		}
		else{
			tail = nullptr;
		}
		delete temp;
		return true;
		count--;
	}
	return false;
}

template <typename T>
bool LinkedList<T>::removeTail() {
	if (tail != nullptr){
		Node* temp = tail;
		tail = tail->prev;
		if (tail){
			tail->next = nullptr;
		}
		else{
			head = nullptr;
		}
		delete temp;
		return true;
		count--;
	}
	return false;
}
template <typename T>
void LinkedList<T>::Clear(){
	Node* current = head;

	while(current) {
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	count = 0;
}
//Big Five

//Constructor
template <typename T>
LinkedList<T>::LinkedList(){
	head = nullptr;
	tail = nullptr;
	count = 0;
}

//Destructor
template <typename T>
LinkedList<T>::~LinkedList(){
	Node* current = head;

	while(current) {
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	count = 0;
}
//Move Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	if (this == &other){
		return *this;
	}

	this->Clear();

	head = other.head;
	tail = other.tail;
	count = other.size;

	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;

	return *this;
}

//Copy Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs){
	if (this == &rhs){
		return *this;
	}

	this->Clear();

	Node* current = rhs.head;
	while (current){
		addTail(current->data);
		current = current->next;
	}

	count = rhs.count;
	return*this;
}
//Move
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
	count = other.count;
	head = other.head;
	tail = other.tail;

	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}
//Copy
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){
	Node* current = list.head;

	while(current){
		addTail(current->data);
		current = current->next;
	}
	count = list.count;
}
template <typename T>
void LinkedList<T>::printForward() const {
    Node* current = head;
    while(current){
        std::cout << current->data << " ";
		current = current->next;
    }
	std::cout << "" << std::endl;
}

template <typename T>
void LinkedList<T>::printReverse() const {
    Node* current = tail;
    while(current){
        std::cout << current->data << " ";
		current = current->prev;
    }
	std::cout << "" << std::endl;
}
template <typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const{
	int count = 0;
	Node* current = head;
	while(current){
		current = current->next;
		count++;
	}
	return count;
}
template <typename T>
LinkedList<T>::Node* LinkedList<T>::getHead(){
	return head;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getHead() const{
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getTail() {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::getTail() const {
    return tail;
}