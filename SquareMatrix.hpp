#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class SquareMatrix : public RectangleMatrix<T>{
    public:
        SquareMatrix() = default;

        explicit SquareMatrix(int count) {
            T item;
            item = 0;
            this->lines = count;
            this->columns = count;
            this->rectangleMatrix = new ArraySequnce<T>(count * count);
            for (int i = 0; i < count * count; ++i) {
                this->rectangleMatrix->Set(i, item);
            }
            this->rectangleMatrix->SetSize(4);
        }

        SquareMatrix(T* items, int count) {
            this->lines = count;
            this->columns = count;;
            this->rectangleMatrix = new ArraySequnce<T>(items, count * count);
            for (int i = 0; i < count * count; ++i) {
                this->rectangleMatrix->Set(i, items[i]);
            }
        }

        SquareMatrix(const SquareMatrix& matrix) {
            this->lines = matrix.lines;
            this->columns = matrix.columns;
            this->rectangleMatrix = new ArraySequnce<T>(*matrix.rectangleMatrix);
        }
    public:
        int GetSize() {
            return this->lines;
        }
    public:
        SquareMatrix<T> operator+ (SquareMatrix<T> B) {
            if (this->lines == B.lines && this->columns == B.columns) {
                SquareMatrix<T> resultMatrix(*this);
                for (int i = 0; i < resultMatrix.lines; ++i) {
                    for (int j = 0; j < resultMatrix.columns; ++j) {
                        resultMatrix.Set(i + 1, j + 1, this->Get(i + 1, j + 1) + B.Get(i + 1, j + 1));
                    }
                }
                return resultMatrix;
            }
            else {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(DifferentSizedMatricesCode);
                errorInfo.CopyErrorMsg(DifferentSizedMatricesMsg);
                throw errorInfo;
            }
        };

        SquareMatrix<T> operator- (const SquareMatrix<T> B) {
            if (this->lines == B.lines && this->columns == B.columns) {
                SquareMatrix<T> resultMatrix(*this);
                for (int i = 0; i < resultMatrix.lines; ++i) {
                    for (int j = 0; j < resultMatrix.columns; ++j) {
                        resultMatrix.Set(i + 1, j + 1, this->Get(i + 1, j + 1) - B.Get(i + 1, j + 1));
                    }
                }
                return resultMatrix;
            }
            else {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(DifferentSizedMatricesCode);
                errorInfo.CopyErrorMsg(DifferentSizedMatricesMsg);
                throw errorInfo;
            }
        };

        SquareMatrix<T> operator* (SquareMatrix<T> B) {
            if (this->lines == B.lines && this->columns == B.columns) {
                SquareMatrix<T> resultMatrix(this->lines);
                for (int i = 0; i < resultMatrix.lines; ++i) {
                    for (int j = 0; j < resultMatrix.columns; ++j) {
                        for (int l = 0; l < this->columns; ++l) {
                            resultMatrix.Set(i + 1, j + 1, resultMatrix.Get(i + 1, j + 1) + (B.Get(l + 1, j + 1) * this->Get(i + 1, l + 1)));
                        }
                    }
                }
                return resultMatrix;
            }
            else {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(DifferentSizedMatricesCode);
                errorInfo.CopyErrorMsg(DifferentSizedMatricesMsg);
                throw errorInfo;
            }
        };

        SquareMatrix<T>& operator= (SquareMatrix<T> B) {
            if (this->lines == B.lines) {
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        this->Set(i + 1, j + 1, B.Get(i + 1, j + 1));
                    }
                }
            }
            else {
                delete this->rectangleMatrix;
                this->rectangleMatrix = new ArraySequnce<T>(*B.rectangleMatrix);
                this->lines = B.lines;
                this->columns = B.columns;
            }
            return *this;
        };

    SquareMatrix<T>& operator= (RectangleMatrix<T> B) {
        if (B.isSquareMatrix() && this->lines == B.GetLinesCount()) {
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    this->Set(i + 1, j + 1, B.Get(i + 1, j + 1));
                }
            }
            return *this;
        }
        else if (!B.isSquareMatrix()) {
            ErrorInfo errorInfo;
            errorInfo.SetErrorCode(NotSquareMatrixCode);
            errorInfo.CopyErrorMsg(NotSquareMatrixMsg);
            throw errorInfo;
        }
        else if (B.isSquareMatrix() && this->lines != B.GetLinesCount()) {
            delete this->rectangleMatrix;
            this->rectangleMatrix = new ArraySequnce<T>(B.GetArrayCopy(), B.GetLinesCount() * B.GetColumnsCount());
            this->lines = B.GetLinesCount();
            this->columns = B.GetColumnsCount();
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    this->Set(i + 1, j + 1, B.Get(i + 1, j + 1));
                }
            }
            return *this;
        }
    };

        friend std :: ostream& operator<< (std :: ostream& os, SquareMatrix squareMatrix) {
            for (int i = 0; i < squareMatrix.lines; ++i) {
                for (int j = 0; j < squareMatrix.columns; ++j) {
                    std :: cout << std :: setprecision(3) << squareMatrix.Get(i + 1, j + 1) << " ";
                }
                std :: cout << "\n";
            }
            return os;
        }
};
