#include <iostream>
#include <string>
#include <numeric>

using namespace std;

int main() {
    //use strings to avoid floating point erros
    string s;
    int repeating_decimals;
    cin >> s >> repeating_decimals;

    int index = s.find('.');

    string number = s.substr(0, index) + s.substr(index + 1);

    int shift_left = s.size() - index - repeating_decimals - 1;

    string non_repeating = number.substr(0, index + shift_left);
    string repeating = number.substr(index + shift_left, repeating_decimals);

    unsigned long long non_rep_int = stoull(non_repeating);
    unsigned long long full_rep_int = stoull(non_repeating + repeating);

    unsigned long long numerator = full_rep_int - non_rep_int;
    unsigned long long denom = stoull(string(repeating_decimals, '9') + string(shift_left, '0')); // 999...000

    unsigned long long g = gcd(numerator, denom);
    numerator /= g;
    denom /= g;

    cout << numerator << "/" << denom << endl;

    return 0;
}
