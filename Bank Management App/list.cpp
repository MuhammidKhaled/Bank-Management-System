#include "list.h"

template <class T>
ListNode<T>::ListNode() : indirectObject(nullptr), link(nullptr) {}

template <class T>
List<T>::List() : head(nullptr), current(nullptr), count(0) {}

// Query Methods
template <class T>
int List<T>::size() {
	return count;
}

template <class T>
int List<T>::end() {
	return current == nullptr;
}

// Navigation Methods
template <class T>
void List<T>::reset() {
	current = head;
}

template <class T>
void List<T>::next() {
	if (current != nullptr) {
		current = current->link;
	}
}

// Modifiers Members
template <class T>
int List<T>::insert(T& object) {
    ListNode<T>* p = new ListNode<T>;
    if (p != nullptr) {
        p->indirectObject = &object;
        p->link = head;
        head = p;
        count++;
        current = p;
        return 1;
    }
    else {
        return 0;
    }
}

template <class T>
T* List<T>::remove() {
    if (count == 0) {
        return nullptr; 
    }

    T* removedObject; 

    if (head == current) {
        removedObject = head->indirectObject;
        head = head->link;
        delete current;
        current = head; 
    }
    else {
        ListNode<T>* previous = head;
        while (previous->link != current) {
            previous = previous->link;
        }

        removedObject = current->indirectObject;
        previous->link = current->link;
        delete current;
        current = previous->link;
    }

    count--;
    return removedObject;
}


// Retrieving Methods
template <class T>
T* List<T>::retrieve() {
    return current != nullptr ? current->indirectObject : nullptr;
}

template <class T>
T* List<T>::operator[](int i) {
    if (i < 0 || i >= count) {
        return nullptr;
    }
    ListNode<T>* temp = head;
    for (int j = 0; j < i; j++) {
        temp = temp->link;
    }
    return temp->indirectObject;
}

// Destructor
template <class T>
List<T>::~List() {
    ListNode<T>* temp;
    while (head != nullptr) {
        temp = head;
        head = head->link;
        delete temp;
    }
    current = nullptr;
    count = 0;
}

template <class T>
int List<T>::append(T& object) {
    ListNode<T>* newNode = new ListNode<T>;
    if (newNode != nullptr) {
        newNode->indirectObject = &object;
        newNode->link = nullptr;

        if (head == nullptr) {
            head = newNode;
            current = newNode;
        }
        else {
            ListNode<T>* temp = head;
            while (temp->link != nullptr) {
                temp = temp->link;
            }
            temp->link = newNode;
        }
        count++;
        return 1;
    }
    else {
        return 0; 
    }
}

// Copy Constructor
template <class T>
List<T>::List(const List& l) : head(nullptr), current(nullptr), count(0) {
    ListNode<T>* temp = l.head;
    while (temp != nullptr) {
        T* object = temp->indirectObject;
        append(*object);
        temp = temp->link;
    }

    // Handling current
    temp = l.head;
    ListNode<T>* newCurrent = head;
    while (temp != nullptr && temp != l.current) {
        temp = temp->link;
        if (newCurrent != nullptr) {
            newCurrent = newCurrent->link;
        }
        else {
            break;
        }
    }
    current = newCurrent;
}

// Assignment Operator
template <class T>
List<T>& List<T>::operator=(const List& l) {
    if (this != &l) {
        reset();

        ListNode<T>* srcNode = l.head;
        while (srcNode != nullptr) {
            T* newObj = new T(*srcNode->indirectObject);
            append(*newObj);
            srcNode = srcNode->link;
        }

        ListNode<T>* temp = l.head;
        ListNode<T>* newCurrent = head;
        while (temp != nullptr && temp != l.current) {
            temp = temp->link;
            if (newCurrent != nullptr) {
                newCurrent = newCurrent->link;
            }
            else {
                break;
            }
        }
        current = newCurrent;
    }
    return *this;
}