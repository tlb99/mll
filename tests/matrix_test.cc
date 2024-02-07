#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(MatrixTest, BasicAssertions) {
    Matrix<int> m(2, 2);
    m.setElement(0, 0, 1);
    m.setElement(0, 1, 2);
    m.setElement(1, 0, 3);
    m.setElement(1, 1, 4);

    EXPECT_EQ(m.getElement(0, 0), 1);
    EXPECT_EQ(m.getElement(0, 1), 2);
    EXPECT_EQ(m.getElement(1, 0), 3);
    EXPECT_EQ(m.getElement(1, 1), 4);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    Matrix<int> m3 = m1 + m2;

    EXPECT_EQ(m3.getElement(0, 0), 6);
    EXPECT_EQ(m3.getElement(0, 1), 8);
    EXPECT_EQ(m3.getElement(1, 0), 10);
    EXPECT_EQ(m3.getElement(1, 1), 12);
}


TEST(MatrixTest, MatrixAdditionWithInvalidSizes) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 1);
    m2.setElement(0, 0, 5);
    m2.setElement(1, 0, 6);

    try {
        Matrix<int> m3 = m1 + m2;
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid matrix sizes for addition"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(MatrixTest, MatrixScalarAddition) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    Matrix<int> m2 = m1 + s1;

    EXPECT_EQ(m2.getElement(0, 0), 6);
    EXPECT_EQ(m2.getElement(0, 1), 7);
    EXPECT_EQ(m2.getElement(1, 0), 8);
    EXPECT_EQ(m2.getElement(1, 1), 9);
}

TEST(MatrixTest, ScalarMatrixAddition) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    Matrix<int> m2 = s1 + m1;

    EXPECT_EQ(m2.getElement(0, 0), 6);
    EXPECT_EQ(m2.getElement(0, 1), 7);
    EXPECT_EQ(m2.getElement(1, 0), 8);
    EXPECT_EQ(m2.getElement(1, 1), 9);
}

TEST(MatrixTest, MatrixSubtraction) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    Matrix<int> m3 = m1 - m2;

    EXPECT_EQ(m3.getElement(0, 0), -4);
    EXPECT_EQ(m3.getElement(0, 1), -4);
    EXPECT_EQ(m3.getElement(1, 0), -4);
    EXPECT_EQ(m3.getElement(1, 1), -4);
}

TEST(MatrixTest, MatrixSubtractionWithInvalidSizes) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 1);
    m2.setElement(0, 0, 5);
    m2.setElement(1, 0, 6);

    try {
        Matrix<int> m3 = m1 - m2;
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid matrix sizes for subtraction"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(MatrixTest, MatrixScalarSubtraction) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    Matrix<int> m2 = m1 - s1;

    EXPECT_EQ(m2.getElement(0, 0), -4);
    EXPECT_EQ(m2.getElement(0, 1), -3);
    EXPECT_EQ(m2.getElement(1, 0), -2);
    EXPECT_EQ(m2.getElement(1, 1), -1);
}

TEST(MatrixTest, ScalarMatrixSubtraction) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    Matrix<int> m2 = s1 - m1;

    EXPECT_EQ(m2.getElement(0, 0), 4);
    EXPECT_EQ(m2.getElement(0, 1), 3);
    EXPECT_EQ(m2.getElement(1, 0), 2);
    EXPECT_EQ(m2.getElement(1, 1), 1);
}

TEST(MatrixTest, MatrixMultiplication) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    Matrix<int> m3 = m1 * m2;

    EXPECT_EQ(m3.getElement(0, 0), 19);
    EXPECT_EQ(m3.getElement(0, 1), 22);
    EXPECT_EQ(m3.getElement(1, 0), 43);
    EXPECT_EQ(m3.getElement(1, 1), 50);
}

TEST(MatrixTest, MatrixScalarMultiplication) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    Matrix<int> m2 = m1 * s1;

    EXPECT_EQ(m2.getElement(0, 0), 5);
    EXPECT_EQ(m2.getElement(0, 1), 10);
    EXPECT_EQ(m2.getElement(1, 0), 15);
    EXPECT_EQ(m2.getElement(1, 1), 20);
}

TEST(MatrixTest, ScalarMatrixMultiplication) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    int s1 = 5;

    Matrix<int> m2 = s1 * m1;

    EXPECT_EQ(m2.getElement(0, 0), 5);
    EXPECT_EQ(m2.getElement(0, 1), 10);
    EXPECT_EQ(m2.getElement(1, 0), 15);
    EXPECT_EQ(m2.getElement(1, 1), 20);
}

TEST(MatrixTest, MatrixMultiplicationWithInvalidSizes) {
    Matrix<int> m1(1, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);

    Matrix<int> m2(1, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);

    try {
        Matrix<int> m3 = m1 * m2;
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid matrix sizes for multiplication"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(MatrixTest, MatrixEquality) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 2);
    m2.setElement(0, 0, 1);
    m2.setElement(0, 1, 2);
    m2.setElement(1, 0, 3);
    m2.setElement(1, 1, 4);

    bool eq = (m1 == m2);

    EXPECT_EQ(eq, true);
}

TEST(MatrixTest, MatrixInequality) {
    Matrix<int> m1(2, 2);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(1, 0, 3);
    m1.setElement(1, 1, 4);

    Matrix<int> m2(2, 2);
    m2.setElement(0, 0, 5);
    m2.setElement(0, 1, 6);
    m2.setElement(1, 0, 7);
    m2.setElement(1, 1, 8);

    bool eq = (m1 == m2);

    EXPECT_EQ(eq, false);
}