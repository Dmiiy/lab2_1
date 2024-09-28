#ifndef LINKEDLIST_INCLUDED
#define LINKEDLIST_INCLUDED

#include <iostream>
#include "Common.h"
#include "C:\Users\dimak\CLionProjects\lab2_1\smrt_ptr\Shared_ptr.h"

template<class T>
class LinkedList {
    struct Node {
        T value;
        Shared_ptr<Node> next;  // Указатель на следующий элемент

        Node(T value, Shared_ptr<Node> next = nullptr) : value(value), next(next) {}
    };

    Shared_ptr<Node> first = nullptr;  // Указатель на первый элемент
    Shared_ptr<Node> last = nullptr;   // Указатель на последний элемент
    int size = 0;

public:
    LinkedList(T *items, int count) {
        for (int i = 0; i < count; i++) {
            append(items[i]);
        }
    }

    LinkedList() = default;

    LinkedList(const LinkedList<T> &list) : size(list.size) {
        Shared_ptr<Node> current = list.first;
        while (current.get()) {
            append(current->value);
            current = current->next;
        }
    }

    ~LinkedList() = default;  // Shared_ptr автоматически очистит память

    T getFirst() const {
        if (!first.get()) throw IndexOutOfRange("List is empty");
        return first->value;
    }

    T getLast() const {
        if (!last.get()) throw IndexOutOfRange("List is empty");
        return last->value;
    }

    T &get(int index) const {
        if (index < 0 || index >= size)
            throw IndexOutOfRange("Index out of range");

        Shared_ptr<Node> current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    T operator[](int i) const {
        return get(i);
    }

    T &operator[](int i) {
        return get(i);
    }

    LinkedList<T> *getSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= size)
            throw IndexOutOfRange("Invalid index range");

        Shared_ptr<Node> current = first;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        }

        auto *subList = new LinkedList<T>();
        for (int i = startIndex; i <= endIndex; i++) {
            subList->append(current->value);
            current = current->next;
        }
        return subList;
    }

    int getLength() const {
        return size;
    }

    void append(T item) {
        auto newNode = Shared_ptr<Node>(new Node(item));
        if (!first.get()) {
            first = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;
        size++;
    }

    void prepend(T item) {
        auto newNode = Shared_ptr<Node>(new Node(item, first));
        if (!first.get()) {
            last = newNode;
        }
        first = newNode;
        size++;
    }

    void insertAt(T item, int index) {
        if (index < 0 || index > size)
            throw IndexOutOfRange("Index out of range");

        if (index == 0) {
            prepend(item);
            return;
        }

        Shared_ptr<Node> current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        auto newNode = Shared_ptr<Node>(new Node(item, current->next));
        current->next = newNode;

        if (index == size) {
            last = newNode;
        }

        size++;
    }

    LinkedList<T> *concat(LinkedList<T> *list) const {
        auto *result = new LinkedList<T>(*this);
        Shared_ptr<Node> current = list->first;
        while (current.get()) {
            result->append(current->value);
            current = current->next;
        }
        return result;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size)
            throw IndexOutOfRange("Index out of range");

        if (index == 0) {
            first = first->next;
            if (!first.get()) {
                last = nullptr;
            }
            size--;
            return;
        }

        Shared_ptr<Node> current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        current->next = current->next->next;

        if (index == size - 1) {
            last = current;
        }

        size--;
    }

//    struct Iterator {
//        Shared_ptr<Node> m_ptr;
//
//        Iterator(Shared_ptr<Node> ptr) : m_ptr(ptr) {}
//
//        T &operator*() const {
//            return m_ptr->value;
//        }
//        const T& get(int index) const {
//            // Ваш текущий код для поиска элемента
//            return m_ptr->value;
//        }
//
//        Iterator &operator++() {
//            m_ptr = m_ptr->next;
//            return *this;
//        }
//
//        bool operator!=(const Iterator &other) const {
//            return m_ptr.get() != other.m_ptr.get();
//        }
//    };
//
//    Iterator begin() const {
//        return Iterator(first);
//    }
//
//    Iterator end() const {
//        return Iterator(nullptr);
//    }
};

#endif
