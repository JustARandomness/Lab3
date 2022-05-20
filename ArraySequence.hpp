#include <iostream>
#include <cstring>
#include "DynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T> {
    private:
        DynamicArray<T>* items;
    public:
        ArraySequence(T* items, int count) {
            auto* dynamicArray = new DynamicArray<T> (items, count);
            this->items = dynamicArray;
        }

        explicit ArraySequence() {
            auto* newArray = new DynamicArray<T> ();
            this->items = newArray;
        }

        ArraySequence(const ArraySequence<T>& sequence) {
            auto* newArray = new DynamicArray<T> (sequence.items, sequence.GetLength());
            this->items = newArray;
        }
    public:
        T GetFirst() override {
            return this->items->Get(0);
        }

        T GetLast() override{
            return this->items->Get(items->GetSize() - 1);
        }

        T Get(int index) override{
            return this->items->Get(index);
        }

        Sequence<T>* GetSubSequence(int startIndex, int endIndex) override {
            int size = this->items->GetSize();
            if (endIndex >= startIndex && endIndex >= 0 && endIndex < size && startIndex >= 0 && startIndex < size) {
                auto *newSequence = new ArraySequence();
                int subArraySize = endIndex - startIndex + 1;
                auto *subArray = new DynamicArray<T>(endIndex - startIndex + 1);
                for (int i = 0; i < subArraySize; ++i) {
                    subArray->Set(i, this->items->Get(startIndex + i));
                }
                newSequence->items = subArray;
                return newSequence;
            }
            else {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(IndexOutOfRangeCode);
                errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
                throw errorInfo;
                return nullptr;
            }
        }

        int GetLength() override{
            return this->items->GetSize();
        }
    public:
        void Delete(int index){
            if (index < 0 || index >= this->items->GetSize()) {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(IndexOutOfRangeCode);
                errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
                throw errorInfo;
                return;
            }

            auto* newDynamicArray = new DynamicArray<T> (this->items->GetSize() - 1);

            for (int i = 0; i < index; ++i) {
                newDynamicArray->Set(i, this->items->Get(i));
            }

            for (int i = index; i < this->items->GetSize() - 1; ++i) {
                newDynamicArray->Set(i, this->items->Get(i + 1));
            }

            delete this->items;
            this->items = newDynamicArray;
        }

        void Set(int index, T item) override {
            this->items->Set(index, item);
        }

        void Append(T item) override{
            if (this->items->GetSize() == this->items->GetCapacity()) {
                this->items->Resize(this->items->GetSize() * 2);
                this->items->Set(this->items->GetSize(), item);
                this->items->SetSize(this->items->GetSize() + 1);
            }
            else {
                this->items->Set(this->items->GetSize(), item);
                this->items->SetSize(this->items->GetSize() + 1);
            }
        }

        void Prepend(T item) override {
            this->items->Resize(this->items->GetSize() + 1);
            for (int i = this->items->GetSize() - 1; i > 0; --i) {
                this->items->Set(i, this->items->Get(i - 1));
            }
            this->items->Set(0, item);
        }

        void InsertAt(T item, int index) override {
            this->items->Resize(this->items->GetSize() + 1);
            this->items->SetSize(this->items->GetSize() + 1);
            for (int i = this->items->GetSize() - 1; i > index; --i) {
                this->items->Set(i, this->items->Get(i - 1));
            }
            this->items->Set(index, item);
        }

        Sequence<T>* Concat(Sequence<T>* list) override {
            auto* newArraySequence = new ArraySequence;
            newArraySequence->items = new DynamicArray<T> (this->items->GetSize() + list->GetLength());
            for (int i = 0; i < this->items->GetSize(); ++i) {
                newArraySequence->items->Set(i, this->items->Get(i));
                newArraySequence->items->SetSize(newArraySequence->items->GetSize() + 1);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                newArraySequence->items->Set(i + this->items->GetSize(), list->Get(i));
                newArraySequence->items->SetSize(newArraySequence->items->GetSize() + 1);
            }
            return newArraySequence;
        }

        Sequence<T>* Copy() override {
            auto* newArraySequence = new ArraySequence;
            for (int i = 0; i < this->GetLength(); ++i) {
                newArraySequence->Append(this->Get(i));
            }
        }
};