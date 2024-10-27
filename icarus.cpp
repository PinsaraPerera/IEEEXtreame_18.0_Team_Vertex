#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cin >> S;
    int S_len = S.length();

    // Check for presence of 'U', 'L', 'R'
    bool hasU = false, hasL = false, hasR = false;
    for (char c : S) {
        if (c == 'U') hasU = true;
        if (c == 'L') hasL = true;
        if (c == 'R') hasR = true;
    }

    // Initialize variables
    int N = 0;
    int A, B;
    int MAXN = 4002;
    vector<int> left_child(MAXN, 0);
    vector<int> right_child(MAXN, 0);
    vector<int> parent_node(MAXN, 0);

    if (hasU) {
        // Assign B = 1, A = 2
        B = 1;
        A = 2;
        left_child[B] = A;
        parent_node[A] = B;
        N = 2;
        // Start simulation from A
        int current = A;
        for (char c : S) {
            if (c == 'L') {
                if (left_child[current]) {
                    current = left_child[current];
                } else {
                    N++;
                    if (N > 2 * S_len) {
                        cout << "-1";
                        return 0;
                    }
                    left_child[current] = N;
                    parent_node[N] = current;
                    current = N;
                }
            } else if (c == 'R') {
                if (right_child[current]) {
                    current = right_child[current];
                } else {
                    N++;
                    if (N > 2 * S_len) {
                        cout << "-1";
                        return 0;
                    }
                    right_child[current] = N;
                    parent_node[N] = current;
                    current = N;
                }
            } else if (c == 'U') {
                if (parent_node[current]) {
                    current = parent_node[current];
                }
                // If no parent, skip
            }
        }
    } else {
        if ((hasL && hasR) || (!hasL && !hasR)) {
            // Impossible to prevent B from being visited
            cout << "-1";
            return 0;
        }
        if (hasL && !hasR) {
            // S contains only 'L's
            A = 1;
            B = 2;
            right_child[A] = B;
            parent_node[B] = A;
            N = 2;
        } else if (hasR && !hasL) {
            // S contains only 'R's
            A = 1;
            B = 2;
            left_child[A] = B;
            // Additionally, assign right child to allow 'R' moves
            right_child[A] = 3;
            parent_node[3] = A;
            N = 3;
        }

        // Start simulation from A
        int current = A;
        for (char c : S) {
            if (c == 'L') {
                if (left_child[current]) {
                    current = left_child[current];
                }
                // Skip if no left child exists
            } else if (c == 'R') {
                if (right_child[current]) {
                    current = right_child[current];
                }
                // Skip if no right child exists
            }
            // No need to handle 'U' here, as it's irrelevant
        }
    }

    if (N > 2 * S_len) {
        cout << "-1";
        return 0;
    }

    // Output N, A, B
    cout << N << " " << A << " " << B << "\n";
    for (int i = 1; i <= N; i++) {
        cout << left_child[i] << " " << right_child[i] << "\n";
    }

    return 0;
}
