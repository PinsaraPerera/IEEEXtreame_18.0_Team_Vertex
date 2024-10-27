#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to compute (base^exp) % mod using fast exponentiation
ll powmod(ll base, ll exp, ll mod){
    ll res = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N;
    ll M;
    cin >> N >> M;
    
    // If N is even, no valid target permutations exist
    if(N % 2 == 0){
        cout << "0";
        return 0;
    }
    
    int k = (N - 1) / 2;
    
    // Compute factorials up to N modulo M
    // fact[i] = i! % M
    vector<ll> fact(N + 1, 1);
    for(int i = 1; i <= N; i++) {
        fact[i] = (fact[i - 1] * i) % M;
    }
    
    // Compute C(N-1, k) modulo M
    // C(n, k) = fact[n] * inv(fact[k]) * inv(fact[n-k]) % M
    ll fact_n_minus_1 = fact[N - 1];
    ll fact_k = fact[k];
    ll fact_n_minus_k = fact[N - 1 - k];
    
    // Compute modular inverses using Fermat's Little Theorem
    // Since M is prime, inverse exists
    ll inv_fact_k = powmod(fact_k, M - 2, M);
    ll inv_fact_n_minus_k = powmod(fact_n_minus_k, M - 2, M);
    
    // Compute C(N-1, k)
    ll C = (fact_n_minus_1 * inv_fact_k) % M;
    C = (C * inv_fact_n_minus_k) % M;
    
    // Compute sum_move = k * (k + 1) * (N-1)! % M
    ll sum_move = (( (k * (k + 1)) % M ) * fact_n_minus_1 ) % M;
    
    // Compute k*(k-1)
    ll kl = (ll)k * (k - 1);
    
    // Compute sum_sort = C * k! * k*(k-1) % M
    ll sum_sort = ((C * fact_k) % M);
    sum_sort = (sum_sort * kl) % M;
    
    // Compute total_sum = (sum_move + sum_sort) % M
    ll total_sum = (sum_move + sum_sort) % M;
    
    cout << total_sum;
}
