#include <iostream>

using namespace std;

int main() {
    int val;
    cin >> val;
    unsigned long long last_three{1};
    unsigned long long two_count{0};
    unsigned long long five_count{0};
    for(long i = 2; i <= val; i++) {
        long num = i;

        while (num % 5 == 0) {
            five_count++;
            num /= 5;
        }
    }

    for(int i{2}; i <= val; i++) {
        int num = i;

        while (num % 5 == 0) {
            num /= 5;
        }

        while(num % 2 == 0 && two_count < five_count) {
            num /= 2;
            two_count++;
        }
        
        last_three *= num;
        last_three = last_three%1000;
            
    }
    
    if (val >= 7) {
        printf("%03d\n", last_three); //output with zero's in the begining
    } else {
        std::cout << last_three << std::endl; //e.g 5! = 120, so the output should be 12 not 012
    }
}