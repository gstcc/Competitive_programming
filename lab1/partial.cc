#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

void print_A(vector<double> const& A, int n) {
    int index = 0;
    for(double el : A) {
        std::cout << el << " ";
        index++;
        if (index % n == 0) {
            std::cout << endl;
        }
    }
}

void reduce_row(vector<double> & A, int n, int index) {
    double factor = A[index];
    if (factor == 0) {
        return;
    }
    for(int i{index}; i<index+n && i<A.size(); i++) {
        A[i] /= factor;
    }
}

void row_subtraction(vector<double> & A, int n, int first_row, int second_row, int col) {
    double factor = A[second_row*n+col];
    for(int i{first_row*n+col}; i<(first_row+1)*n; i++) {
        A[second_row*n+col] -= A[i]*factor;
        // cout << second_row*n+col << endl;
        ++col;
    }
}

void swap_row(vector<double> & A, int n, int first_row, int second_row) {
    for(int c=0; c<n; c++) {
        double tmp = A[first_row*n + c];
        A[first_row*n + c] = A[second_row*n + c];
        A[second_row*n + c] = tmp; 
    }
}

void rref(vector<double> & A, int n) {
    int row = 0; //Current row we are pivoting
    for(int col{0}; col < n && row < n-1; col++) {
        bool not_zero_row = false;
        if (abs(A[row*n+col]) <= 1e-5) { //equal to zero, with some room of floating point value
            int swap_with = row;
            while(abs(A[swap_with*n+col]) <= 1e-5) {
                swap_with++;
                if (swap_with >= n-1) {
                    not_zero_row = true;
                    break;
                }
            }
            if (!not_zero_row) {
                swap_row(A, n, row, swap_with);
            }
        }
        if (!not_zero_row) {
            reduce_row(A, n, row*n+col); 
            int second_row = 0;
            while(second_row < n-1) {
                if (second_row != row) {
                    row_subtraction(A, n, row, second_row, col);
                }
                second_row++;
            }
        }
        ++row;
    }
}

std::string is_solvable(vector<double> const& A, int n) {
    int col = 0;
    std::ostringstream oss("");
    bool multiple {false}; 
    for(int r{0}; r<n-1; r++) {
        int count = 0;
        for(int c{col}; c<n-1; c++) { //Find all elements in row that are non-zero
            if (abs(A[r*n+c]) >= 1e-9) { //not zero
                ++count;
            }
        }
        if (count == 1) { //Single solution to variable
            oss << std::fixed << setprecision(3) << A[(r+1)*n-1] << " ";
        } else if (count == 0 && abs(A[(r+1)*n-1]) >= 1e-9 ) { //Make sure we don't have an illegal instruction
            return "-1";
        } else {
            multiple = true;
            
        }
        ++col;
    }
    if (multiple) {
        return "-2";
    }
    // All unkown variablle have a single value, solvable
    return oss.str();
}

vector<string> find_unkown_variables(vector<double> const& A, int n) {
    vector<string> variables(n-1);
    for(int r{0}; r<n-1; r++) {
        vector<int> indices;
        for(int c{0}; c<n-1; c++) { //Find all elements in row that are non-zero, except last one
            if (abs(A[r*n+c]) >= 1e-9) {
                indices.push_back(c);
            }
        }
        if (indices.size()==1 && variables[indices.back()] != "?") { //just one left variable, we can 
            variables[indices.back()] = to_string(A[r*n+indices.back()]);
        } else if (indices.size() > 1) {
            for (int i : indices) {
                variables[i] = "?";
            }
        }
    }
    return variables;
}

vector<double> flatten_vectors(vector<double> const A, vector<double> const& b, int n) {
    vector<double> combined{};
    int b_index = 0;
    for (int i{0}; i<A.size(); i++) {
        if (i%n==0 && i!=0) {
            combined.push_back(b[b_index]);
            b_index++;
        }
        combined.push_back(A[i]);
    }
    combined.push_back(b[b_index]);
    return combined;
}

int main() {
    int n;
    while (cin >> n) {
        if (n==0) break;

        vector<double> A(n*n);
        vector<double> b(n);
        
        for(int i{0}; i<n*n; i++) {
            cin >> A[i];
        }

        for(int k{0}; k<n; k++) {
            cin >> b[k];
        }

        if (n==1) {
            if (A[0]==0.0){
                cout << "?" << endl;
            } else {
                cout << b[0]/A[0] << endl;
            }
            continue;
        }

        vector<double> combined = flatten_vectors(A, b, n);
        rref(combined, n+1);
        // print_A(combined, n+1);
        string s = "";
        s = is_solvable(combined, n+1);
        if (s=="-1") {
            cout << "inconsistent" << std::endl;
        } else if (s=="-2") {
            // cout << "multiple" << endl;
            auto result = find_unkown_variables(combined, n+1);
            copy(result.begin(), result.end(), ostream_iterator<string>{cout, " "});
            cout << endl;
            // cout << "tmp " << endl;
        } else {
            cout << s << std::endl;
        }
    }
}