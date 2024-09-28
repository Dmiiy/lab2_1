#ifndef LAB2_1_SHARED_PTR_H
#define LAB2_1_SHARED_PTR_H

#include "Control_Block.h"

template<typename T>
class Shared_ptr {
    template<typename U>
    friend
    class Weak_ptr;

private:
    T *m_ptr;
    Control_Block *cb;

public:
    Shared_ptr(T *ptr = nullptr) noexcept: m_ptr(ptr), cb(new Control_Block) {
        if (m_ptr != nullptr) {
            (*cb)++;
        }
    }

    Shared_ptr(const Shared_ptr<T> &other) : m_ptr(other.m_ptr), cb(other.cb) {
        if (m_ptr != nullptr) {
            (*cb)++;
        }
    }

    unsigned int get_count() {
        return cb->get();
    }

    T *get() {
        return m_ptr;
    }

    const T *get() const {
        return m_ptr;
    }

    T &operator*() {
        if (m_ptr != nullptr) {
            return *m_ptr;
        }
    }

    const T &operator*() const {
        if (m_ptr != nullptr) {
            return *m_ptr;
        }
    }

    T *operator->() {
        if (m_ptr != nullptr) {
            return m_ptr;
        }
    }

    const T *operator->() const {
        if (m_ptr != nullptr) {
            return m_ptr;
        }
    }

    Shared_ptr &operator=(const Shared_ptr &other) {
        if (this != &other) {
            reset();
            delete cb;
            m_ptr = other.m_ptr;
            cb = other.cb;
            if (m_ptr != nullptr) {
                (*cb)++;
            }
        }
        return *this;
    }

    Shared_ptr(Shared_ptr &&other) noexcept : m_ptr(other.m_ptr), cb(other.cb) {
        other.m_ptr = nullptr;
        other.cb = nullptr;
    }

    Shared_ptr &operator=(Shared_ptr &&other) noexcept {
        if (this != &other) {
            reset();
            delete cb;
            m_ptr = other.m_ptr;
            cb = other.cb;
            other.m_ptr = nullptr;
            other.cb = nullptr;
        }
        return *this;
    }

    void reset(T *ptr = nullptr) {
        if (cb) {
            (*cb)--;
            if (cb->get() == 0) {
                delete m_ptr; // освобождаем память только если указатель не nullptr
                if (cb->get_weak_count() == 0) {
                    delete cb;
                }
            }
        }
        m_ptr = ptr;
        cb = new Control_Block;
        if (m_ptr != nullptr) {
            (*cb)++;
        }
    }

    bool operator!=(T *ptr) {
        return m_ptr != ptr;
    }

    const bool operator!=(T *ptr) const {
        return m_ptr != ptr;
    }

    void swap(Shared_ptr &other) {
        T *temp = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = temp;
        Control_Block *temp2 = cb;
        cb = other.cb;
        other.cb = temp2;
    }

    ~Shared_ptr() {
        if (cb) {
            (*cb)--;
            if (cb->get() == 0) {
                delete m_ptr; // освобождение памяти
                if (cb->get_weak_count() == 0) {
                    delete cb;
                }
            }
        }
    }
};

#endif //LAB2_1_SHARED_PTR_H
