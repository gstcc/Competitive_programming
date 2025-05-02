
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

const double EPS = 1e-5;

bool equal(double a, double b) {
    return fabs(a - b) < EPS;
}

void print_A(vector<double> const& A, int n) {
    int index = 0;
    for (double el : A) {
        cout << el << " ";
        index++;
        if (index % n == 0) {
            cout << endl;
        }
    }
}

void reduce_row(vector<double> &A, int n, int index) {
    double factor = A[index];
    if (equal(factor, 0)) return;
    for (int i = index; i < index + n; i++) {
        A[i] /= factor;
    }
}

void row_subtraction(vector<double> &A, int n, int first_row, int second_row, int col) {
    double factor = A[second_row * n + col];
    for (int i = 0; i < n; i++) {
        A[second_row * n + i] -= factor * A[first_row * n + i];
    }
}

void swap_row(vector<double> &A, int n, int first_row, int second_row) {
    for (int c = 0; c < n; c++) {
        swap(A[first_row * n + c], A[second_row * n + c]);
    }
}

void rref(vector<double> &A, int n) {
    int row = 0;
    for (int col = 0; col < n - 1 && row < n - 1; col++) {
        int sel = -1;
        for (int i = row; i < n - 1; i++) {
            if (!equal(A[i * n + col], 0)) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;
        if (sel != row) swap_row(A, n, row, sel);
        reduce_row(A, n, row * n + col);
        for (int i = 0; i < n - 1; i++) {
            if (i != row && !equal(A[i * n + col], 0)) {
                row_subtraction(A, n, row, i, col);
            }
        }
        row++;
    }
}

vector<pair<int, int>> list_pivots(vector<double> const& A, int n) {
    vector<pair<int, int>> res;
    for (int r = 0; r < n - 1; r++) {
        int c = 0;
        while (c < n - 1 && equal(A[r * n + c], 0)) c++;
        if (c != n - 1) res.emplace_back(r, c);
    }
    sort(res.rbegin(), res.rend());
    return res;
}

bool check_inconsistent(vector<double> const& A, int n) {
    for (int r = 0; r < n - 1; r++) {
        bool all_zero = true;
        for (int c = 0; c < n - 1; c++) {
            if (!equal(A[r * n + c], 0)) {
                all_zero = false;
                break;
            }
        }
        if (all_zero && !equal(A[r * n + (n - 1)], 0)) {
            return true; // Inconsistent
        }
    }
    return false;
}

string is_solvable(vector<double> const& A, int n) {
    if (check_inconsistent(A, n)) {
        return "-1"; // inconsistent
    }
    auto pivots = list_pivots(A, n);
    if (pivots.size() < n - 1) {
        return "-2"; // multiple solutions
    }
    ostringstream oss;
    for (int r = 0; r < n - 1; r++) {
        oss << fixed << setprecision(2) << A[r * n + (n - 1)] << " ";
    }
    return oss.str();
}

vector<string> find_unknown_variables(vector<double> const& A, int n) {
    vector<string> variables(n - 1, "?");
    for (int r = 0; r < n - 1; r++) {
        int leading_col = -1;
        for (int c = 0; c < n - 1; c++) {
            if (!equal(A[r * n + c], 0)) {
                if (leading_col == -1) leading_col = c;
                else {
                    leading_col = -2; // multiple nonzero
                    break;
                }
            }
        }
        if (leading_col >= 0) {
            variables[leading_col] = to_string(A[r * n + (n - 1)]);
        }
    }
    return variables;
}

vector<double> flatten_vectors(vector<double> const& A, vector<double> const& b, int n) {
    vector<double> combined;
    int b_index = 0;
    for (int i = 0; i < A.size(); i++) {
        if (i % n == 0 && i != 0) {
            combined.push_back(b[b_index++]);
        }
        combined.push_back(A[i]);
    }
    combined.push_back(b[b_index]);
    return combined;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<double> A(n * n);
        vector<double> b(n);

        for (int i = 0; i < n * n; i++) cin >> A[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        if (n == 1) {
            if (equal(A[0], 0.0)) cout << "?" << endl;
            else cout << fixed << setprecision(2) << b[0] / A[0] << endl;
            continue;
        }

        vector<double> combined = flatten_vectors(A, b, n);
        rref(combined, n + 1);

        string s = is_solvable(combined, n + 1);
        if (s == "-1") {
            cout << "inconsistent" << endl;
        } else if (s == "-2") {
            auto result = find_unknown_variables(combined, n + 1);
            for (const string& str : result) cout << str << " ";
            cout << endl;
        } else {
            cout << s << endl;
        }
    }
}

