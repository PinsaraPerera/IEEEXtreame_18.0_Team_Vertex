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
    
    // Initialize min_length[M] to INF (N+1)
    vector<int> min_length(N, N+1);
    
    // Temporary storage for hash and starting positions
    typedef pair<ll, ll> hash_pair;
    
    // Define a temporary vector for substrings of current l
    vector<pair<hash_pair, int>> substrings;
    substrings.reserve(N); // Maximum N substrings per l
    
    // Reusable temporary vectors to avoid reallocations
    vector<int> starts;
    vector<pair<int, int>> intervals;
    
    // Iterate over all possible substring lengths
    for(int l=1; l<=N; l++){
        // Number of substrings of length l
        int total_substrings = N - l +1;
        substrings.clear();
        substrings.reserve(total_substrings);
        
        // Compute hashes for all substrings of length l
        for(int s=0; s <= N - l; s++){
            ll hash1 = (prefix1[s + l] - (prefix1[s] * power1[l]) % MOD1 + MOD1) % MOD1;
            ll hash2 = (prefix2[s + l] - (prefix2[s] * power2[l]) % MOD2 + MOD2) % MOD2;
            substrings.emplace_back(make_pair(make_pair(hash1, hash2), s));
        }
        
        // Sort the substrings by hash1 and then hash2
        sort(substrings.begin(), substrings.end(), [&](const pair<hash_pair, int> &a, const pair<hash_pair, int> &b) -> bool{
            if(a.first.first != b.first.first) return a.first.first < b.first.first;
            return a.first.second < b.first.second;
        });
        
        // Process groups of identical substrings
        int i =0;
        while(i < substrings.size()){
            int j = i+1;
            while(j < substrings.size() && substrings[j].first == substrings[i].first){
                j++;
            }
            // Substrings from i to j-1 have the same hash (i.e., identical substrings)
            
            // Collect starting positions
            starts.clear();
            starts.reserve(j - i);
            for(int k=i; k<j; k++) starts.push_back(substrings[k].second);
    
            // Create intervals [s+1, s+l-1] for each starting position
            intervals.clear();
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
            // Sort intervals by start_bridge to facilitate merging
            sort(intervals.begin(), intervals.end());
            
            // Merge overlapping or contiguous intervals and count unique bridge positions
            int total_bridge = 0;
            int current_start = intervals[0].first;
            int current_end = intervals[0].second;
            for(int k=1; k<intervals.size(); k++){
                if(intervals[k].first <= current_end +1){
                    current_end = max(current_end, intervals[k].second);
                }
                else{
                    total_bridge += (current_end - current_start +1);
                    current_start = intervals[k].first;
                    current_end = intervals[k].second;
                }
            }
            total_bridge += (current_end - current_start +1);
            
            // Update min_length[M] where M = total_bridge
            if(total_bridge < N){
                min_length[total_bridge] = min(min_length[total_bridge], l);
            }
            
            i = j;
        }
    }
    
    // Prepare the answer based on min_length
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
