#include <cstdlib>
#include <chrono>
#include <complex>

#include "C:\Users\dimak\CLionProjects\lab2_1\smrt_ptr\Weak_ptr.h"
#include "C:\Users\dimak\CLionProjects\lab2_1\smrt_ptr\Unique_ptr.h"
#include "C:\Users\dimak\CLionProjects\lab2_1\sequence\Sequence.h"
#include "C:\Users\dimak\CLionProjects\lab2_1\sequence\LinkedListSequence.h"

#include "lib/googletest/include/gtest/gtest.h"

TEST(Shared_ptr, BasicOperations) {
    Shared_ptr<int> sp(new int(5));
    ASSERT_EQ(*sp, 5);
    ASSERT_EQ(sp.get_count(), 1);
}

TEST(Shared_ptr, CopyConstructor) {
    Shared_ptr<int> sp1(new int(10));
    Shared_ptr<int> sp2(sp1);
    ASSERT_EQ(*sp1, 10);
    ASSERT_EQ(*sp2, 10);
    ASSERT_EQ(sp1.get_count(), 2);
    ASSERT_EQ(sp2.get_count(), 2);
}

TEST(Shared_ptr, AssignmentOperator) {
    Shared_ptr<int> sp1(new int(15));
    Shared_ptr<int> sp2(new int(20));
    sp1 = sp2;
    ASSERT_EQ(*sp1, 20);
    ASSERT_EQ(*sp2, 20);
    ASSERT_EQ(sp1.get_count(), 2);
    ASSERT_EQ(sp2.get_count(), 2);
}

TEST(Shared_ptr, Destructor) {
    Shared_ptr<int> sp1(new int(25));
    {
        Shared_ptr<int> sp2(sp1);
        ASSERT_EQ(*sp1, 25);
        ASSERT_EQ(*sp2, 25);
        ASSERT_EQ(sp1.get_count(), 2);
        ASSERT_EQ(sp2.get_count(), 2);
    }
    ASSERT_EQ(sp1.get_count(), 1);
}

TEST(Shared_ptr, MultipleReferences) {
    Shared_ptr<int> sp1(new int(30));
    Shared_ptr<int> sp2(sp1);
    Shared_ptr<int> sp3(sp1);
    ASSERT_EQ(*sp1, 30);
    ASSERT_EQ(*sp2, 30);
    ASSERT_EQ(*sp3, 30);
    ASSERT_EQ(sp1.get_count(), 3);
    ASSERT_EQ(sp2.get_count(), 3);
    ASSERT_EQ(sp3.get_count(), 3);
    sp2.reset(); // Уменьшаем счетчик ссылок
    ASSERT_EQ(sp1.get_count(), 2);
    ASSERT_EQ(sp3.get_count(), 2);
}

TEST(Shared_ptr, Reset) {
    Shared_ptr<int> sp(new int(35));
    ASSERT_EQ(*sp, 35);
    ASSERT_EQ(sp.get_count(), 1);
    sp.reset();
    ASSERT_EQ(sp.get_count(), 0); // Счетчик ссылок должен быть нулевым
    ASSERT_EQ(sp.get(), nullptr); // `sp` теперь должен быть недействительным
}

TEST(Shared_ptr, MoveConstructor) {
    Shared_ptr<int> sp1(new int(40));
    Shared_ptr<int> sp2(std::move(sp1));
    ASSERT_EQ(*sp2, 40);
    ASSERT_EQ(sp1.get(), nullptr); // `sp1` больше не ссылается на объект
    ASSERT_EQ(sp2.get_count(), 1); // `sp2` теперь владеет объектом
}

TEST(Shared_ptr, MoveAssignmentOperator) {
    Shared_ptr<int> sp1(new int(45));
    Shared_ptr<int> sp2(new int(50));
    sp2 = std::move(sp1);
    ASSERT_EQ(*sp2, 45);
    ASSERT_EQ(sp1.get(), nullptr); // `sp1` больше не ссылается на объект
    ASSERT_EQ(sp2.get_count(), 1); // `sp2` теперь владеет объектом
}

