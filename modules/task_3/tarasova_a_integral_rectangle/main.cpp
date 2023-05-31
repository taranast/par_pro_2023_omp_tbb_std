// Copyright 2023 Tarasova Anastasiya
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./integral_tbb.h"

double f1(double x, double y, double z) {
    return x + y + z;
}

double f2(double x, double y, double z) {
    return x * y * z;
}

double f3(double x, double y, double z) {
    return sin(x) * cos(y) + z;
}

double f4(double x, double y, double z) {
    return exp(x) + y * y * z;
}

double f5(double x, double y, double z) {
    return x * x * x + y * y + z;
}

TEST(Parallel_TBB, Test_inegral_1) {
    double (*fun)(double, double, double);
    fun = f1;
    ASSERT_DOUBLE_EQ(getSequential(0.0, 0.0, 0.0,
        2.0, 2.0, 2.0, 1.0, fun), getParallel(0.0, 0.0, 0.0,
            2.0, 2.0, 2.0, 1.0, fun));
}

TEST(Parallel_TBB, Test_inegral_2) {
    double (*fun)(double, double, double);
    fun = f2;
    ASSERT_DOUBLE_EQ(getSequential(0.0, 1.0, 0.0,
        2.0, 4.0, 3.0, 1.0, fun), getParallel(0.0, 1.0, 0.0,
            2.0, 4.0, 3.0, 1.0, fun));
}

TEST(Parallel_TBB, Test_inegral_3) {
    double (*fun)(double, double, double);
    fun = f3;
    ASSERT_DOUBLE_EQ(getSequential(4.0, 2.0, 1.0,
        6.0, 3.0, 3.0, 1.0, fun), getParallel(4.0, 2.0, 1.0,
            6.0, 3.0, 3.0, 1.0, fun));
}

TEST(Parallel_TBB, Test_inegral_4) {
    double (*fun)(double, double, double);
    fun = f4;
    ASSERT_DOUBLE_EQ(getSequential(0.0, 1.0, 2.0, 2.0,
        3.0, 4.0, 1.0, fun), getParallel(0.0, 1.0, 2.0, 2.0,
            3.0, 4.0, 1.0, fun));
}

TEST(Parallel_TBB, Test_inegral_5) {
    double (*fun)(double, double, double);
    fun = f5;
    ASSERT_DOUBLE_EQ(getSequential(5.0, 3.0, 7.0,
        6.0, 7.0, 8.0, 1.0, fun), getParallel(5.0, 3.0, 7.0,
            6.0, 7.0, 8.0, 1.0, fun));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
