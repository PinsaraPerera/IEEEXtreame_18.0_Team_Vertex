#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <map>
#include <cassert>
#include <cstdint>

using namespace std;

float hexToFloat(const string& hexValue) {
    uint32_t intValue;
    stringstream ss;
    ss << hex << hexValue;
    ss >> intValue;
    float result;
    memcpy(&result, &intValue, sizeof(result));
    return result;
}


uint32_t floatToInt(float value) {
    uint32_t intValue;
    memcpy(&intValue, &value, sizeof(intValue));
    return intValue;
}


string intToHexString(uint32_t intValue) {
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << intValue;
    return ss.str();
}


float fusedMultiplyAdd(float a, float b, float c) {
    return fma(a, b, c);
}


float bitwiseNAND(float a, float b) {
    uint32_t intA = floatToInt(a);
    uint32_t intB = floatToInt(b);
    uint32_t nandResult = ~(intA & intB);
    float result;
    memcpy(&result, &nandResult, sizeof(result));
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    vector<string> results(T);

    for (int t = 0; t < T; ++t) {
        string C0_hex;
        cin >> C0_hex;
        float C0 = hexToFloat(C0_hex);

        // Read LUTs
        int L;
        cin >> L;
        vector<vector<float>> LUTs(L);

        for (int i = 0; i < L; ++i) {
            int lutSize;
            cin >> lutSize;
            LUTs[i].resize(lutSize);
            for (int j = 0; j < lutSize; ++j) {
                string hexValue;
                cin >> hexValue;
                LUTs[i][j] = hexToFloat(hexValue);
            }
        }

     
        int Q;
        cin >> Q;
        vector<float> C(1, C0); // Initial C[0]
        
        for (int q = 0; q < Q; ++q) {
            char command;
            cin >> command;

            if (command == 'C') {
                string hexValue;
                cin >> hexValue;
                C.push_back(hexToFloat(hexValue));
            } 
            else if (command == 'L') {
                int i, j, b;
                cin >> i >> j >> b;
                uint32_t C0_bits = floatToInt(C0);
                int mask = (C0_bits >> j) & ((1 << b) - 1);
                C.push_back(LUTs[i][mask]);
            } 
            else if (command == 'N') {
                int i, j;
                cin >> i >> j;
                C.push_back(bitwiseNAND(C[i], C[j]));
            } 
            else if (command == 'F') {
                int i, j, k;
                cin >> i >> j >> k;
                C.push_back(fusedMultiplyAdd(C[i], C[j], C[k]));
            }
        }

        // Convert the last command's result to a hexadecimal representation and store it
        results[t] = intToHexString(floatToInt(C.back()));
    }

    
    for (const auto& res : results) {
        cout << res << "\n";
    }

    return 0;
}
