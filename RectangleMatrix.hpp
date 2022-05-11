#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class RectangleMatrix {
    private:
        ArraySequnce<T>* rectangleMatrix;
        int lines = 0;
        int columns = 0;
    public:
        RectangleMatrix() {
            this->rectangleMatrix = new ArraySequnce<T>;
        }

        RectangleMatrix(T* items, int linesCount, int columnsCount) {
            this->lines = linesCount;
            this->columns = columnsCount;
            this->rectangleMatrix = new ArraySequnce<T>(items, linesCount * columnsCount);
        }

        RectangleMatrix(int linesCount, int columnsCount) {
            T item;
            item = 0;
            this->lines = linesCount;
            this->columns = columnsCount;
            this->rectangleMatrix = new ArraySequnce<T>(linesCount * columnsCount);
            this->rectangleMatrix->SetSize(linesCount * columnsCount);
            for (int i = 0; i < linesCount * columnsCount; ++i) {
                this->rectangleMatrix->Set(i, item);
            }
            this->rectangleMatrix->SetSize(linesCount * columnsCount);
        }

        RectangleMatrix(const RectangleMatrix& matrix) {
            this->rectangleMatrix = new ArraySequnce<T>(*matrix.rectangleMatrix);
            this->lines = matrix.lines;
            this->columns = matrix.columns;
        }

    public:
        T Get(int lineSerialNumber, int columnSerialNumber) const {
            return this->rectangleMatrix->Get((lineSerialNumber - 1) * this->columns + (columnSerialNumber - 1));
        }

        int GetColumnsCount() {
            return this->columns;
        }

        int GetLinesCount() {
            return this->lines;
        }

        RectangleMatrix GetLine(int lineSerialNumber) {
            T* items = new T [this->columns];
            RectangleMatrix newRectangleMatrix(items, 1, this->columns);
            delete[] items;
            return newRectangleMatrix;
        }

        RectangleMatrix GetColumn(int columnSerialNumber) {
            T* items = new T [this->lines];
            RectangleMatrix newRectangleMatrix(items, this->lines, 1);
            delete[] items;
            return newRectangleMatrix;
        }
    public:
        void Set(int lineSerialNumber, int columnSerialNumber, T item) {
            this->rectangleMatrix->Set((lineSerialNumber - 1) * this->columns + (columnSerialNumber - 1), item);
        }

        double EuclideanNorm() {
            double sum = 0;
            double temp = 0;
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    temp = this->Get(i + 1, j + 1);
                    pow(temp, 2);
                    sum += temp;
                }
            }
            sum = pow(sum, 0.5);
            return sum;
        }

        void MultiplyLineByNumber(int lineSerialNumber, T number) {
            for (int j = 0; j < this->columns; ++j) {
                this->Set(lineSerialNumber, j + 1, this->Get(lineSerialNumber, j + 1) * number);
            }
        }

        void MultiplyColumnByNumber(int columnSerialNumber, T number) {
            for (int i = 0; i < this->lines; ++i) {
                this->Set(i + 1, columnSerialNumber, this->Get(i + 1, columnSerialNumber) * number);
            }
        }

        void SwapColumns(int firstColumnSerialNumber, int secondColumnSerialNumber) {
            T temp;
            for (int i = 0; i < this->lines; ++i) {
                temp = this->Get(i + 1, firstColumnSerialNumber);
                this->Set(i + 1, firstColumnSerialNumber, this->Get(i + 1, secondColumnSerialNumber));
                this->Set(i + 1, firstColumnSerialNumber, temp);
            }
        }

        void SwapLines(int firstLineSerialNumber, int secondLineSerialNumber) {
            T temp;
            for (int j = 0; j < this->columns; ++j) {
                temp = this->Get(firstLineSerialNumber, j + 1);
                this->Set(firstLineSerialNumber, j + 1, this->Get(secondLineSerialNumber, j + 1));
                this->Set(secondLineSerialNumber, j + 1, temp);
            }
        }

    public:
        RectangleMatrix operator+ (const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) + B.Get(i + 1, j + 1));
                }
            }
            return result;
        }

        RectangleMatrix operator- (const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) - B.Get(i + 1, j + 1));
                }
            }
            return result;
        }

        RectangleMatrix& operator= (const RectangleMatrix B) {
            delete this->rectangleMatrix;
            this->lines = B.lines;
            this->columns = B.columns;
            this->rectangleMatrix = new ArraySequnce<T>(*B.rectangleMatrix);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    this->Set(i + 1, j + 1, B.Get(i + 1, j + 1));
                }
            }
            return *this;
        }

        RectangleMatrix operator* (const RectangleMatrix B) {
            RectangleMatrix result(this->lines, B.columns);
            std :: cout << result.lines * result.columns;
            for (int i = 0; i < result.lines; ++i) {
                for (int j = 0; j < result.columns; ++j) {
                    for (int l = 0; l < result.columns; ++l) {
                        result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) + (B.Get(l + 1, j + 1) * this->Get(i + 1, l + 1)));
                    }
                }
            }
            return result;
        }

        RectangleMatrix operator* (T item) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) * item);
                }
            }
            return result;
        }
};