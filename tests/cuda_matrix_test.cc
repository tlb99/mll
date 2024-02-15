#include <gtest/gtest.h>
#include "cuda_matrix.cuh"

TEST(CUDAMatrixTest, BasicAssertions) {
    CUDAMatrix<int> m(2, 2);
    m.setElement(0, 0, 1);
    m.setElement(0, 1, 2);
    m.setElement(1, 0, 3);
    m.setElement(1, 1, 4);

    EXPECT_EQ(m.getElement(0, 0), 1);
    EXPECT_EQ(m.getElement(0, 1), 2);
    EXPECT_EQ(m.getElement(1, 0), 3);
    EXPECT_EQ(m.getElement(1, 1), 4);
}

TEST(CUDAMatrixTest, MatrixAddition) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    CUDAMatrix<int> m3 = m1 + m2;

    EXPECT_EQ(m3.getElement(0, 0), 6);
    EXPECT_EQ(m3.getElement(0, 1), 8);
    EXPECT_EQ(m3.getElement(1, 0), 10);
    EXPECT_EQ(m3.getElement(1, 1), 12);
}

TEST(CUDAMatrixTest, MatrixAdditionWithInvalidSizes) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 1);
    m2.setElement(0, 0, 5);
    m2.setElement(1, 0, 6);

    try {
        CUDAMatrix<int> m3 = m1 + m2;
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid matrix sizes for addition"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(CUDAMatrixTest, MatrixScalarAddition) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    CUDAMatrix<int> m2 = m1 + s1;

    EXPECT_EQ(m2.getElement(0, 0), 6);
    EXPECT_EQ(m2.getElement(0, 1), 7);
    EXPECT_EQ(m2.getElement(1, 0), 8);
    EXPECT_EQ(m2.getElement(1, 1), 9);
}

TEST(CUDAMatrixTest, ScalarMatrixAddition) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    CUDAMatrix<int> m2 = s1 + m1;

    EXPECT_EQ(m2.getElement(0, 0), 6);
    EXPECT_EQ(m2.getElement(0, 1), 7);
    EXPECT_EQ(m2.getElement(1, 0), 8);
    EXPECT_EQ(m2.getElement(1, 1), 9);
}

TEST(CUDAMatrixTest, MatrixSubtraction) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    CUDAMatrix<int> m3 = m1 - m2;

    EXPECT_EQ(m3.getElement(0, 0), -4);
    EXPECT_EQ(m3.getElement(0, 1), -4);
    EXPECT_EQ(m3.getElement(1, 0), -4);
    EXPECT_EQ(m3.getElement(1, 1), -4);
}

TEST(CUDAMatrixTest, MatrixSubtractionWithInvalidSizes) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 1);
    m2.setElement(0, 0, 5);
    m2.setElement(1, 0, 6);

    try {
        CUDAMatrix<int> m3 = m1 - m2;
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid matrix sizes for subtraction"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(CUDAMatrixTest, MatrixScalarSubtraction) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    CUDAMatrix<int> m2 = m1 - s1;

    EXPECT_EQ(m2.getElement(0, 0), -4);
    EXPECT_EQ(m2.getElement(0, 1), -3);
    EXPECT_EQ(m2.getElement(1, 0), -2);
    EXPECT_EQ(m2.getElement(1, 1), -1);
}

TEST(CUDAMatrixTest, ScalarMatrixSubtraction) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    CUDAMatrix<int> m2 = s1 - m1;

    EXPECT_EQ(m2.getElement(0, 0), 4);
    EXPECT_EQ(m2.getElement(0, 1), 3);
    EXPECT_EQ(m2.getElement(1, 0), 2);
    EXPECT_EQ(m2.getElement(1, 1), 1);
}

TEST(CUDAMatrixTest, MatrixMultiplication) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    CUDAMatrix<int> m3 = m1 * m2;

    EXPECT_EQ(m3.getElement(0, 0), 19);
    EXPECT_EQ(m3.getElement(0, 1), 22);
    EXPECT_EQ(m3.getElement(1, 0), 43);
    EXPECT_EQ(m3.getElement(1, 1), 50);
}

TEST(CUDAMatrixTest, MatrixScalarMultiplication) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    CUDAMatrix<int> m2 = m1 * s1;

    EXPECT_EQ(m2.getElement(0, 0), 5);
    EXPECT_EQ(m2.getElement(0, 1), 10);
    EXPECT_EQ(m2.getElement(1, 0), 15);
    EXPECT_EQ(m2.getElement(1, 1), 20);
}

TEST(CUDAMatrixTest, ScalarMatrixMultiplication) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    CUDAMatrix<int> m2 = s1 * m1;

    EXPECT_EQ(m2.getElement(0, 0), 5);
    EXPECT_EQ(m2.getElement(0, 1), 10);
    EXPECT_EQ(m2.getElement(1, 0), 15);
    EXPECT_EQ(m2.getElement(1, 1), 20);
}

TEST(CUDAMatrixTest, MatrixMultiplicationWithInvalidSizes) {
    CUDAMatrix<int> m1(1, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);

    CUDAMatrix<int> m2(1, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);

    try {
        CUDAMatrix<int> m3 = m1 * m2;
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid matrix sizes for multiplication"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(CUDAMatrixTest, MatrixEquality) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 2);
    m2.setElement(0, 0, 1);
    m2.setElement(0, 1, 2);
    m2.setElement(1, 0, 3);
    m2.setElement(1, 1, 4);

    bool eq = (m1 == m2);

    EXPECT_EQ(eq, true);
}

TEST(CUDAMatrixTest, MatrixInequality) {
    CUDAMatrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    CUDAMatrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    bool eq = (m1 == m2);

    EXPECT_EQ(eq, false);
}