TEST(Shared_ptr, WeakPtr) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp(sp1);
    ASSERT_EQ(sp1.get_count(), 1);
    ASSERT_EQ(wp.use_count(), 1);

    sp1.reset();
    ASSERT_EQ(sp1.get_count(), 0);
    ASSERT_EQ(wp.use_count(), 0);

    ASSERT_EQ(wp.lock().get(), nullptr);
}

TEST(Shared_ptr,Swap) {
    Shared_ptr<int> sp1(new int(60));
    Shared_ptr<int> sp2(new int(70));
    sp1.swap(sp2);
    ASSERT_EQ(*sp1, 70);
    ASSERT_EQ(*sp2, 60);
}

TEST(Unique_ptr, DefaultConstructor) {
    Unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(Unique_ptr, ConstructorWithPointer) {
    Unique_ptr<int> ptr(new int(5));
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, 5);
}

TEST(Unique_ptr, MoveConstructor) {
    Unique_ptr<int> ptr1(new int(10));
    Unique_ptr<int> ptr2(std::move(ptr1));

    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 10);
}

TEST(Unique_ptr, MoveAssignment) {
    Unique_ptr<int> ptr1(new int(20));
    Unique_ptr<int> ptr2;
    ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 20);
}

TEST(Unique_ptr, Reset) {
    Unique_ptr<int> ptr(new int(30));
    ptr.reset(new int(40));

    EXPECT_EQ(*ptr, 40);
}

TEST(Unique_ptr, Release) {
    Unique_ptr<int> ptr(new int(50));
    int* rawPtr = ptr.release();

    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*rawPtr, 50);

    delete rawPtr;
}

TEST(Unique_ptr, Swap) {
    Unique_ptr<int> ptr1(new int(60));
    Unique_ptr<int> ptr2(new int(70));

    ptr1.swap(ptr2);

    EXPECT_EQ(*ptr1, 70);
    EXPECT_EQ(*ptr2, 60);
}

TEST(Unique_ptr, SwapWithRawPointer) {
    Unique_ptr<int> ptr(new int(80));
    int* rawPtr = new int(90);

    ptr.swap(rawPtr);

    EXPECT_EQ(*ptr, 90);

    delete rawPtr;
}

TEST(Weak_ptr, ConstructorFromSharedPtr) {
    Shared_ptr<int> sp1(new int(50));
    Weak_ptr<int> wp(sp1);
    EXPECT_EQ(wp.use_count(), 1);
}

TEST(Weak_ptr, CopyConstructor) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp(sp1);
    Weak_ptr<int> copy(wp);
    EXPECT_EQ(copy.use_count(), 1);
}

TEST(Weak_ptr, MoveConstructor) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp(sp1);
    Weak_ptr<int> moved(std::move(wp));
    EXPECT_EQ(moved.use_count(), 1);
}

TEST(Weak_ptr, LockReturnsSharedPtr) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp(sp1);
    Shared_ptr<int> locked = wp.lock();
    EXPECT_NE(locked.get(), nullptr);
    EXPECT_EQ(*locked.get(), 55);
}

TEST(Weak_ptr, Reset) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp(sp1);
    wp.reset();
    EXPECT_EQ(wp.use_count(), 0);
}

TEST(Weak_ptr, Swap) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp1(sp1);
    Weak_ptr<int> wp2(sp1);

    wp1.swap(wp2);

    EXPECT_EQ(wp1.use_count(), 1);
    EXPECT_EQ(wp2.use_count(), 1);
}

TEST(Weak_ptr, Destructor) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> wp(sp1);
    {
        Weak_ptr<int> wp1(sp1);
        EXPECT_EQ(wp.weak_count(), 2); // Проверяем, что счетчик слабых ссылок увеличился
    }
    EXPECT_EQ(wp.weak_count(), 1); // Проверяем, что счетчик слабых ссылок уменьшился при выходе из области видимости
}
TEST(Weak_ptr, LockReturnsNullptrWhenExpired) {
    Shared_ptr<int> sp1(new int(55));
    Weak_ptr<int> weakPtr(sp1);
    sp1.reset(); // Сбрасываем shared_ptr, чтобы он больше не указывал на объект
    Shared_ptr<int> locked = weakPtr.lock();
    EXPECT_EQ(locked.get(), nullptr);
}

