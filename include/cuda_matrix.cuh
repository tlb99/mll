#ifndef CUDAMATRIX_CUH
#define CUDAMATRIX_CUH

#include <cuda_runtime.h>

template <class T>
class CUDAMatrix
{
    public:
        // Define the constructors
        CUDAMatrix();
        CUDAMatrix(int nRows, int nCols);
        CUDAMatrix(int nRows, int nCols, const T *inputData);
        CUDAMatrix(const CUDAMatrix<T>& inputMatrix);

        // Define the destructor
        ~CUDAMatrix();

        // Configuration methods
        bool resize(int numRows, int numCols);

        // Element access methods
        T getElement(int numRows, int numCols);
        bool setElement(int numRows, int numCols, T value);
        int getNumRows();
        int getNumCols();

        // Overload the assignment operator
        bool operator== (const CUDAMatrix<T>& rhs);

        // Overload the addition, subtraction, and multiplication operators
        template <class U> friend CUDAMatrix<U> operator+ (const CUDAMatrix<U>& lhs, const CUDAMatrix<U>& rhs);
        template <class U> friend CUDAMatrix<U> operator+ (const U& lhs, const CUDAMatrix<U>& rhs);
        template <class U> friend CUDAMatrix<U> operator+ (const CUDAMatrix<U>& lhs, const U& rhs);

        template <class U> friend CUDAMatrix<U> operator- (const CUDAMatrix<U>& lhs, const CUDAMatrix<U>& rhs);
        template <class U> friend CUDAMatrix<U> operator- (const U& lhs, const CUDAMatrix<U>& rhs);
        template <class U> friend CUDAMatrix<U> operator- (const CUDAMatrix<U>& lhs, const U& rhs);

        template <class U> friend CUDAMatrix<U> operator* (const CUDAMatrix<U>& lhs, const CUDAMatrix<U>& rhs);
        template <class U> friend CUDAMatrix<U> operator* (const U& lhs, const CUDAMatrix<U>& rhs);
        template <class U> friend CUDAMatrix<U> operator* (const CUDAMatrix<U>& lhs, const U& rhs);

    private:
        int sub2Ind(int row, int col) const;
        T *m_matrixData;
        int m_nRows, m_nCols, m_nElements;
};


/* *********************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *********************************************************************************************/

// Default constructor
template <class T>
CUDAMatrix<T>::CUDAMatrix()
{
    m_nRows = 1;
    m_nCols = 1;
    m_nElements = 1;
    cudaMallocManaged(&m_matrixData, m_nElements * sizeof(T));
}

//Construct empty matrix of size nRows x nCols
template <class T>
CUDAMatrix<T>::CUDAMatrix(int nRows, int nCols)
{
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    cudaMallocManaged(&m_matrixData, m_nElements * sizeof(T));

    for (int i = 0; i < m_nElements; i++)
        m_matrixData[i] = 0;
}

// Construct from const linear array
template <class T>
CUDAMatrix<T>::CUDAMatrix(int nRows, int nCols, const T *inputData)
{
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    cudaMallocManaged(&m_matrixData, m_nElements * sizeof(T));
    for (int i = 0; i < m_nElements; i++)
        m_matrixData[i] = inputData[i];
}

// Copy constructor
template <class T>
CUDAMatrix<T>::CUDAMatrix(const CUDAMatrix<T>& inputMatrix)
{
    m_nRows = inputMatrix.m_nRows;
    m_nCols = inputMatrix.m_nCols;
    m_nElements = m_nRows * m_nCols;
    cudaMallocManaged(&m_matrixData, m_nElements * sizeof(T));
    for (int i = 0; i < m_nElements; i++)
        m_matrixData[i] = inputMatrix.m_matrixData[i];
}

// Destructor
template <class T>
CUDAMatrix<T>::~CUDAMatrix()
{
    cudaFree(m_matrixData);
}

/* *********************************************************************************************
CONFIGURATION FUNCTIONS
/* *********************************************************************************************/

