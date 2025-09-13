#include <iostream>

int main()
{
    int n;
    double d;
    if (!(std::cin >> n >> d) || !(n > 0)) {
        std::cout << "error";
        std::exit(1);
    }
    double mx = d, mn = d, av = d;
    for (int i = 1; i < n; i++) {
        if (!(std::cin >> d)) {
            std::cout << "error";
            std::exit(1);
        }
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