#include "LinkedList.hpp"
#include <iostream>
#include <cstring>

template <class T>
class LinkedListSequence : public Sequence<T> {
private:
    LinkedList<T>* linkedList;
public:
    LinkedListSequence(T* items, int count) {
        auto* list = new LinkedList<T> (items, count);
        this->linkedList = list;
    }

    LinkedListSequence() {
        auto* list = new LinkedList<T> ();
        this->linkedList = list;
    }

    explicit LinkedListSequence(const LinkedList<T>& sequence) {
        auto* newList = new LinkedList<T> (sequence);
        this->linkedList = newList;
    }
public:
    T GetFirst() override {
        return this->linkedList->GetFirst()->GetData();
    }

    T GetLast() override{
        return this->linkedList->GetLast()->GetData();
    }

    T Get(int index) override {
        return (this->linkedList->Get(index))->GetData();
    }

    Sequence<T>* GetSubSequence(int startIndex, int endIndex) {
        auto* newListSequence = new LinkedListSequence;
        newListSequence->linkedList = this->linkedList->GetSubList(startIndex, endIndex);
        return newListSequence;
    }

    int GetLength() override {
        return this->linkedList->GetLength();
    }
public:
    void Delete (int index) override{
        this->linkedList->Delete(index);
    }

    void Set (int index, T item) override{
        (this->linkedList->Get(index))->SetData(item);
    }

    void Append(T item) override {
        this->linkedList->Append(item);
    }

    void Prepend(T item) override{
        this->linkedList->Prepend(item);
    }

    void InsertAt(T item, int index) override {
        this->linkedList->InsertAt(item, index);
    }
    Sequence<T>* Concat(Sequence<T>* list) override {
        auto* newListSequence = new LinkedListSequence;
        int size = this->linkedList->GetLength();
        for (int i = 0; i < size; ++i) {
            newListSequence->linkedList->Append(this->linkedList->Get(i)->GetData());
        }
        size = list->GetLength();
        for (int i = 0; i < size; ++i) {
            newListSequence->linkedList->Append(list->Get(i));
        }
        return newListSequence;
    }

    Sequence<T>* Copy() override {
        auto* newListSequence = new LinkedListSequence;
        for (int i = 0; i < this->GetLength(); ++i) {
            newListSequence->Append(this->Get(i));
        }
        return newListSequence;
    }
};