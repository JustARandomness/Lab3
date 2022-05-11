#include <iostream>
#include <cstring>

template <class T>
class LinkedList {
private:
    class LinkedListNode {
    private:
        T data;
        LinkedListNode* pPrev;
        LinkedListNode* pNext;
    public:
        T GetData() {
            return this->data;
        }

        void SetData(T item) {
            this->data = item;
        }

        LinkedListNode* GetNext() {
            return this->pNext;
        }

        void SetNext(LinkedListNode* element) {
            this->pNext = element;
        };

        LinkedListNode* GetPrev() {
            return this->pPrev;
        }

        void SetPrev(LinkedListNode* element) {
            this->pPrev = (LinkedListNode*)element;
        };
    };

    LinkedListNode* first;

    LinkedListNode* last;
public:
    LinkedList(T* items, int count) {
        auto* prev = new LinkedListNode;
        this->first = prev;
        prev->SetPrev(nullptr);
        prev->SetData(items[0]);
        for (int i = 1; i < count; ++i) {
            auto* next = new LinkedListNode;

            next->SetPrev(prev);
            prev->SetNext(next);
            next->SetData(items[i]);

            prev = next;
            this->last = next;
            next->SetNext(nullptr);
        }
    }

    LinkedList() = default;

    LinkedList(const LinkedList<T>& list) {
        auto* prev_element = new LinkedListNode;
        LinkedListNode* element = list.first;
        int count = list.GetLength();

        this->first = prev_element;
        prev_element->SetData(element->GetData());
        element = element->GetNext();
        for (int i = 1; i < count; ++i) {
            auto *next_element = new LinkedListNode;

            prev_element->SetNext(next_element);
            next_element->SetPrev(prev_element);
            next_element->SetData(element->GetData());

            prev_element = prev_element->GetNext();
            element = element->GetNext();
            this->last = next_element;
            next_element->SetNext(nullptr);
        }
    };
public:
    int GetLength() const{
        LinkedListNode* element = this->first;

        int size = 1;
        while(element->GetNext() != nullptr) {
            ++size;
            element = element->GetNext();
        }

        return size;
    }
    LinkedListNode* GetFirst() {
        if (!this) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NoListCreatedCode);
            errorInfo.CopyErrorMsg(NoListCreatedMsg);
            throw errorInfo;
            return nullptr;
        }

        return this->first;
    }

    LinkedListNode* GetLast() {
        if (!this) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NoListCreatedCode);
            errorInfo.CopyErrorMsg(NoListCreatedMsg);
            throw errorInfo;
            return nullptr;
        }

        return this->last;
    }

    LinkedListNode* Get(int index) {
        if (index >= 0 && index < this->GetLength()) {
            LinkedListNode* element = this->first;
            int counter = 0;
            while (counter != index) {
                element = element->GetNext();
                ++counter;
            }
            return element;
        }
        else {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(IndexOutOfRangeCode);
            errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
            throw errorInfo;
            return nullptr;
        }
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= this->GetLength() || endIndex < 0 || endIndex >= this->GetLength()) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(IndexOutOfRangeCode);
            errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
            throw errorInfo;
            return nullptr;
        }

        LinkedListNode* element = this->first;
        int counter = 0;
        T* items = new T [endIndex - startIndex + 1];

        while (counter != startIndex) {
            element = element->GetNext();
            ++counter;
        }

        for (int i = startIndex; i <= endIndex; ++i) {
            items[i - startIndex] = element->GetData();
            element = element->GetNext();
        }

        auto* subList = new LinkedList(items, endIndex - startIndex + 1);
        delete [] items;
        return subList;
    }
public:
    void Delete (int index) {
        if (index < 0 || index >= this->GetLength()) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(IndexOutOfRangeCode);
            errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
            throw errorInfo;
            return;
        }

        LinkedListNode* element = this->Get(index);
        LinkedListNode* nextElement = element->GetNext();
        LinkedListNode* prevElement = element->GetPrev();

        int length = this->GetLength();
        if (length == 1) {
            delete element;
            this->first = nullptr;
            this->last = nullptr;
        }
        else {
            if (index == 0) {
                delete element;
                this->first = nextElement;
                nextElement->SetPrev(nullptr);
            }
            else if (index == length - 1) {
                delete element;
                this->last = prevElement;
                prevElement->SetNext(nullptr);
            }
            else {
                delete element;
                prevElement->SetNext(nextElement);
                nextElement->SetPrev(prevElement);
            }
        }
    }

    void Append(T item) {
        auto* new_last = new LinkedListNode;
        auto* old_last = new LinkedListNode;

        new_last->SetData(item);
        new_last->SetPrev(this->last);
        new_last->SetNext(nullptr);

        old_last = new_last->GetPrev();
        if (old_last != nullptr) {
            old_last->SetNext(new_last);
        }
        else {
            this->first = new_last;
        }

        this->last = new_last;
    }

    void Prepend(T item) {
        auto* new_element = new LinkedListNode;

        new_element->SetData(item);
        new_element->SetPrev(nullptr);
        new_element->SetNext(this->first);
        if (this->first != nullptr) {
            this->first->SetPrev(new_element);
        }
        else {
            this->last = new_element;
        }
        this->first = new_element;
    }

    void InsertAt(T item, int index) {
        if (!this) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NoListCreatedCode);
            errorInfo.CopyErrorMsg(NoListCreatedMsg);
            throw errorInfo;
            return;
        }

        if (index < 0 || index >= this->GetLength()) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(IndexOutOfRangeCode);
            errorInfo.CopyErrorMsg(IndexOutOfRangeMsg);
            throw errorInfo;
            return;
        }

        LinkedListNode* nextElement = this->first;
        int counter = 0;
        while (counter != index) {
            nextElement = nextElement->GetNext();
            ++counter;
        }

        LinkedListNode* prevElement = nextElement->GetPrev();
        auto* newElement = new LinkedListNode;

        newElement->SetData(item);
        newElement->SetNext(nextElement);
        newElement->SetPrev(prevElement);

        nextElement->SetPrev(newElement);
        prevElement->SetNext(newElement);
    }

    LinkedList<T>* Concat(LinkedList<T>* list) {
        auto* new_list = new LinkedList<T> (*this);
        auto* prev_element = new LinkedListNode;
        LinkedListNode* element = this->first;
        prev_element->SetData(element->GetData());
        new_list->first = prev_element;
        element = element->GetNext();
        int count = this->GetLength();
        for (int i = 1; i < count; ++i) {
            auto *next_element = new LinkedListNode;

            prev_element->SetNext(next_element);
            next_element->SetPrev(prev_element);
            next_element->SetData(element->GetData());

            prev_element = prev_element->GetNext();
            element = element->GetNext();
            new_list->last = next_element;
            next_element->SetNext(nullptr);
        }

        count = list->GetLength();
        element = list->first;

        for (int i = 0; i < count; ++i) {
            auto* next_element = new LinkedListNode;

            prev_element->SetNext(next_element);
            next_element->SetPrev(prev_element);
            next_element->SetData(element->GetData());

            prev_element = prev_element->GetNext();
            element = element->GetNext();
            new_list->last = next_element;
            next_element->SetNext(nullptr);
        }
        return new_list;
    }
};