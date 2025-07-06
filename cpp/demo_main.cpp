#include "snapshot_predictor.hpp"
#include <iostream>
#include <cmath>

int main() {
    int n=1000, m=4000, T=100000, k=2500, q=300;
    int B = std::ceil(std::sqrt(k));
    auto snaps = chooseSnapshotTimes(n,m,T,q,B);

    std::cout << "Predicted " << snaps.size()+1
              << " blocks (B="<<B<<") boundaries:\n";
    for (int t : snaps) std::cout << "  t=" << t << '\n';
    std::cout << "(last block ends at T="<<T-1<<")\n";
}