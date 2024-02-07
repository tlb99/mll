#ifndef MATRIX_HPP
#define MATRIX_HPP

template <class T>
class Matrix
{
    public:
        // Define the constructors
        Matrix();
        Matrix(int nRows, int nCols);
        Matrix(int nRows, int nCols, const T *inputData);
        Matrix(const Matrix<T>& inputMatrix);

        // Define the destructor
        ~Matrix();

        // Configuration methods
        bool resize(int numRows, int numCols);

        // Element access methods
        T getElement(int numRows, int numCols);
        bool setElement(int numRows, int numCols, T value);
        int getNumRows();
        int getNumCols();

        // Overload the assignment operator
        bool operator== (const Matrix<T>& rhs);

        // Overload the addition, subtraction, and multiplication operators
        template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator+ (const U& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const U& rhs);

        template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator- (const U& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const U& rhs);

        template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator* (const U& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const U& rhs);

    private:
        int sub2Ind(int row, int col) const;
    
    private:
        T *m_matrixData;
        int m_nRows, m_nCols, m_nElements;
};


/* *********************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *********************************************************************************************/

// Default constructor
template <class T>
Matrix<T>::Matrix()
{
    m_nRows = 1;
    m_nCols = 1;
    m_nElements = 1;
    m_matrixData = new T[m_nElements];
    m_matrixData[0] = 0;
}

// Construct empty matrix of size nRows x nCols
template <class T>
Matrix<T>::Matrix(int nRows, int nCols)
{
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i = 0; i < m_nElements; i++)
        m_matrixData[i] = 0;
}

// Construct from const linear array
template <class T>
Matrix<T>::Matrix(int nRows, int nCols, const T *inputData)
{
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i = 0; i < m_nElements; i++)
        m_matrixData[i] = inputData[i];
}

// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T>& inputMatrix)
{
    m_nRows = inputMatrix.m_nRows;
    m_nCols = inputMatrix.m_nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i = 0; i < m_nElements; i++)
        m_matrixData[i] = inputMatrix.m_matrixData[i];
}

// Destructor
template <class T>
Matrix<T>::~Matrix()
{
    if (m_matrixData != nullptr)
        delete[] m_matrixData;
}

/* *********************************************************************************************
CONFIGURATION FUNCTIONS
/* *********************************************************************************************/

// Resize the matrix
template <class T>
bool Matrix<T>::resize(int numRows, int numCols)
{
    m_nRows = numRows;
    m_nCols = numCols;
    m_nElements = m_nRows * m_nCols;
    if (m_matrixData != nullptr)
        delete[] m_matrixData;

    m_matrixData = new T[m_nElements];

    if (m_matrixData != nullptr) {
        for (int i = 0; i < m_nElements; i++)
            m_matrixData[i] = 0;
        return true;
    }
    else
        return false;
}

/* *********************************************************************************************
ELEMENT ACCESS FUNCTIONS
/* *********************************************************************************************/
template <class T>
T Matrix<T>::getElement(int numRows, int numCols)
{
    int linearIndex = sub2Ind(numRows, numCols);

    if (linearIndex >= 0)
        return m_matrixData[linearIndex];
    else
        return 0;
}

template <class T>
bool Matrix<T>::setElement(int numRows, int numCols, T elementValue)
{
    int linearIndex = sub2Ind(numRows, numCols);

    if (linearIndex >= 0) {
        m_matrixData[linearIndex] = elementValue;
        return true;
    }
    else
        return false;
}

template <class T>
int Matrix<T>::getNumRows()
{
    return m_nRows;
}

template <class T>
int Matrix<T>::getNumCols()
{
    return m_nCols;
}

/* *********************************************************************************************
OVERLOADED OPERATOR FUNCTIONS
/* *********************************************************************************************/

/* *********************************************************************************************
THE + OPERATOR
/* *********************************************************************************************/

// Matrix + Matrix
template <class T>
Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    if (lhs.m_nRows != rhs.m_nRows || lhs.m_nCols != rhs.m_nCols)
        throw std::invalid_argument("Invalid matrix sizes for addition");

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];

    return resultMatrix;

}

// Scalar + Matrix
template <class T>
Matrix<T> operator+ (const T& lhs, const Matrix<T>& rhs)
{
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs + rhs.m_matrixData[i];

    return resultMatrix;
}

// Matrix + Scalar
template <class T>
Matrix<T> operator+ (const Matrix<T>& lhs, const T& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] + rhs;

    return resultMatrix;
}

/* *********************************************************************************************
THE - OPERATOR
/* *********************************************************************************************/
// Matrix - Matrix
template <class T>
Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    if (lhs.m_nRows != rhs.m_nRows || lhs.m_nCols != rhs.m_nCols)
        throw std::invalid_argument("Invalid matrix sizes for subtraction");

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];

    return resultMatrix;
}

// Scalar - Matrix
template <class T>
Matrix<T> operator- (const T& lhs, const Matrix<T>& rhs)
{
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs - rhs.m_matrixData[i];

    return resultMatrix;
}

// Matrix - Scalar
template <class T>
Matrix<T> operator- (const Matrix<T>& lhs, const T& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] - rhs;

    return resultMatrix;
}

/* *********************************************************************************************
THE * OPERATOR
/* *********************************************************************************************/
// Scalar * Matrix
template <class T>
Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs)
{
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs * rhs.m_matrixData[i];

    return resultMatrix;
}

// Matrix * Scalar
template <class T>
Matrix<T> operator* (const Matrix<T>& lhs, const T& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    Matrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] * rhs;

    return resultMatrix;
}

// Matrix * Matrix
template <class T>
Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    int l_numRows = lhs.m_nRows;
    int l_numCols = lhs.m_nCols;
    int r_numRows = rhs.m_nRows;
    int r_numCols = rhs.m_nCols;

    if (l_numCols != r_numRows) 
        throw std::invalid_argument("Invalid matrix sizes for multiplication");

    Matrix<T> resultMatrix(l_numRows, r_numCols);

    for (int i = 0; i < l_numRows; i++) {
        for (int j = 0; j < r_numCols; j++) {
            T sum = 0;
            for (int k = 0; k < l_numCols; k++) {
                sum += lhs.m_matrixData[lhs.sub2Ind(i, k)] * rhs.m_matrixData[rhs.sub2Ind(k, j)];
            }
            resultMatrix.m_matrixData[resultMatrix.sub2Ind(i, j)] = sum;
        }
    }

    return resultMatrix;
}

/* *********************************************************************************************
THE == OPERATOR
/* *********************************************************************************************/
template <class T>
bool Matrix<T>::operator== (const Matrix<T>& rhs)
{
    if (m_nRows != rhs.m_nRows || m_nCols != rhs.m_nCols)
        return false;

    for (int i = 0; i < m_nElements; i++) {
        if (m_matrixData[i] != rhs.m_matrixData[i])
            return false;
    }

    return true;
}
/* *********************************************************************************************
PRIVATE FUNCTIONS
/* *********************************************************************************************/
template <class T>
int Matrix<T>::sub2Ind(int row, int col) const
{
    if ((row >= 0 && row < this->m_nRows) && (col >= 0 && col < this->m_nCols))
        return (row * this->m_nCols) + col;
    else
        return -1;
}
#endif
