# include <bits/stdc++.h>
using namespace std;

int main(){
    // clear n th bit
    // clear 2nd bit and return value

    int number, n_th_bit;
    cout << "Enter the number : ";
    cin >> number;
    cout << "Enter the bit you want to remove : ";
    cin >> n_th_bit;
    cout << (number & ~(1 << n_th_bit));
}