#include <iostream>
#include <cstring>

template <class T>
class DynamicArray {
private :
    T* array;
    int size = 0;
    int capacity = 0;
public:
    DynamicArray(T* items, int count) {
        this->array = new T [count];
        this->size = count;
        this->capacity = count;
        memcpy(this->array, items, sizeof(T) * count);
    }

    DynamicArray() = default;

    explicit DynamicArray(int count) {
        auto* newArray = new T [count];
        this->array = newArray;
        this->capacity = count;
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        auto* new_array = new T [dynamicArray.capacity];
        this->array = new_array;
        this->size = dynamicArray.size;
        this->capacity = dynamicArray.capacity;
        for (int i = 0; i < this->size; ++i) {
            this->array[i] = dynamicArray.array[i];
        }
    }
public:
    T Get(int index) {
        if (!this->array) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NoListCreatedCode);
            errorInfo.CopyErrorMsg(NoListCreatedMsg);
            throw errorInfo;
        }

        if (index < 0 || index >= this->size) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NoListCreatedCode);
            errorInfo.CopyErrorMsg(NoListCreatedMsg);
            throw errorInfo;
        }

        return this->array[index];
    }
    int GetSize() {
        return this->size;
    }

    int GetCapacity() {
        return this->capacity;
    }
public:
    void Set(int index, T value) {
        if (!this->array) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NoListCreatedCode);
            errorInfo.CopyErrorMsg(NoListCreatedMsg);
            throw errorInfo;
            return;
        }

        if (index < 0 || (index >= this->size && this->size == this->capacity)) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(IndexOutOfRangeCode);
            errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
            throw errorInfo;
            return;
        }

        this->array[index] = value;
    }

    void Resize(int NewSize) {
        T* buffer_array = new T [this->size];
        memcpy(buffer_array, this->array, sizeof(T) * this->size);
        int oldSize = this->size;
        delete[] this->array;
        if (oldSize < NewSize) {
            this->array = new T [NewSize];
            this->capacity = NewSize;
            this->size = oldSize;
            for (int i = 0; i < oldSize; ++i) {
                this->array[i] = buffer_array[i];
            }
        }
        else {
            this->array = new T[NewSize];
            this->size = NewSize;
            this->capacity = NewSize;
            for (int i = 0; i < NewSize; ++i) {
                this->array[i] = buffer_array[i];
            }
        }
        delete[] buffer_array;
    }

    void SetSize(int NewSize) {
        this->size = NewSize;
    }
};