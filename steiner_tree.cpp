#include <iostream>
#include <vector>
#define MOD 1000099999
using namespace std;
typedef long long ll;

const int MAXN = 200005;
ll factorial[MAXN], inv_factorial[MAXN];

// Function to compute x^y modulo MOD
ll mod_pow(ll x, ll y, ll mod) {
    ll result = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1)
            result = result * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return result;
}

// Precompute factorials and inverse factorials
void compute_factorials(int n) {
    factorial[0] = 1;
    for (int i = 1; i <= n; i++)
        factorial[i] = factorial[i - 1] * i % MOD;
    inv_factorial[n] = mod_pow(factorial[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--)
        inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % MOD;
}

// Compute C(n, k) modulo MOD
ll comb(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return factorial[n] * inv_factorial[k] % MOD * inv_factorial[n - k] % MOD;
}

vector<vector<int>> tree;
vector<int> size_subtree;
vector<ll> cnt_p_sub, cnt_p;
vector<ll> W;

void dfs(int u, int parent) {
    size_subtree[u] = 1;
    ll sum_C2_children = 0;
    cnt_p_sub[u] = 0;
    for (int v : tree[u]) {
        if (v == parent)
            continue;
        dfs(v, u);
        size_subtree[u] += size_subtree[v];
        ll c2 = size_subtree[v] * (size_subtree[v] - 1) / 2 % MOD;
        sum_C2_children = (sum_C2_children + c2) % MOD;
        cnt_p[u] = (cnt_p[u] + cnt_p[v]) % MOD;
    }
    ll c2_size = size_subtree[u] * (size_subtree[u] - 1) / 2 % MOD;
    cnt_p_sub[u] = (c2_size - sum_C2_children + MOD) % MOD;
    cnt_p[u] = (cnt_p[u] + cnt_p_sub[u]) % MOD;
}

int main() {
    int N;
    cin >> N;
    compute_factorials(N + 5);

    W.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> W[i];

    tree.resize(N + 1);
    for (int i = 1; i <= N - 1; i++) {
        int U, V;
        cin >> U >> V;
        tree[U].push_back(V);
        tree[V].push_back(U);
    }

    size_subtree.resize(N + 1);
    cnt_p_sub.resize(N + 1);
    cnt_p.resize(N + 1);
    dfs(1, -1);

    ll sum_W = 0;
    ll sum_Wcntp = 0;
    for (int i = 1; i <= N; i++) {
        sum_W = (sum_W + W[i]) % MOD;
        sum_Wcntp = (sum_Wcntp + W[i] * cnt_p[i] % MOD) % MOD;
    }

    for (int k = 1; k <= N; k++) {
        ll c1 = comb(N - 1, k - 1);
        ll c2 = 0;
        if (k >= 2 && N >= 2)
            c2 = comb(N - 2, k - 2);
        ll ans = (sum_W * c1 % MOD + sum_Wcntp * c2 % MOD) % MOD;
        cout << ans << endl;
    }

    return 0;
}
