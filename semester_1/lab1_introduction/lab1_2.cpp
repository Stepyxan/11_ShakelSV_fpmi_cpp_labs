#include <iostream>

int main()
{
    long long n, even_sum = 0, odd_mult = 1;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i % 2) {
            odd_mult *= i;
        }
        else {
            even_sum += i;
        }
    }
    std::cout << even_sum << ' ' << odd_mult;
}