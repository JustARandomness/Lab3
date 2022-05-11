#include <iostream>
#include <cstring>

template <class T>
void TestConcat (Sequence<T>* First, Sequence<T>* Second, int classType, ErrorInfo* errorInfo) {
    if (classType == 0) {
        int flag = 1;
        LinkedListSequence<T>* newSequence;
        newSequence = dynamic_cast<LinkedListSequence<T>*>(First->Concat(Second, errorInfo));
        if (newSequence->GetLength() == First->GetLength() + Second->GetLength()) {
            for (int i = 0; i < First->GetLength(); ++i) {
                if (newSequence->Get(i, errorInfo) != First->Get(i, errorInfo)) {
                    flag = 0;
                    break;
                }
            }
            for (int i = First->GetLength(); i < newSequence->GetLength(); ++i) {
                if (newSequence->Get(i, errorInfo) != Second->Get(i - First->GetLength(), errorInfo)) {
                    flag = 0;
                    break;
                }
            }
        } else {
            flag = 0;
        }
        if (flag == 1) {
            std::cout << "LinkedList Concat is working properly";
        } else {
            std::cout << "LinkedList Concat is not working properly";
        }
    }
    else {
        int flag = 1;
        auto *newSequence = new ArraySequence<T>();
        newSequence = dynamic_cast<ArraySequence<T>*>(First->Concat(Second, errorInfo));
        if (newSequence->GetLength() == First->GetLength() + Second->GetLength()) {
            for (int i = 0; i < First->GetLength(); ++i) {
                if (newSequence->Get(i, errorInfo) != First->Get(i, errorInfo)) {
                    flag = 0;
                    break;
                }
            }
            for (int i = First->GetLength(); i < newSequence->GetLength(); ++i) {
                if (newSequence->Get(i, errorInfo) != Second->Get(i - First->GetLength(), errorInfo)) {
                    flag = 0;
                    break;
                }
            }
        } else {
            flag = 0;
        }
        if (flag == 1) {
            std::cout << "ArraySequence Concat is working properly";
        } else {
            std::cout << "ArraySequence Concat is not working properly";
        }
    }
}

template <class T>
void TestAppend(const Sequence<T>* testSequence, T item, int classType, ErrorInfo* errorInfo) {
    if (classType == 0) {
        auto* newSequence = new LinkedListSequence<T> (testSequence);
        newSequence->Append(item, errorInfo);
        if (newSequence->Get(newSequence->GetLength()) == item) {
            std :: cout << "Append is working properly";
        }
        else {
            std :: cout << "Append is not working properly";
        }
    }
}