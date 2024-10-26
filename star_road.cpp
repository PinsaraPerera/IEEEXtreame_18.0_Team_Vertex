#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

int N;
int S[MAXN]; // Restaurant stars
vector<int> adj[MAXN]; // Original tree adjacency list
vector<int> dag[MAXN]; // DAG adjacency list
int dp[MAXN]; // Longest path length ending at node
bool visited[MAXN];
int ans = 1;
vector<int> topo_order;

void dfs_topo(int u) {
    visited[u] = true;
    for (int v : dag[u]) {
        if (!visited[v]) {
            dfs_topo(v);
        }
    }
    topo_order.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> S[i];
    }

    // Build the DAG based on the star ratings
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        if (S[u] < S[v]) {
            dag[u].push_back(v);
        } else if (S[u] > S[v]) {
            dag[v].push_back(u);
        }
        // If S[u] == S[v], no edge is added
    }

    // Perform topological sort
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            dfs_topo(i);
        }
    }

    reverse(topo_order.begin(), topo_order.end());

    // Initialize dp
    for (int i = 1; i <= N; ++i) {
        dp[i] = 1;
    }

    // Compute dp in topological order
    for (int u : topo_order) {
        for (int v : dag[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                ans = max(ans, dp[v]);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
