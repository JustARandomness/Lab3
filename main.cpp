#include <iostream>
#include "ErrorInfo.hpp"
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Test.hpp"
#include "MapWhereReduce.hpp"
#include "print.hpp"
#include <iomanip>
#include "Sum.hpp"
#include "RectangleMatrix.hpp"
#include "SquareMatrix.hpp"
#include "TriangleMatrix.hpp"
#include "ComplexNumbers.hpp"

int main() {
//    int n;
//    std :: cin >> n;
//    auto* items = new double [n];
//    for (int i = 0; i < n; ++i) {
//        std :: cout << "items[" << i << "] = ";
//        std :: cin >> items[i];
//    }
//    auto* linkedListSequence = new LinkedListSequence<double> (items, n);
//    linkedListSequence = dynamic_cast<LinkedListSequence<double>*>(map(linkedListSequence, [] (auto x) { return x *= 2;}));
//    PrintSequence(linkedListSequence);
    int  lines, columns;
    std :: cin >> lines;
    std :: cin >> columns;
    auto* items = new double [lines * columns];
//    (ComplexNumber<double>*)malloc(sizeof(ComplexNumber<double>) * lines * columns)
    for (int i = 0; i < lines * columns; ++i) {
        std :: cout << "items[" << i << "] = ";
        std :: cin >> items[i];
    }
    SquareMatrix<double> squareMatrix(items, lines);
    SquareMatrix<double> newSquareMatrix(items, lines);
    squareMatrix = squareMatrix + newSquareMatrix;
    std :: cout << squareMatrix.GetLine(2);
    squareMatrix = (squareMatrix.GetLine(2)) * (squareMatrix.GetColumn(2));
    std :: cout << squareMatrix;
    return 0;
}
