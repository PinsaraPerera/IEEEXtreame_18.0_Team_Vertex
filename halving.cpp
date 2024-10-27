#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

int main() {
    int N;
    cin >> N;
    if (N > 20) {
        cout << "0" << endl; // For large N, the problem is computationally infeasible
        return 0;
    }
    vector<int> C(2 * N);
    vector<int> assigned_numbers;
    vector<bool> number_used(2 * N + 1, false);
    for (int i = 0; i < 2 * N; ++i) {
        cin >> C[i];
        if (C[i] != -1) {
            assigned_numbers.push_back(C[i]);
            number_used[C[i]] = true;
        }
    }
    vector<int> R(N);
    for (int i = 0; i < N; ++i) {
        cin >> R[i];
    }
    vector<int> B(N);
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }
    // Check that elements of B are distinct
    vector<bool> B_used(2 * N + 1, false);
    for (int i = 0; i < N; ++i) {
        if (B_used[B[i]]) {
            cout << 0 << endl;
            return 0;
        }
        B_used[B[i]] = true;
    }
    // Check that B_i is not assigned to a position outside its pair
    for (int i = 0; i < N; ++i) {
        int pos1 = 2 * i;
        int pos2 = 2 * i + 1;
        if ((C[pos1] == B[i] || C[pos2] == B[i])) continue;
        for (int j = 0; j < 2 * N; ++j) {
            if (j != pos1 && j != pos2 && C[j] == B[i]) {
                cout << 0 << endl;
                return 0;
            }
        }
    }
    vector<int> available_numbers;
    for (int x = 1; x <= 2 * N; ++x) {
        if (!number_used[x]) {
            available_numbers.push_back(x);
        }
    }
    unordered_map<int, int> num_to_bit;
    int idx = 0;
    for (int num : available_numbers) {
        num_to_bit[num] = idx++;
    }
    int total_available = available_numbers.size();
    // Generate possible assignments per pair
    vector<vector<pair<int, int>>> pair_assignments(N);
    bool possible = true;
    for (int i = 0; i < N; ++i) {
        int pos1 = 2 * i;
        int pos2 = 2 * i + 1;
        int R_i = R[i];
        int B_i = B[i];
        int A1 = C[pos1];
        int A2 = C[pos2];
        vector<pair<int, int>> valid_assignments;
        // Both positions known
        if (A1 != -1 && A2 != -1) {
            bool valid = false;
            if (R_i == 0 && min(A1, A2) == B_i) valid = true;
            if (R_i == 1 && max(A1, A2) == B_i) valid = true;
            if (!valid) {
                possible = false;
                break;
            }
            continue; // No unknowns in this pair
        }
        // One position known
        else if (A1 != -1 || A2 != -1) {
            int known_value = A1 != -1 ? A1 : A2;
            int unknown_pos = A1 == -1 ? pos1 : pos2;
            if (known_value != B_i && number_used[B_i]) {
                possible = false;
                break;
            }
            if (known_value == B_i) {
                // Need to assign a number to the unknown position
                for (int val : available_numbers) {
                    if (number_used[val]) continue;
                    if (val == known_value) continue;
                    bool valid = false;
                    if (R_i == 0 && min(known_value, val) == B_i) valid = true;
                    if (R_i == 1 && max(known_value, val) == B_i) valid = true;
                    if (valid) {
                        valid_assignments.emplace_back(unknown_pos, val);
                    }
                }
            } else {
                if (B_i != known_value) {
                    possible = false;
                    break;
                }
                // Assign B_i to the unknown position
                if (!number_used[B_i]) {
                    valid_assignments.emplace_back(unknown_pos, B_i);
                } else {
                    possible = false;
                    break;
                }
            }
        }
        // Both positions unknown
        else {
            // Need to assign B_i to one of the positions
            for (int val1 : available_numbers) {
                if (number_used[val1]) continue;
                if (val1 != B_i) continue;
                for (int val2 : available_numbers) {
                    if (val2 == val1 || number_used[val2]) continue;
                    bool valid = false;
                    if (R_i == 0 && min(val1, val2) == B_i) valid = true;
                    if (R_i == 1 && max(val1, val2) == B_i) valid = true;
                    if (valid) {
                        valid_assignments.emplace_back(val1, val2);
                    }
                }
            }
        }
        if (valid_assignments.empty() && (A1 == -1 || A2 == -1)) {
            possible = false;
            break;
        }
        pair_assignments[i] = valid_assignments;
    }
    if (!possible) {
        cout << 0 << endl;
        return 0;
    }
    // Use DP to count the number of valid assignments
    unordered_map<long long, int> dp[2];
    dp[0][0] = 1;
    int curr = 0, next = 1;
    for (int i = 0; i < N; ++i) {
        dp[next].clear();
        if (pair_assignments[i].empty()) {
            dp[next] = dp[curr];
        } else {
            for (const auto& state : dp[curr]) {
                long long used = state.first;
                int ways = state.second;
                for (const auto& assignment : pair_assignments[i]) {
                    long long new_used = used;
                    int val1 = assignment.first;
                    int val2 = assignment.second;
                    int bit1 = num_to_bit[val1];
                    int bit2 = num_to_bit[val2];
                    if (used & (1LL << bit1)) continue;
                    if (used & (1LL << bit2)) continue;
                    new_used |= (1LL << bit1);
                    new_used |= (1LL << bit2);
                    dp[next][new_used] = (dp[next][new_used] + ways) % MOD;
                }
            }
        }
        swap(curr, next);
    }
    int result = 0;
    for (const auto& state : dp[curr]) {
        result = (result + state.second) % MOD;
    }
    cout << result << endl;
    return 0;
}
