#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Constants for double hashing
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE1 = 911;
const ll BASE2 = 3571;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string S;
    cin >> S;
    int N = S.length();
    
    // Precompute prefix hashes and powers
    vector<ll> prefix1(N+1, 0), prefix2(N+1, 0);
    vector<ll> power1(N+1, 1), power2(N+1, 1);
    
    for(int i=0; i<N; i++){
        prefix1[i+1] = (prefix1[i] * BASE1 + (S[i]-'a' +1)) % MOD1;
        prefix2[i+1] = (prefix2[i] * BASE2 + (S[i]-'a' +1)) % MOD2;
        power1[i+1] = (power1[i] * BASE1) % MOD1;
        power2[i+1] = (power2[i] * BASE2) % MOD2;
    }
    
    // Initialize min_length[M] to INF
    vector<int> min_length(N, N+1);
    
    // Temporary storage for hash pairs
    typedef pair<ll, ll> hash_pair;
    
    // For each possible length
    for(int l=1; l<=N; l++){
        if(l > N) break;
        int total_substrings = N - l +1;
        // Vector of pairs: (hash_pair, starting position)
        vector<pair<hash_pair, int>> substrings;
        substrings.reserve(total_substrings);
        for(int s=0; s <= N - l; s++){
            ll hash1 = (prefix1[s + l] - (prefix1[s] * power1[l]) % MOD1 + MOD1) % MOD1;
            ll hash2 = (prefix2[s + l] - (prefix2[s] * power2[l]) % MOD2 + MOD2) % MOD2;
            substrings.emplace_back(make_pair(make_pair(hash1, hash2), s));
        }
        // Sort the substrings by hash1 and hash2
        sort(substrings.begin(), substrings.end(), [&](const pair<hash_pair, int> &a, const pair<hash_pair, int> &b) -> bool{
            if(a.first.first != b.first.first) return a.first.first < b.first.first;
            return a.first.second < b.first.second;
        });
        // Group substrings with the same hash
        int i =0;
        while(i < substrings.size()){
            int j = i+1;
            while(j < substrings.size() && substrings[j].first == substrings[i].first){
                j++;
            }
            // Now, substrings from i to j-1 have the same substring
            // Collect all starting positions
            vector<int> starts;
            starts.reserve(j - i);
            for(int k=i; k<j; k++) starts.push_back(substrings[k].second);

            vector<pair<int, int>> intervals;
            intervals.reserve(starts.size());
            for(auto &s_pos: starts){
                int start_bridge = s_pos +1;
                int end_bridge = s_pos + l -1;
                if(start_bridge > end_bridge || end_bridge > N-1){
                    continue;
                }
                intervals.emplace_back(make_pair(start_bridge, end_bridge));
            }
            if(intervals.empty()){
                // No bridges covered by this substring
                // Update min_length[0] (M = 0)
                min_length[0] = min(min_length[0], l);
                i = j;
                continue;
            }
            // Sort the intervals by start_bridge
            sort(intervals.begin(), intervals.end());
            // Merge intervals and count unique bridge positions
            int merged_start = intervals[0].first;
            int merged_end = intervals[0].second;
            int total_bridge = 0;
            for(int k=1; k<intervals.size(); k++){
                if(intervals[k].first <= merged_end +1){
                    merged_end = max(merged_end, intervals[k].second);
                }
                else{
                    total_bridge += (merged_end - merged_start +1);
                    merged_start = intervals[k].first;
                    merged_end = intervals[k].second;
                }
            }
            total_bridge += (merged_end - merged_start +1);
            // Update min_length[M]
            if(total_bridge >=0 && total_bridge < N){
                min_length[total_bridge] = min(min_length[total_bridge], l);
            }
            i = j;
        }
    }
    
    vector<int> answer(N, 0);
    for(int k=1; k<=N; k++){
        int M = N -k;
        if(M >=0 && M < N && min_length[M] <= N){
            answer[k-1] = min_length[M];
        }
        else{
            answer[k-1] = 0;
        }
    }
    
    // Print the answers
    for(int i=0; i<N; i++){
        cout << answer[i] << (i < N-1 ? ' ' : '\n');
    }
}
