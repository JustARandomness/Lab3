#include <iostream>
#include <cstring>

template <class T, typename Function>
Sequence<T>* map (Sequence<T>* sequence, Function function) {
    Sequence<T>* newSequence = sequence->Copy();
    for (int i = 0; i < sequence->GetLength(); ++i) {
        newSequence->Set(i, function(newSequence->Get(i)));
    }
    return newSequence;
}

template <class T, typename Function>
Sequence<T>* where(Sequence<T>* sequence, Function function) {
    Sequence<T>* newSequence = sequence->Copy();
    int i = 0;
    while (i < newSequence->GetLength()) {
        if (!function(newSequence->Get(i))) {
            newSequence->Delete(i);
        }
        else {
            ++i;
        }
    }
    return newSequence;
}