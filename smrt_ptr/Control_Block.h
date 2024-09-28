#ifndef LAB2_1_CONTROL_BLOCK_H
#define LAB2_1_CONTROL_BLOCK_H

class Control_Block{
private:
    unsigned int ref_count{};
    unsigned weak_count{};
public:
    Control_Block() : ref_count(0), weak_count(0){}

    Control_Block(const Control_Block&) = delete;
    Control_Block& operator=(const Control_Block&) = delete;

    ~Control_Block(){};

    void reset()
    {
        ref_count = 0;
    }

    unsigned int get()
    {
        return ref_count;
    }

    void operator++() // post increment
    {
        ref_count++;
    }
    void operator++(int) // pre increment
    {
        ref_count++;
    }


    void operator--()
    {
        ref_count--;
    }
    void operator--(int)
    {
        ref_count--;
    }

    unsigned int get_weak_count()
    {
        return weak_count;
    }
    void weak_minus(){
        weak_count--;
    }

    void weak_plus(){
        weak_count++;
    }
};


#endif //LAB2_1_CONTROL_BLOCK_H
