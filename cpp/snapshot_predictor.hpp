#pragma once
#include <vector>

/// Return vector of snapshot boundaries (B-1 values) in [0,T)
/// B is chosen by caller (e.g. B = ceil(sqrt(k)) )
std::vector<int> chooseSnapshotTimes(
        int n, int m, int T,int q, int B);
