#include <bits/stdc++.h>
using namespace std;

// Function to find the maximum number by swapping using BFS with pruning
string maximizeNumber(string num, int K) {
    // Initialize a set to keep track of visited states at each level
    unordered_set<string> visited;
    // Initialize a queue for BFS
    queue<string> q;
    q.push(num);
    visited.insert(num);
    
    // Perform BFS for K levels
    for(int step = 0; step < K; step++) {
        int size = q.size();
        if(size == 0) break; // No more states to process
        unordered_set<string> currentLevel;
        for(int i = 0; i < size; i++) {
            string current = q.front(); q.pop();
            // Try all possible swaps for the current string
            for(int j = 0; j < current.size()-1; j++) {
                for(int l = j+1; l < current.size(); l++) {
                    // Avoid leading zero after swap
                    if(j == 0 && current[l] == '0') continue;
                    // If the digits are the same, no need to swap
                    if(current[j] == current[l]) continue;
                    // Swap the digits
                    string temp = current;
                    swap(temp[j], temp[l]);
                    // If this state hasn't been visited in this level, add it
                    if(!currentLevel.count(temp)) {
                        q.push(temp);
                        currentLevel.insert(temp);
                    }
                }
            }
        }
        // If no new states are generated, break early
        if(currentLevel.empty()) break;
    }
    
    // After K swaps, find the maximum number in the queue
    string max_num = "";
    while(!q.empty()) {
        string current = q.front(); q.pop();
        if(current.size() > max_num.size() || (current.size() == max_num.size() && current > max_num)) {
            max_num = current;
        }
    }
    return max_num;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N;
    int K;
    cin >> N >> K;
    string s = to_string(N);
    
    // Edge case: If the number has only one digit, return it as is
    if(s.size() == 1){
        cout << s;
        return 0;
    }
    
    // Edge case: If K is 0, return the original number
    if(K == 0){
        cout << s;
        return 0;
    }
    
    // Perform the maximization
    string result = maximizeNumber(s, K);
    
    cout << result;
}
