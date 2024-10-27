#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

int N, Q;
int P[MAXN];
ll result[MAXN];

struct BIT {
    int N;
    vector<ll> tree;

    void init(int n) {
        N = n;
        tree.assign(N + 2, 0);
    }

    void point_update(int idx, ll val) {
        for (; idx <= N; idx += idx & -idx)
            tree[idx] += val;
    }

    void range_update(int l, int r, ll val) {
        point_update(l, val);
        point_update(r + 1, -val);
    }

    ll prefix_query(int idx) {
        ll res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += tree[idx];
        return res;
    }

    ll range_query(int l, int r) {
        return prefix_query(r) - prefix_query(l - 1);
    }

    ll point_query(int idx) {
        return prefix_query(idx) - prefix_query(idx - 1);
    }
};

struct Event {
    int idx;
    int type; // 0: update0, 1: update1, 2: query2, 3: query3
    int l, r;
    ll c;     // Only for updates
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        cin >> P[i];
    }

    vector<Event> events;

    for (int idx = 0; idx < Q; ++idx) {
        int T;
        cin >> T;
        Event e;
        e.idx = idx;
        e.type = T;
        if (T == 0 || T == 1) {
            cin >> e.l >> e.r >> e.c;
        } else {
            cin >> e.l >> e.r;
            e.c = 0;
        }
        events.push_back(e);
    }

    BIT bit0, bit1;
    bit0.init(N);
    bit1.init(N);

    vector<ll> ans(Q);
    for (auto &e : events) {
        if (e.type == 0) {
            // Type 0 update: Range update on A[l..r]
            bit0.range_update(e.l, e.r, e.c);
        } else if (e.type == 1) {
            // Type 1 update: Point updates on positions P[l..r]
            for (int i = e.l; i <= e.r; ++i) {
                int pos = P[i];
                bit1.point_update(pos, e.c);
            }
        } else if (e.type == 2) {
            // Type 2 query: Sum A[l..r]
            ll sum0 = bit0.range_query(e.l, e.r);
            ll sum1 = bit1.range_query(e.l, e.r);
            ans[e.idx] = sum0 + sum1;
        } else if (e.type == 3) {
            // Type 3 query: Sum A_{P[l..r]}
            ll total_sum = 0;
            for (int i = e.l; i <= e.r; ++i) {
                int pos = P[i];
                ll val0 = bit0.point_query(pos);
                ll val1 = bit1.point_query(pos);
                total_sum += val0 + val1;
            }
            ans[e.idx] = total_sum;
        }
    }

    for (auto &e : events) {
        if (e.type == 2 || e.type == 3) {
            cout << ans[e.idx] << '\n';
        }
    }

    return 0;
}
