#include "snapshot_predictor.hpp"
#include <pybind11/embed.h>          
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

namespace py = pybind11;
static py::scoped_interpreter guard{};   // start the interpreter once
static py::object predictFunc;

/// internal helper
static std::vector<double> predictHist(int n,int m,int T,int q) {
    if (!predictFunc) {
        py::module_ sys = py::module_::import("sys");
        // Print sys.path before
        auto path_list = sys.attr("path");
        std::cout << "[C++] Original sys.path:\n";
        for (auto item : path_list) std::cout << "  " << py::str(item) << "\n";

        // Insert correct path
       // sys.attr("path").attr("append")("C:/Workspace/adaptive-snapshots/ml/.venv/Lib/site-packages");
        sys.attr("path").attr("append")("C:/Workspace/adaptive-snapshots/");

        // Print again
        std::cout << "[C++] Updated sys.path:\n";
        for (auto item : path_list) std::cout << "  " << py::str(item) << "\n";

        auto mlmod = py::module_::import("ml.predict_hist");
        predictFunc = mlmod.attr("predict_hist");
    }
    return predictFunc(n,m,T,q).cast<std::vector<double>>();
}

std::vector<int> chooseSnapshotTimes(int n, int m, int T, int q, int B) {
    std::cout << "Running chooseSnapshotTimes..." << std::endl;

    std::vector<double> hist;
    try {
        hist = predictHist(n, m, T, q);
    } catch (const std::exception& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
        return {};
    }

    std::cout << "Got histogram of size: " << hist.size() << std::endl;

    int bins = hist.size();
    std::vector<double> cdf(bins);
    cdf[0] = hist[0];
    for (int i = 1; i < bins; ++i) cdf[i] = cdf[i - 1] + hist[i];

    std::vector<int> bounds;
    double invBins = 1.0 / bins;
    for (int b = 1; b < B; ++b) {
        double frac = double(b) / B;
        int idx = std::lower_bound(cdf.begin(), cdf.end(), frac) - cdf.begin();
        int t = std::min(int(idx * invBins * T), T - 1);
        bounds.push_back(t);
    }

    std::cout << "Generated " << bounds.size() << " snapshot boundaries.\n";
    return bounds;
}