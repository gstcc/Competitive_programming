/*
 * Gustav Carlsosn (gusca083)
 * Time complexity O(log(A)), space O(1), where a is the maximum number of x1, x2, y1, y2
 * Does rational arithmetics, the division utilizes the multiplication operator
 * but reverts the right hand side
 * Assumes that y1, y2, x2 are not zero
 */

#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

long long lcm(long long a, long long b)
{
    return std::abs(a * b) / std::gcd(a, b);
}

class ArithmeticOperation
{
  public:
    long long x, y;

    ArithmeticOperation() : x(0), y(1)
    {
    }

    ArithmeticOperation(long long x, long long y)
    {
        if (y < 0)
        {
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

    bool operator==(const ArithmeticOperation &other) const
    {
        long long d1 = gcd(x, other.y);
        long long d2 = gcd(y, other.x);
        return x/d1 == other.x/d2 && y/d1 == other.y/d2; //Convert to simplest form, so e.g. 1/2 == 2/4
    }

    bool operator!=(const ArithmeticOperation &other) const
    {
        return !(*this == other);
    }

    bool operator<(const ArithmeticOperation &other) const
    {
        return x * other.y < other.x * y;
    }

    bool operator>(const ArithmeticOperation &other) const
    {
        return other < *this;
    }

    bool operator<=(const ArithmeticOperation &other) const
    {
        return !(*this > other) || (*this == other);
    }

    bool operator>=(const ArithmeticOperation &other) const
    {
        return !(*this < other) || (*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, const ArithmeticOperation &a);
    friend std::istream &operator>>(std::istream &is, ArithmeticOperation &a);

};


std::ostream &operator<<(std::ostream &os, const ArithmeticOperation &a)
{
    os << a.x << " / " << a.y;
    return os;
}

std::istream &operator>>(std::istream &is, ArithmeticOperation &a)
{
    long long num, denom;

    is >> num  >> denom;
    a = ArithmeticOperation(num, denom);
    return is;
}

int main()
{
    int n;
    cin >> n;

    long long x1, y1, x2, y2;
    char op;
    /* Tests for checking the operators
    ArithmeticOperation tmp1{1, 4};
    ArithmeticOperation tmp2{2, 8};
    ArithmeticOperation tmp3{2, 5};
    cout << (tmp1 == tmp2) << " " << (tmp1 > tmp2) << " " << (tmp1 < tmp2) << " " << (tmp1 > tmp2) << " " << (tmp1 <= tmp2) << " " << (tmp1 < tmp3) << endl; 
*/
    while (n--)
    {
        // cin >> x1 >> y1 >> op >> x2 >> y2;
        
        ArithmeticOperation lhs;
        ArithmeticOperation rhs;
        ArithmeticOperation result;
        cin >> lhs >> op >> rhs;

        if (op == '+')
            result = lhs + rhs;
        else if (op == '-')
            result = lhs - rhs;
        else if (op == '*')
            result = lhs * rhs;
        else if (op == '/')
            result = lhs / rhs;

        cout << result << endl;
    }

    return 0;
}
