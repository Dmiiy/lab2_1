#ifndef LAB2_1_UNIQUE_PTR_H
#define LAB2_1_UNIQUE_PTR_H

template<typename T>
class Unique_ptr {

private:
    T *m_ptr;

public:

    explicit Unique_ptr(T *ptr = nullptr) : m_ptr(ptr) {}

    ~Unique_ptr() {
        delete m_ptr;
    }

    // move constructors
    Unique_ptr(Unique_ptr &&other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    Unique_ptr &operator=(Unique_ptr &&other) {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    Unique_ptr(const Unique_ptr &) = delete;

    Unique_ptr &operator=(const Unique_ptr &) = delete;

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

    T *release() {
        T *ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    void reset(T *ptr = nullptr) {
        delete m_ptr;
        m_ptr = ptr;
    }

    T *get() const {
            return m_ptr;
    }

    void swap(Unique_ptr& other) {
        T* temp = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = temp;
    }

    void swap(T*& other) {
        T* temp = m_ptr;
        m_ptr = other;
        other = temp;
    }

    bool operator!=(T *ptr) {
        return m_ptr != ptr;
    }

    const bool operator!=(T *ptr) const {
        return m_ptr != ptr;
    }

};

#endif //LAB2_1_UNIQUE_PTR_H
