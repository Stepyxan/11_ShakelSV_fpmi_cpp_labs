#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    double d;
    std::cin >> d;
    double mx = d, mn = d, av = d;
    for (int i = 1; i < n; i++) {
        std::cin >> d;
        if (d > mx) {
            mx = d;
        }
        if (d < mn) {
            mn = d;
        }
        av += d;
    }
    std::cout << av / n << ' ' << mn << ' ' << mx;
}