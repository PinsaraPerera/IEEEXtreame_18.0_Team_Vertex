#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to calculate an approximation of division by 3 using bit shifts
int approximateDivisionBy3(int bignr) {
    return (bignr + (bignr >> 2) + (bignr >> 4) + (bignr >> 6) + (bignr >> 8) +
                (bignr >> 10) + (bignr >> 12) + (bignr >> 14) + (bignr >> 16) +
                (bignr >> 18) + (bignr >> 20) + (bignr >> 22) + (bignr >> 24) +
                (bignr >> 26) + (bignr >> 28) + (bignr >> 30)) >> 2;
}

// Function to check if the number represented by a vector of digits is divisible by 3
bool isDivisibleBy3(const vector<int>& digits) {
    int sum = 0;
    for (int digit : digits) {
        sum += digit;
    }
    return sum % 3 == 0;
}

// Function to divide the number represented by a vector of digits by 3
int divideBy3WithApproximation(vector<int>& digits) {
    int carry = 0;
    int len = digits.size();
    int leadingZeros = 0;
    
    // Process each digit and approximate the division
    for (int i = 0; i < len; ++i) {
        int current = carry * 10 + digits[i];
        digits[i] = approximateDivisionBy3(current);
        carry = current % 3;
        if (digits[i] == 0 && leadingZeros == i) {
            leadingZeros++;
        }
    }
    
    // Remove leading zeros
    return leadingZeros;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Input number as a string
    string s;
    cin >> s;
    
    // Remove leading zeros
    size_t start = s.find_first_not_of('0');
    if (start == string::npos) {
        // If the number is zero or consists solely of zeros
        cout << "-1" << endl;
        return 0;
    }
    
    // Convert the number into a vector of digits
    vector<int> digits;
    for (size_t i = start; i < s.size(); i++) {
        digits.push_back(s[i] - '0');
    }
    
    // Special case: if the number is 1, the answer is 0 (since 3^0 = 1)
    if (digits.size() == 1 && digits[0] == 1) {
        cout << "0" << endl;
        return 0;
    }
    
    int steps = 0;
    
    // Process the number repeatedly by dividing by 3
    while (true) {
        // First, check if the sum of digits is divisible by 3
        if (!isDivisibleBy3(digits)) {
            cout << "-1" << endl;
            return 0;
        }
        
        // Divide the number by 3 using the approximation
        int leadingZeros = divideBy3WithApproximation(digits);
        digits.erase(digits.begin(), digits.begin() + leadingZeros); // Remove leading zeros
        steps++;
        
        // If the result is "1", we are done
        if (digits.size() == 1 && digits[0] == 1) {
            cout << steps << endl;
            return 0;
        }
    }
}
