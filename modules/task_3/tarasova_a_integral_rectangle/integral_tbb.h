// Copyright 2023 Tarasova Anastasiya
#ifndef MODULES_TASK_3_TARASOVA_A_INTEGRAL_RECTANGLE_INTEGRAL_TBB_H_
#define MODULES_TASK_3_TARASOVA_A_INTEGRAL_RECTANGLE_INTEGRAL_TBB_H_

#include <vector>

double getParallel(double a1, double b1, double a2, double b2, double a3,
    double b3, double h, const std::function<double(double, double, double)>& fun);
double getSequential(double a1, double b1, double a2, double b2, double a3,
    double b3, double h, const std::function<double(double, double, double)>& fun);

#endif  // MODULES_TASK_3_TARASOVA_A_INTEGRAL_RECTANGLE_INTEGRAL_TBB_H_
