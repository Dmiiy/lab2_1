#ifndef LINKEDLISTSEQUENCE_INCLUDED
#define LINKEDLISTSEQUENCE_INCLUDED

#include "LinkedList.h"
#include "Sequence.h"

template<class T>
class LinkedListSequence : public Sequence<T> {
    LinkedList<T> data;  // Односвязный список

    void checkIndex(int index) const {
        if (index < 0 || index >= getLength())
            throw IndexOutOfRange("Index out of range");
    }

public:
    LinkedListSequence(T *items, int count) : data(items, count) {}

    LinkedListSequence() = default;

    explicit LinkedListSequence(const LinkedList<T> &list) : data(list) {}

    T getFirst() const override {
        return data.getFirst();
    }

    T getLast() const override {
        return data.getLast();
    }

    T get(int index) const override {
        return data.get(index);
    }

    T operator[](int i) const {
        return data[i];
    }

    T &operator[](int i) {
        return data[i];
    }

    Sequence<T> *getSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        auto *res = new LinkedListSequence<T>();
        for (int index = startIndex; index <= endIndex; index++) {
            res->append(data.get(index));
        }
        return res;
    }

    int getLength() const override {
        return data.getLength();
    }

    void append(T item) override {
        data.append(item);
    }

    void prepend(T item) override {
        data.prepend(item);
    }

    void insertAt(T item, int index) override {
        data.insertAt(item, index);
    }

    Sequence<T> *concat(Sequence<T> *list) override {
        auto *res = new LinkedListSequence<T>(*this);
        for (int i = 0; i < list->getLength(); i++) {
            res->append(list->get(i));
        }
        return res;
    }

    void removeAt(int index) override {
        data.removeAt(index);
    }

    ~LinkedListSequence() override = default;

    Sequence<T> *map(T (*f)(T)) const override {
        auto *res = new LinkedListSequence<T>();
        for (int i = 0; i < getLength(); i++) {
            res->append(f(data.get(i)));
        }
        return res;
    }

    Sequence<T> *where(bool (*h)(T)) const override {
        auto *res = new LinkedListSequence<T>();
        for (int i = 0; i < getLength(); i++) {
            if (h(data.get(i))) {
                res->append(data.get(i));
            }
        }
        return res;
    }

    T reduce(T (*f)(T, T)) const override {
        T result = data.getFirst();
        for (int i = 1; i < getLength(); i++) {
            result = f(result, data.get(i));
        }
        return result;
    }
};

#endif
