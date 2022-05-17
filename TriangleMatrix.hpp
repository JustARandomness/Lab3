#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class TriangleMatrix : public SquareMatrix<T> {
    public:
        TriangleMatrix() = default;

        TriangleMatrix(T item, int linesCount, int columnsCount) {  // Заполняет все элементы, стоящие выше главной диагонали введенным числом
            this->rectangleMatrix = new DynamicArray<T>(GetSum(linesCount));
            this->lines = linesCount;
            this->columns = columnsCount;
            this->size = linesCount;
            for (int i = 0; i < linesCount; ++i) {
                this->rectangleMatrix->Set(i, item);
            }
        }

        TriangleMatrix(T* items, int linesCount, int columnsCount) {
            this->rectangleMatrix = new DynamicArray<T>(GetSum(linesCount));
            this->lines = linesCount;
            this->columns = columnsCount;
            this->size = linesCount;
            for (int i = 0; i < this->size; ++i) {
                this->rectangleMatrix->Set(i, items[i]);
            }
        }

        TriangleMatrix(const TriangleMatrix<T>& triangleMatrix) {
            this->rectangleMatrix = new DynamicArray<T>(*triangleMatrix.rectangleMatrix);
            this->size = triangleMatrix.size;
            this->columns = this->size;
            this->lines = this->size;
        }
    public:
        T Get(int lineIndex, int columnIndex) {
            if (lineIndex > 1 && columnIndex <= lineIndex - 1) {
                T item;
                item = 0;
                return item;
            }
            else {
                return this->rectangleMatrix->Get((lineIndex - 1) * this->size + (columnIndex - 1) - (lineIndex - 1));
            }
        }
        void Set(T item, int lineIndex, int columnIndex) {
            if (lineIndex > 1 && columnIndex <= lineIndex - 1) {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(ChangingTriangleMatrixCode);
                errorInfo.CopyErrorMsg(ChangingTriangleMatrixMsg);
                throw errorInfo;
            }
        }
};
