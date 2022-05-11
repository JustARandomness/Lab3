#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class SquareMatrix {
    private:
        ArraySequnce<T>* sqMatrix;
        int size = 0;
    public:
        SquareMatrix() = default;

        explicit SquareMatrix(int count) {
            this->size = count;
            this->sqMatrix = new ArraySequnce<T>(count * count);
            for (int i = 0; i < count * count; ++i) {
                this->sqMatrix->Set(i, 0);
            }
            this->sqMatrix->SetSize(4);
        }

        SquareMatrix(T* items, int count) {
            this->size = count;
            this->sqMatrix = new ArraySequnce<T>(items, count * count);
            for (int i = 0; i < count * count; ++i) {
                this->sqMatrix->Set(i, items[i]);
            }
        }

        SquareMatrix(const SquareMatrix& matrix) {
            this->size = matrix.size;
            this->sqMatrix = new ArraySequnce<T>(*matrix.sqMatrix);
        }
    public:
        T Get(int lineSerialNumber, int columnSerialNumber) {
            return this->sqMatrix->Get((lineSerialNumber - 1) * this->size + columnSerialNumber - 1);
        }

        int GetSize() {
            return this->size;
        }

    public:
        void Set(int lineSerialNumber, int columnSerialNumber, T item) {
            this->sqMatrix->Set((lineSerialNumber - 1) * this->size + columnSerialNumber - 1, item);
        }

        double EuclideanNorm() {
            double sum = 0;
            double temp = 0;
            for (int i = 0; i < this->size; ++i) {
                for (int j = 0; j < this->size; ++j) {
                    temp = this->Get(i + 1, j + 1);
                    pow(temp, 2);
                    sum += temp;
                }
            }
            sum = pow(sum, 0.5);
            return sum;
        }

        void MultiplyLineByNumber(int lineSerialNumber, T number) {
            for (int j = 0; j < this->size; ++j) {
                this->Set(lineSerialNumber, j + 1, this->Get(lineSerialNumber, j + 1) * number);
            }
        }

        void MultiplyColumnByNumber(int columnSerialNumber, T number) {
            for (int i = 0; i < this->size; ++i) {
                this->Set(i + 1, columnSerialNumber, this->Get(i + 1, columnSerialNumber) * number);
            }
        }

        void SwapColumns(int firstColumnSerialNumber, int secondColumnSerialNumber) {
            T temp;
            for (int i = 0; i < this->size; ++i) {
                temp = this->Get(i + 1, firstColumnSerialNumber);
                this->Set(i + 1, firstColumnSerialNumber, this->Get(i + 1, secondColumnSerialNumber));
                this->Set(i + 1, firstColumnSerialNumber, temp);
            }
        }

        void SwapLines(int firstLineSerialNumber, int secondLineSerialNumber) {
            T temp;
            for (int j = 0; j < this->size; ++j) {
                temp = this->Get(firstLineSerialNumber, j + 1);
                this->Set(firstLineSerialNumber, j + 1, this->Get(secondLineSerialNumber, j + 1));
                this->Set(secondLineSerialNumber, j + 1, temp);
            }
        }
    public:
        SquareMatrix<T> operator+ (SquareMatrix<T> B) {
            if (this->size == B.size) {
                SquareMatrix<T> resultMatrix(*this);
                for (int i = 0; i < resultMatrix.size; ++i) {
                    for (int j = 0; j < resultMatrix.size; ++j) {
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
            if (this->size == B.size) {
                SquareMatrix<T> resultMatrix(*this);
                for (int i = 0; i < resultMatrix.size; ++i) {
                    for (int j = 0; j < resultMatrix.size; ++j) {
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
            if (this->size == B.size) {
                SquareMatrix<T> resultMatrix(this->size);
                for (int i = 0; i < resultMatrix.size; ++i) {
                    for (int j = 0; j < resultMatrix.size; ++j) {
                        for (int l = 0; l < resultMatrix.size; ++l) {
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
        SquareMatrix<T> operator* (T item) {
            SquareMatrix<T> resultMatrix(*this);
            for (int i = 0; i < resultMatrix.size; ++i) {
                for (int j = 0; j < resultMatrix.size; ++j) {
                    resultMatrix.Set(i + 1, j + 1, resultMatrix.Get(i + 1, j + 1) * item);
                }
            }
            return resultMatrix;
        };

        SquareMatrix<T>& operator= (SquareMatrix<T> B) {
            for (int i = 0; i < this->size; ++i) {
                for (int j = 0; j < this->size; ++j) {
                    this->Set(i + 1, j + 1, B.Get(i + 1, j + 1));
                }
            }
            return *this;
        };

};
