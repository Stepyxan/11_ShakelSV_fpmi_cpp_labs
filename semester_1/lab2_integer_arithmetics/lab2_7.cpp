#include <iostream>
#include <cmath>
int main()
{
    int n;
    if (!(std::cin >> n) || n < 1) {
        std::cout << "error";
        std::exit(1);
    }
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            int c_sqr = a * a + b * b;
            int c = sqrt(c_sqr);
            if (c <= n && c * c == c_sqr) {
                std::cout << a << ' ' << b << ' ' << c << '\n';
            }
        }
    }
}