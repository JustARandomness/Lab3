#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class TriangleMatrix : public SquareMatrix<T> {
    public:
        TriangleMatrix() = default;

        TriangleMatrix(T item, int linesCount, int columnsCount) {  // Заполняет все элементы, стоящие выше главной диагонали введенным числом
            this->rectangleMatrix = new ArraySequnce<T>(GetSum(linesCount));
            this->lines = linesCount;
            this->columns = columnsCount;
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    if (i != j) {
                        this->Set(i + 1, j + 1, item);
                    }
                    else {
                        continue;
                    }
                }
            }
        }

        TriangleMatrix(T* items, int linesCount, int columnsCount) {
            this->rectangleMatrix = new ArraySequnce<T>(GetSum(linesCount));
            this->lines = linesCount;
            this->columns = columnsCount;
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    if (i != j) {
                        this->rectangleMatrix = items[(i - 1) * this->columns + (j - 1) - (i - 1)];
                    }
                    else {
                        continue;
                    }
                }
            }
        }
};
