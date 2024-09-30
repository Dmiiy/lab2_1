#ifndef LAB2_1_WEAK_PTR_H
#define LAB2_1_WEAK_PTR_H

#include "Shared_ptr.h"
#include "Control_Block.h"

template<class T>
class Weak_ptr {
private:
    Control_Block *cb = nullptr;
    Shared_ptr<T> *sp = nullptr;

public:
    Weak_ptr(Shared_ptr<T> &sp) : cb(sp.cb), sp(&sp) {
        if (cb != nullptr) {
            cb->weak_plus();
        }
    }

    Weak_ptr() = default;

    Weak_ptr(const Weak_ptr &wp) : cb(wp.cb), sp(wp.sp) {
        if (cb != nullptr) {
            cb->weak_plus();
        }
    }

    Weak_ptr(Weak_ptr &&other) noexcept : cb(other.cb), sp(other.sp) {
        other.cb = nullptr;
        other.sp = nullptr;
    }

    Weak_ptr &operator=(Weak_ptr &&other) noexcept {
        if (this != &other) {
            reset(); // вызов reset для управления состоянием текущего объекта
            cb = other.cb;
            sp = other.sp;
            other.cb = nullptr;
            other.sp = nullptr;
        }
        return *this;
    }

    Weak_ptr &operator=(const Weak_ptr &wp) noexcept {
        if (this != &wp) {
            reset();
            cb = wp.cb;
            sp = wp.sp;
            if (cb != nullptr) {
                cb->weak_plus();
            }
        }
        return *this;
    }

    ~Weak_ptr() {
        reset(); // безопасное освобождение ресурсов
    }

    Shared_ptr<T> lock() const {
        return expired() ? Shared_ptr<T>(nullptr) : Shared_ptr<T>(*sp);
    }

    bool expired() const {
        return cb == nullptr || cb->get() == 0;
    }

    void reset() {
        if (cb != nullptr) {
            cb->weak_minus();
            if (cb->get_weak_count() == 0 && cb->get() == 0) {
                delete cb;
            }
            cb = nullptr; // избегаем dangling pointer
        }
    }

    void swap(Weak_ptr& other) {
        Shared_ptr<T>* temp = sp;
        sp = other.sp;
        other.sp = temp;
        Control_Block* temp2 = cb;
        cb = other.cb;
        other.cb = temp2;
    }

    unsigned int use_count() const {
        return cb ? cb->get() : 0;
    }

    unsigned int weak_count() const {
        return cb ? cb->get_weak_count() : 0;
    }
};


#endif //LAB2_1_WEAK_PTR_H