// Resize the matrix
template <class T>
bool CUDAMatrix<T>::resize(int numRows, int numCols)
{
    m_nRows = numRows;
    m_nCols = numCols;
    m_nElements = m_nRows * m_nCols;
    if (m_matrixData != nullptr)
        cudaFree(m_matrixData);

    cudaMallocManaged(&m_matrixData, m_nElements * sizeof(T));

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
T CUDAMatrix<T>::getElement(int numRows, int numCols)
{
    int linearIndex = sub2Ind(numRows, numCols);

    if (linearIndex >= 0)
        return m_matrixData[linearIndex];
    else
        return 0;
}

template <class T>
bool CUDAMatrix<T>::setElement(int numRows, int numCols, T elementValue)
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
int CUDAMatrix<T>::getNumRows()
{
    return m_nRows;
}

template <class T>
int CUDAMatrix<T>::getNumCols()
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
CUDAMatrix<T> operator+ (const CUDAMatrix<T>& lhs, const CUDAMatrix<T>& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    if (lhs.m_nRows != rhs.m_nRows || lhs.m_nCols != rhs.m_nCols)
        throw std::invalid_argument("Invalid matrix sizes for addition");

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];

    return resultMatrix;

}

// Scalar + Matrix
template <class T>
CUDAMatrix<T> operator+ (const T& lhs, const CUDAMatrix<T>& rhs)
{
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs + rhs.m_matrixData[i];

    return resultMatrix;
}

// Matrix + Scalar
template <class T>
CUDAMatrix<T> operator+ (const CUDAMatrix<T>& lhs, const T& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] + rhs;

    return resultMatrix;
}

/* *********************************************************************************************
THE - OPERATOR
/* *********************************************************************************************/
// Matrix - Matrix
template <class T>
CUDAMatrix<T> operator- (const CUDAMatrix<T>& lhs, const CUDAMatrix<T>& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    if (lhs.m_nRows != rhs.m_nRows || lhs.m_nCols != rhs.m_nCols)
        throw std::invalid_argument("Invalid matrix sizes for subtraction");

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];

    return resultMatrix;
}

// Scalar - Matrix
template <class T>
CUDAMatrix<T> operator- (const T& lhs, const CUDAMatrix<T>& rhs)
{
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs - rhs.m_matrixData[i];

    return resultMatrix;
}

// Matrix - Scalar
template <class T>
CUDAMatrix<T> operator- (const CUDAMatrix<T>& lhs, const T& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] - rhs;

    return resultMatrix;
}

/* *********************************************************************************************
THE * OPERATOR
/* *********************************************************************************************/
// Scalar * Matrix
template <class T>
CUDAMatrix<T> operator* (const T& lhs, const CUDAMatrix<T>& rhs)
{
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs * rhs.m_matrixData[i];

    return resultMatrix;
}

// Matrix * Scalar
template <class T>
CUDAMatrix<T> operator* (const CUDAMatrix<T>& lhs, const T& rhs)
{
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;

    CUDAMatrix<T> resultMatrix(numRows, numCols);

    for (int i = 0; i < numElements; i++)
        resultMatrix.m_matrixData[i] = lhs.m_matrixData[i] * rhs;

    return resultMatrix;
}

// Matrix * Matrix
template <class T>
CUDAMatrix<T> operator* (const CUDAMatrix<T>& lhs, const CUDAMatrix<T>& rhs)
{
    int l_numRows = lhs.m_nRows;
    int l_numCols = lhs.m_nCols;
    int r_numRows = rhs.m_nRows;
    int r_numCols = rhs.m_nCols;

    if (l_numCols != r_numRows) 
        throw std::invalid_argument("Invalid matrix sizes for multiplication");

    T *result_m_matrixData;
    cudaMallocManaged(&result_m_matrixData, l_numRows * r_numCols * sizeof(T));

    int blockSize = 256;
    int numBlocks = (l_numCols + blockSize - 1) / blockSize;

    matrixMultiplyKernel<<<numBlocks, blockSize>>>(lhs.m_matrixData, rhs.m_matrixData, result_m_matrixData, l_numCols);

    cudaDeviceSynchronize();

    CUDAMatrix<T> resultMatrix(l_numRows, r_numCols, result_m_matrixData);
    cudaFree(result_m_matrixData);

    return resultMatrix;
}

template <class T>
__global__ void matrixMultiplyKernel(T *a, T *b, T *c, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < width && col < width) {
        T value = 0;
        for (int k = 0; k < width; ++k) {
            value += a[row * width + k] * b[k * width + col];
        }
        c[row * width + col] = value;
    }
}


/* *********************************************************************************************
THE == OPERATOR
/* *********************************************************************************************/
template <class T>
bool CUDAMatrix<T>::operator== (const CUDAMatrix<T>& rhs)
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
int CUDAMatrix<T>::sub2Ind(int row, int col) const
{
    if ((row >= 0 && row < this->m_nRows) && (col >= 0 && col < this->m_nCols))
        return (row * this->m_nCols) + col;
    else
        return -1;
}
#endif
