// Copyright 2023 Tarasova Anastasiya
#include <iostream>
#include <vector>

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

double integral(double a1, double a2, double a3, double b1, 
    double b2, double b3, double h, double f(double, double, double)) {
    double sum = 0.0, x, y, z;
    int n1, n2, n3;
    n1 = (int)((b1 - a1) / h);
    n2 = (int)((b2 - a2) / h);
    n3 = (int)((b3 - a3) / h);
    std::vector<double> x1(n1), y1(n2), z1(n3);
    for (int i = 0; i < n1; i++)
        x1[i] = a1 + i * h + h / 2;
    for (int i = 0; i < n2; i++)
        y1[i] = a2 + i * h + h / 2;
    for (int i = 0; i < n3; i++)
        z1[i] = a3 + i * h + h / 2;
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            for (int k = 0; k < n3; k++)
                sum += f(x1[i], y1[j], z1[k]) * h * h * h;
    return sum;
}

TEST(Sequential, Test_inegral_1) {
    ASSERT_DOUBLE_EQ(24, integral(0.0, 0.0, 0.0, 
        2.0, 2.0, 2.0, 1.0, f1));
}

TEST(Sequential, Test_inegral_2) {
    ASSERT_DOUBLE_EQ(67.5, integral(0.0, 1.0, 0.0, 
        2.0, 4.0, 3.0, 1.0, f2));
}

TEST(Sequential, Test_inegral_3) {
    ASSERT_DOUBLE_EQ(10.69676228022772, integral(4.0, 2.0, 1.0, 
        6.0, 3.0, 3.0, 1.0, f3));
}

TEST(Sequential, Test_inegral_4) {
    ASSERT_DOUBLE_EQ(126.52164136415277, integral(0.0, 1.0, 2.0, 2.0, 
        3.0, 4.0, 1.0, f4));
}

TEST(Sequential, Test_inegral_5) {
    ASSERT_DOUBLE_EQ(800.5, integral(5.0, 3.0, 7.0, 
        6.0, 7.0, 8.0, 1.0, f5));
}
