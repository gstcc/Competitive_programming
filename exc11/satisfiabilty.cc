#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

class expr {
public:
    expr(int n, string s) {
        istringstream iss(s);
        string tmp;
        while (iss >> tmp) {
            int var;
            if (tmp == "v") {
                continue;
            } else if (tmp.front() == '~') {
                var = stoi(tmp.substr(2)) - 1; // Convert x1 to index 0
            } else {
                var = stoi(tmp.substr(1)) - 1;
            }
            variables.push_back({var, tmp.front()=='~'});;
        }
    }

    bool satisfies(unsigned int n) const {
        for (auto [v, negated] : variables) {
            bool val = (n >> v) & 1;
            bool res = (negated ? !val : val);
            if (res) return true;
        }
        return false;
    }

private:
    vector<pair<int, bool>> variables;
};

int main() {
    int T, n, m;
    string s;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        cin.ignore(); // Discard the remaining newline

        vector<expr> clauses;
        for (int i = 0; i < m; i++) {
            getline(cin, s);
            expr exp(n, s);
            clauses.push_back(exp);
        }

        unsigned int max_val = (1u << n);
        bool found = false;

        for (unsigned int v = 0; v < max_val; v++) {
            bool satisfiable = true;
            for (auto const& c : clauses) {
                if (!c.satisfies(v)) {
                    satisfiable = false;
                    break;
                }
            }
            if (satisfiable) {
                cout << "satisfiable" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "unsatisfiable" << endl;
        }
    }
}

