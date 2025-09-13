#include <iostream>

int main()
{
    int n;
    if (!(std::cin >> n) || !(1000 <= n && n <= 9999)) {
        std::cout << "error";
        std::exit(1);
    }
    if (n / 1000 == n % 10 && n / 100 % 10 == n / 10 % 10) {
        std::cout << "Palindrome";
    }
    else {
        std::cout << "Not palindrome";
    }
}
