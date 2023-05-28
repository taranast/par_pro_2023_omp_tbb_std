// Copyright 2023 Mironova Ekaterina
#include "../../../modules/task_3/mironova_e_radix_batcher_tbb/radix_batcher_tbb.h"
#include <tbb/tbb.h>
#include <vector>
#include <cstdint>
#include <limits>
#include <cstring>
#include <algorithm>
#include <utility>

void compexch(double* x, double* y) {
    if (*y < *x) {
        std::swap(*x, *y);
    }
}

std::vector<double> radixSort(std::vector<double> data, int exp) {
    int size = data.size();
    std::vector<double> res(size);
    std::vector<int> counter(256, 0);
    uint64_t n;
    for (int i = 0; i < size; i++) {
        std::memcpy(&n, &data[i], sizeof(n));
        counter[255 & (n >> (8 * exp))]++;
    }
    for (int i = 1; i < 256; i++) {
        counter[i] += counter[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        std::memcpy(&n, &data[i], sizeof(n));
        res[counter[255 & (n >> (8 * exp))] - 1] = data[i];
        counter[255 & (n >> (8 * exp))]--;
    }
    return res;
}

std::vector<double> fullRadixSort(std::vector<double> unsortedData) {
    std::vector<double> negativePart, nonNegativePart;
    for (int i = 0; i < unsortedData.size(); i++) {
        if (unsortedData[i] >= 0) {
            nonNegativePart.push_back(unsortedData[i]);
        } else {
            negativePart.push_back(unsortedData[i]);
        }
    }
    for (int exp = 0; exp < sizeof(double); exp++) {
        negativePart = radixSort(negativePart, exp);
        nonNegativePart = radixSort(nonNegativePart, exp);
    }
    std::vector<double> sortedData(unsortedData.size());
    for (int i = negativePart.size(), j = 0; i > 0; i--, j++) {
        sortedData[j] = negativePart[i-1];
    }
    for (int i = 0, j = negativePart.size(); i < nonNegativePart.size(); i++, j++) {
        sortedData[j] = nonNegativePart[i];
    }
    return sortedData;
}

std::vector<double> batcherMerge(const std::vector<double>& firstPart, const std::vector<double>& secondPart) {
    int size = firstPart.size() + secondPart.size();
    std::vector<double> fullData(size);
    std::vector<double> all(firstPart.begin(), firstPart.end());
    all.insert(all.end(), secondPart.begin(), secondPart.end());
    for (int i = 0, j = 0; i < size - 1; j += 2, i += 2) {
        fullData[i] = all[j];
        fullData[i + 1] = all[j + 1];
    }
    for (int i = 0; i < size; i += 2)
        compexch(&fullData[i], &fullData[i + 1]);
    for (int i = 1; i < size - 1; i += 2)
        compexch(&fullData[i], &fullData[i + 1]);
    std::merge(firstPart.begin(), firstPart.end(), secondPart.begin(), secondPart.end(), fullData.begin());
    int hsize = (secondPart.size() - firstPart.size() + 1) / 2 - 1;
    for (int i = firstPart.size() + 1; i + hsize < secondPart.size(); i++)
        compexch(&fullData[i], &fullData[i + 1]);
    return fullData;
}

struct structForTbb {
    mutable std::vector<double> data;
    structForTbb() = default;
    structForTbb(const structForTbb& s, tbb::split) {}
    void operator()(const tbb::blocked_range<std::vector<double>::iterator>& tmp) {
        data.insert(data.end(), tmp.begin(), tmp.end());
        data = fullRadixSort(data);
    }
    void join(const structForTbb& tmp) {
        data = batcherMerge(tmp.data, data);
    }
};

std::vector<double> radixSortBatcherMergeTbb(const std::vector<double>& data) {
    structForTbb t;
    std::vector<double> dataCopy(data);
    tbb::parallel_reduce(
        tbb::blocked_range<std::vector<double>::iterator>(dataCopy.begin(),
        dataCopy.end()), t);
    return t.data;
}
