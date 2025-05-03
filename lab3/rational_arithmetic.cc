#include <iostream>
#include <numeric>
#include <ostream>
#include <string>
#include <cmath>

using namespace std;

int lcm(int a, int b)
{
    return std::abs(a * b) / std::gcd(a, b);
}

class ArithmeticOperation
{
  public:
    int x, y;
    ArithmeticOperation() : x{}, y{}
    {
    }

    ArithmeticOperation(int x, int y)
    {
        int g = gcd(abs(x), abs(y));
        x /= g;
        y /= g;
        if (y < 0)
        {
            x = -x;
            y = -y;
        }
        this->x = x;
        this->y = y;
    }

    ArithmeticOperation operator+(const ArithmeticOperation &other) const
    {
        int lcd = lcm(y, other.y);
        int lhs_num = lcd / y * x;
        int rhs_num = lcd / other.y * other.x;
        int num = lhs_num + rhs_num;
        int g = gcd(num, lcd);
        return ArithmeticOperation(num / g, lcd / g);
    }

    ArithmeticOperation operator-(const ArithmeticOperation &other) const
    {
        return *this + ArithmeticOperation(-other.x, other.y);
    }

    ArithmeticOperation operator*(const ArithmeticOperation &other) const
    {
        int num = x * other.x;
        int denom = y * other.y;
        int g = gcd(num, denom);
        return ArithmeticOperation(num / g, denom / g);
    }

    ArithmeticOperation operator/(const ArithmeticOperation &other) const
    {
        return *this * ArithmeticOperation(other.y, other.x);
    }

    void print() const
    {
        if (y < 0)
        {
            cout << -x << " / " << -y << endl;
        }
        else
        {
            cout << x << " / " << y << endl;
        }
    }
};

int main()
{
    int n, x1, y1, x2, y2;
    string op;
    cin >> n;
    while (n--)
    {
        cin >> x1 >> y1 >> op >> x2 >> y2;
        ArithmeticOperation lhs(x1, y1), rhs(x2, y2), result{};
        if (op == "+")
            result = lhs + rhs;
        else if (op == "-")
            result = lhs - rhs;
        else if (op == "*")
            result = lhs * rhs;
        else if (op == "/")
            result = lhs / rhs;
        result.print();
    }
}
