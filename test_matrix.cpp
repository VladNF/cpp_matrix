#include <vector>
#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(Matrix, get_default_value) {
    Matrix<int, -1, 2> m2;
    auto cell2 = m2[42][42];
    ASSERT_EQ(m2[42][42], -1);
    ASSERT_EQ(cell2, -1);
    ASSERT_EQ(m2.size(), 0);

    Matrix<int, -1, 3> m3;
    auto cell3 = m3[42][42][42];
    ASSERT_EQ(cell3, -1);
    ASSERT_EQ(m3[42][42][42], -1);
    ASSERT_EQ(m3.size(), 0);
}

TEST(Matrix, get_set_value) {
    Matrix<int, -1, 2> m2;
    auto cell2 = m2[0][0];
    m2[0][0] = 0;
    ASSERT_EQ(m2[0][0], 0);
    ASSERT_EQ(cell2, 0);
    ASSERT_EQ(m2[42][42], -1);
    ASSERT_EQ(m2.size(), 1);

    Matrix<int, -1, 3> m3;
    auto cell3 = m3[0][0][0];
    m3[0][0][0] = 0;
    ASSERT_EQ(m3[0][0][0], 0);
    ASSERT_EQ(cell3, 0);
    ASSERT_EQ(m3[42][42][42], -1);
    ASSERT_EQ(m3.size(), 1);

    ((m2[100][100] = 314) = 0) = 217;
    ASSERT_EQ(m2[100][100], 217);
}

TEST(Matrix, iterate_over_elements) {
    Matrix<int, 0> m;
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;

    ASSERT_EQ(m.size(), 3);
    for (auto e : m) {
        int v;
        Slice s;
        std::tie(s, v) = e;
        ASSERT_EQ(v, 1);
    }
}