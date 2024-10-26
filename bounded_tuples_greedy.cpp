#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll MOD = 998244353;
const ll MAX_COMBINATIONS = 1e7;

int N, M;
vector<ll> U; // Upper bounds for variables
vector<ll> L; // Lower bounds for variables
vector<bool> variable_in_constraint;
vector<ll> low, high;
vector<vector<int>> P;

ll total_assignments = 0;
ll total_combinations = 1;

// Recursive function to assign values to variables and count valid assignments
void dfs(int idx, vector<ll>& V) {
    if (total_assignments > MAX_COMBINATIONS) {
        return;
    }
    if (idx == N) {
        // Check all constraints
        bool valid = true;
        for (int c = 0; c < M; c++) {
            ll sum = 0;
            for (int idx2 : P[c]) {
                sum += V[idx2];
            }
            if (sum < low[c] || sum > high[c]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            total_assignments = (total_assignments + 1) % MOD;
        }
        return;
    }

    for (ll val = L[idx]; val <= U[idx]; val++) {
        V[idx] = val;
        dfs(idx + 1, V);
        V[idx] = -1; // Reset for next iteration
        if (total_assignments > MAX_COMBINATIONS) {
            return;
        }
    }
}

int main() {
    cin >> N >> M;

    U.resize(N, 1e18); // Initialize upper bounds to a large value
    L.resize(N, 0);    // Initialize lower bounds to 0
    variable_in_constraint.resize(N, false);
    low.resize(M);
    high.resize(M);
    P.resize(M);

    for (int c = 0; c < M; c++) {
        int K;
        cin >> low[c] >> high[c] >> K;
        P[c].resize(K);
        for (int i = 0; i < K; i++) {
            cin >> P[c][i];
            P[c][i]--; // Convert to 0-based index
            variable_in_constraint[P[c][i]] = true;
        }
    }

    // Update variable bounds based on constraints
    for (int idx = 0; idx < N; idx++) {
        for (int c = 0; c < M; c++) {
            bool contains = false;
            for (int idx2 : P[c]) {
                if (idx2 == idx) {
                    contains = true;
                    break;
                }
            }
            if (contains) {
                // Calculate possible min and max for this variable based on this constraint
                ll sum_min = 0;
                ll sum_max = 0;
                for (int idx2 : P[c]) {
                    if (idx2 != idx) {
                        sum_min += 0; // Variables are non-negative
                        sum_max += U[idx2];
                    }
                }
                ll var_min = max(L[idx], low[c] - sum_max);
                ll var_max = min(U[idx], high[c] - sum_min);
                if (var_min > var_max) {
                    cout << 0 << endl;
                    return 0;
                }
                L[idx] = max(L[idx], var_min);
                U[idx] = min(U[idx], var_max);
            }
        }
    }

    // Check if any variable is unbounded
    bool unbounded = false;
    for (int i = 0; i < N; i++) {
        if (!variable_in_constraint[i]) {
            unbounded = true;
            break;
        }
    }

    if (unbounded) {
        cout << "infinity" << endl;
        return 0;
    }

    // Check if total combinations are feasible
    total_combinations = 1;
    for (int i = 0; i < N; i++) {
        if (L[i] > U[i]) {
            cout << 0 << endl;
            return 0;
        }
        ll range = U[i] - L[i] + 1;
        total_combinations *= range;
        if (total_combinations > MAX_COMBINATIONS) {
            cout << 0 << endl;
            return 0;
        }
    }

    // Initialize variables
    vector<ll> V(N, -1);

    dfs(0, V);

    cout << total_assignments << endl;
    return 0;
}
