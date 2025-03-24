    #include <iostream>
    #include <iterator>
    #include <string>
    #include <utility>
    #include <cmath>
    #include <sstream>
    #include <numeric>

    using namespace std;

    string handleRepeatingDecimalInput(std::string& input) {
        input = input.substr(2);
        size_t pos = input.find("...");

        if (pos != std::string::npos) {
            std::string trimmedInput = input.substr(0, pos);        
            std::stringstream ss(trimmedInput);
            return ss.str();
        }

        std::stringstream ss(input);
        return ss.str();
    }

    pair<long long, long long> calc_fraction(string val) {
        long long best_numerator = pow(10, 10);
        long long best_denom = pow(10, 10);
        for(int i{0}; i < val.size(); i++) {
            long long val1 = 0;
            long long val2 = 0;
            if (i != 0) {
                val1 = stoi(val.substr(0, i));
            }
            if (i <= val.size()-1) {
                val2 = stoi(val.substr(i));
            }
            long long numerator = val1 * (pow(10LL, val.size()-i)-1) + val2;
            long long denom = pow(10LL, i) * (pow(10LL, val.size()-i)-1);
            int g = gcd(numerator, denom);
            numerator /= g;
            denom /= g;
            if (denom < best_denom) {
                best_numerator = numerator;
                best_denom = denom;
            }
        }
        return {best_numerator, best_denom};
    }

    int main() {
        while (true){
            string s;
            cin >> s;
            if (s == "0") {
                break;
            } else {
                auto val = handleRepeatingDecimalInput(s);
                
                auto result = calc_fraction(val);
                std::cout << result.first << "/" << result.second << std::endl;
            }
        }
    }