// Тесты для LinkedList
TEST(LinkedList, BasicOperations) {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.prepend(0);

    ASSERT_EQ(list.getFirst(), 0);
    ASSERT_EQ(list.getLast(), 2);
    ASSERT_EQ(list.getLength(), 3);
}

TEST(LinkedList, InsertAt) {
    LinkedList<int> list;
    list.append(1);
    list.append(3);
    list.insertAt(2, 1);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);
}

TEST(LinkedList, RemoveAt) {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.removeAt(1);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.getLength(), 2);
}

TEST(LinkedList, GetSubList) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(items, 5);
    LinkedList<int> *subList = list.getSubList(1, 3);

    ASSERT_EQ(subList->getLength(), 3);
    ASSERT_EQ(subList->get(0), 2);
    ASSERT_EQ(subList->get(2), 4);

    delete subList; // не забываем очистить память
}

TEST(LinkedList, Concat) {
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5};
    LinkedList<int> list1(items1, 3);
    LinkedList<int> list2(items2, 2);

    LinkedList<int> *result = list1.concat(&list2);

    ASSERT_EQ(result->getLength(), 8);
    ASSERT_EQ(result->get(0), 1);
    ASSERT_EQ(result->get(4), 5);

    delete result;
}

// Тесты для LinkedListSequence
TEST(LinkedListSequence, BasicOperations) {
    LinkedListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    seq.prepend(0);

    ASSERT_EQ(seq.getFirst(), 0);
    ASSERT_EQ(seq.getLast(), 2);
    ASSERT_EQ(seq.getLength(), 3);
}

TEST(LinkedListSequence, InsertAt) {
    LinkedListSequence<int> seq;
    seq.append(1);
    seq.append(3);
    seq.insertAt(2, 1);

    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 2);
    ASSERT_EQ(seq.get(2), 3);
}

TEST(LinkedListSequence, RemoveAt) {
    LinkedListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    seq.append(3);
    seq.removeAt(1);

    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 3);
    ASSERT_EQ(seq.getLength(), 2);
}

TEST(LinkedListSequence, GetSubsequence) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);
    Sequence<int> *subSeq = seq.getSubsequence(1, 3);

    ASSERT_EQ(subSeq->getLength(), 3);
    ASSERT_EQ(subSeq->get(0), 2);
    ASSERT_EQ(subSeq->get(2), 4);

    delete subSeq;
}

TEST(LinkedListSequence, Concat) {
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5};
    LinkedListSequence<int> seq1(items1, 3);
    LinkedListSequence<int> seq2(items2, 2);

    Sequence<int> *result = seq1.concat(&seq2);

    ASSERT_EQ(result->getLength(), 8);
    ASSERT_EQ(result->get(0), 1);
    ASSERT_EQ(result->get(4), 5);

    delete result;
}

TEST(LinkedListSequence, Map) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);

    Sequence<int> *mapped = seq.map([](int x) { return x * 2; });

    ASSERT_EQ(mapped->get(0), 2);
    ASSERT_EQ(mapped->get(4), 10);

    delete mapped;
}

TEST(LinkedListSequence, Where) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);

    Sequence<int> *filtered = seq.where([](int x) { return x % 2 == 0; });

    ASSERT_EQ(filtered->getLength(), 2);
    ASSERT_EQ(filtered->get(0), 2);
    ASSERT_EQ(filtered->get(1), 4);

    delete filtered;
}

TEST(LinkedListSequence, Reduce) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedListSequence<int> seq(items, 5);

    int result = seq.reduce([](int a, int b) { return a + b; });

    ASSERT_EQ(result, 15);
}


