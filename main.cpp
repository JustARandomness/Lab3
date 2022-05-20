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
    int n;
    std :: cin >> n;
    auto* items = new double [GetSum(n)];
    for (int i = 0; i < GetSum(n); ++i) {
        std :: cout << "items[" << i << "] = ";
        std :: cin >> items[i];
    }
    TriangleMatrix<double> triangleMatrix(items, n);
    std :: cout << triangleMatrix;
    return 0;
}
