#include <bits/stdc++.h>
using namespace std;

// Function to interleave bits of a 32-bit number (split by 1)
inline uint64_t splitBy1(uint32_t a) {
    uint64_t x = a;
    x = (x | (x << 16)) & 0x0000FFFF0000FFFFULL;
    x = (x | (x << 8)) & 0x00FF00FF00FF00FFULL;
    x = (x | (x << 4)) & 0x0F0F0F0F0F0F0F0FULL;
    x = (x | (x << 2)) & 0x3333333333333333ULL;
    x = (x | (x << 1)) & 0x5555555555555555ULL;
    return x;
}

// Function to compute Morton code for 2D coordinates
inline uint64_t mortonEncode2D(uint32_t x, uint32_t y) {
    return (splitBy1(y) << 1) | splitBy1(x);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    // Validate that N is a multiple of 3
    if(N % 3 != 0){
        // According to problem constraints, N is a multiple of 3
        // If not, output nothing or handle accordingly
        return 0;
    }
    
    // Preallocate arrays
    vector<int> x_coords(N);
    vector<int> y_coords(N);
    vector<uint64_t> morton_codes(N);
    
    // Read all points and compute Morton codes
    for(int i = 0; i < N; ++i){
        cin >> x_coords[i] >> y_coords[i];
        
        // Map signed coordinates to unsigned by adding 2^31
        uint32_t x_u = static_cast<uint32_t>(x_coords[i]) + 0x80000000;
        uint32_t y_u = static_cast<uint32_t>(y_coords[i]) + 0x80000000;
        
        morton_codes[i] = mortonEncode2D(x_u, y_u);
    }
    
    // Create a vector of indices
    vector<int> indices(N);
    for(int i = 0; i < N; ++i){
        indices[i] = i;
    }
    
    // Sort indices based on Morton codes
    sort(indices.begin(), indices.end(), [&](const int a, const int b) -> bool{
        return morton_codes[a] < morton_codes[b];
    });
    
    // Group every three consecutive indices
    // Preallocate space for groups
    vector<array<int, 3>> groups;
    groups.reserve(N / 3);
    
    for(int i = 0; i < N; i += 3){
        // Extract the three indices
        int idx1 = indices[i];
        int idx2 = indices[i+1];
        int idx3 = indices[i+2];
        
        // Sort the indices within the group for consistent ordering
        if(idx1 > idx2) swap(idx1, idx2);
        if(idx1 > idx3) swap(idx1, idx3);
        if(idx2 > idx3) swap(idx2, idx3);
        
        groups.push_back({idx1, idx2, idx3});
    }
    
    // Sort the groups based on the first index for consistent output
    sort(groups.begin(), groups.end(), [&](const array<int,3>& a, const array<int,3>& b) -> bool{
        if(a[0] != b[0]) return a[0] < b[0];
        if(a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2];
    });
    
    // Prepare the output using a buffer for efficiency
    string output;
    output.reserve(N * 12); // Approximate reservation (assuming max 10 digits per index + 2 spaces)
    
    for(auto &group : groups){
        output += to_string(group[0]) + ' ' + to_string(group[1]) + ' ' + to_string(group[2]) + '\n';
    }
    
    // Output all groups at once
    cout << output;
    
    return 0;
}
