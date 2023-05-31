// Copyright 2023 Tarasova Anastasiya
#include <tbb/tbb.h>
#include <vector>
#include "../../../modules/task_3/tarasova_a_integral_rectangle/integral_tbb.h"

class Integral {
 private:
    double h;
    double a1, a2, a3;
    double n1, n2, n3;
    double res;
    const std::function<double(double, double, double)>& fun;

 public:
    explicit Integral(double h, double n1, double n2, double n3, double a1, double a2, double a3,
        const std::function<double(double, double, double)>& _fun) :
        h(h), n1(n1), n2(n2), n3(n3), a1(a1), a2(a2), a3(a3), res(0), fun(_fun) {}

    Integral(const trFunctor& f, tbb::split) :
        h(f.h), n1(f.n1), n2(f.n2), n3(f.n3), a1(f.a1), a2(f.a2), a3(f.a3), res(0), fun(f.fun) {}

    void operator()(const tbb::blocked_range3d<int>& r) {
        int i = r.pages().begin(), i_end = r.pages().end();
        int j = r.rows().begin(), j_end = r.rows().end();
        int k = r.cols().begin(), k_end = r.cols().end();

        for (i = r.pages().begin(); i < i_end; i++)
            for (j = r.rows().begin(); j < j_end; j++)
                for (k = r.cols().begin(); k < k_end; k++) {
                    const double x = a1 + i * h + h / 2;
                    const double y = a2 + j * h + h / 2;
                    const double z = a3 + k * h + h / 2;
                    res += h * h * h * fun(x, y, z);
                }
    }

    void join(const trFunctor& f) {
        res += f.res;
    }

    double result() {
        return res;
    }
};
double getParallel(double a1, double b1, double a2, double b2, double a3,
    double b3, double h, const std::function<double(double, double, double)>& fun) {
    int n1 = static_cast<int>((b1 - a1) / h);
    int n2 = static_cast<int>((b2 - a2) / h);
    int n3 = static_cast<int>((b3 - a3) / h);
    trFunctor ftr(h, n1, n2, n3, a1, a2, a3, fun);
    tbb::parallel_reduce(tbb::blocked_range3d<int>(0, n1, 0, n2, 0, n3), ftr);
    return ftr.result();
}

double getSequential(double a1, double b1, double a2, double b2, double a3,
    double b3, double h, const std::function<double(double, double, double)>& fun) {
    int i, j, k, n1, n2, n3;
    double sum = 0;
    n1 = static_cast<int>((b1 - a1) / h);
    n2 = static_cast<int>((b2 - a2) / h);
    n3 = static_cast<int>((b3 - a3) / h);
    for (i = 0; i < n1; i++)
        for (j = 0; j < n2; j++)
            for (k = 0; k < n3; k++) {
                const double x = a1 + i * h + h / 2;
                const double y = a2 + j * h + h / 2;
                const double z = a3 + k * h + h / 2;
                sum += h * h * h * fun(x1, x2, x3);
            }
    return sum;
}
