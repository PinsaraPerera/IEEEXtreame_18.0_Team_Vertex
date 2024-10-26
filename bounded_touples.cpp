#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const long long INF = 1e18;

struct Constraint {
    long long low;
    long long high;
    vector<int> indices;
};

int N, M;
vector<Constraint> constraints;


int countValidAssignments(vector<long long>& values, int idx) {
    if (idx == N) {
        // Check all constraints
        for (const auto& constraint : constraints) {
            long long sum = 0;
            for (int i : constraint.indices) {
                sum += values[i];
            }
            if (sum < constraint.low || sum > constraint.high) {
                return 0; // Does not satisfy this constraint
            }
        }
        return 1; 
    }

    
    long long max_value = INF;
    for (const auto& constraint : constraints) {
        if (find(constraint.indices.begin(), constraint.indices.end(), idx) != constraint.indices.end()) {
            long long remaining_high = constraint.high;
            for (int i : constraint.indices) {
                if (i != idx) {
                    remaining_high -= values[i];
                }
            }
            max_value = min(max_value, remaining_high);
        }
    }
    max_value = max(max_value, 0LL);


    int validCount = 0;
    for (long long v = 0; v <= max_value; ++v) {
        values[idx] = v;
        int result = countValidAssignments(values, idx + 1);
        validCount = (validCount + result) % MOD;

        // Stop if validCount grows too large, signaling infinite solutions
        if (validCount >= MOD) return MOD;
    }

    return validCount;
}

int main() {
    cin >> N >> M;

    // Special case: if there are no constraints, return "infinity"
    if (M == 0) {
        cout << "infinity" << endl;
        return 0;
    }

    constraints.resize(M);
    for (int i = 0; i < M; ++i) {
        long long low, high;
        int K;
        cin >> low >> high >> K;
        constraints[i].low = low;
        constraints[i].high = high;
        constraints[i].indices.resize(K);
        for (int j = 0; j < K; ++j) {
            cin >> constraints[i].indices[j];
            constraints[i].indices[j]--; // Convert to 0-based index
        }
    }

    vector<long long> values(N, 0); // Initialize all V_i to zero
    int result = countValidAssignments(values, 0);

    if (result >= MOD) {
        cout << "infinity" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
