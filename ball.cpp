#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

ull N;
vector<ull> E;
ull total = 0;
int K;

void dfs(int index, ull product, int subset_size) {
    if (product > N) return;
    if (subset_size > 0) {
        ull count = N / product;
        if (subset_size % 2 == 1)
            total += count;
        else
            total -= count;
    }
    for (int i = index; i < K; ++i) {
        // To prevent overflow, check if product * E[i] > N
        if (product > N / E[i]) continue;
        dfs(i + 1, product * E[i], subset_size + 1);
    }
}

int main() {
    cin >> N >> K;
    E.resize(K);
    for (int i = 0; i < K; ++i) {
        cin >> E[i];
    }
    sort(E.begin(), E.end());
    dfs(0, 1, 0);
    cout << total << endl;
    return 0;
}
