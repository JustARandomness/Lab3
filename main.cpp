#include <iostream>
#include "ErrorInfo.hpp"
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "Test.hpp"
#include "MapWhereReduce.hpp"
#include "print.hpp"
#include "SquareMatrix.hpp"
#include <iomanip>
#include "RectangleMatrix.hpp"
#include "TriangleMatrix.hpp"

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
    for (int i = 0; i < lines * columns; ++i) {
        std :: cout << "items[" << i << "] = ";
        std :: cin >> items[i];
    }
    RectangleMatrix rectangleMatrix(items, lines, columns);
    for (int i = 0; i < rectangleMatrix.GetLinesCount(); ++i) {
        for (int j = 0; j < rectangleMatrix.GetColumnsCount(); ++j) {
            std :: cout << std :: fixed << std :: setprecision(3) << rectangleMatrix.Get(i + 1, j + 1) << " ";
        }
        std :: cout << "\n";
    }
    std :: cin >> lines;
    std :: cin >> columns;
    for (int i = 0; i < lines * columns; ++i) {
        std :: cout << "items[" << i << "] = ";
        std :: cin >> items[i];
    }
    std :: cout << "Euclidean norm:\n" << rectangleMatrix.EuclideanNorm() << "\n";
    RectangleMatrix<double> newRectangleMatrix(items, lines, columns);
    rectangleMatrix = rectangleMatrix * newRectangleMatrix;
    for (int i = 0; i < rectangleMatrix.GetLinesCount(); ++i) {
        for (int j = 0; j < rectangleMatrix.GetColumnsCount(); ++j) {
            std :: cout << std :: fixed << std :: setprecision(3) << rectangleMatrix.Get(i + 1, j + 1) << " ";
        }
        std :: cout << "\n";
    }
    return 0;
}
