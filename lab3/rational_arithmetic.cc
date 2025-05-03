/*
* Gustav Carlsosn (gusca083)
* Time complexity O(log(A)), space O(1), where a is the maximum number of x1, x2, y1, y2
* Does rational arithmetics, the division utilizes the multiplication operator
* but reverts the right hand side
* Assumes that y1, y2, x2 are not zero
*/

#include <iostream>
#include <numeric>
#include <string>
#include <cmath>

using namespace std;

long long lcm(long long a, long long b)
{
    return std::abs(a * b) / std::gcd(a, b);
}

class ArithmeticOperation
{
  public:
    long long x, y;

    ArithmeticOperation() : x(0), y(1) {}

    ArithmeticOperation(long long x, long long y)
    {
        if (y < 0) {
            x = -x;
            y = -y;
        }

        long long g = gcd(abs(x), abs(y));
        this->x = x / g;
        this->y = y / g;
    }

    ArithmeticOperation operator+(const ArithmeticOperation &other) const
    {
        long long lcd = lcm(y, other.y);
        long long lhs_num = lcd / y * x;
        long long rhs_num = lcd / other.y * other.x;
        return ArithmeticOperation(lhs_num + rhs_num, lcd);
    }

    ArithmeticOperation operator-(const ArithmeticOperation &other) const
    {
        return *this + ArithmeticOperation(-other.x, other.y);
    }

    ArithmeticOperation operator*(const ArithmeticOperation &other) const
    {
        long long num = x * other.x;
        long long denom = y * other.y;
        return ArithmeticOperation(num, denom);
    }

    ArithmeticOperation operator/(const ArithmeticOperation &other) const
    {
        return *this * ArithmeticOperation(other.y, other.x);
    }

    void print() const
    {
        cout << x << " / " << y << endl;
    }
};

int main()
{
    int n;
    cin >> n;

    long long x1, y1, x2, y2;
    char op;

    while (n--)
    {
        cin >> x1 >> y1 >> op >> x2 >> y2;
        ArithmeticOperation lhs(x1, y1);
        ArithmeticOperation rhs(x2, y2);
        ArithmeticOperation result;

        if (op == '+')
            result = lhs + rhs;
        else if (op == '-')
            result = lhs - rhs;
        else if (op == '*')
            result = lhs * rhs;
        else if (op == '/')
            result = lhs / rhs;

        result.print();
    }

    return 0;
}

