#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    if (n / 1000 == n % 10 && n / 100 % 10 == n / 10 % 10) {
        std::cout << "Palindrome";
    }
    else {
        std::cout << "Not palindrome";
    }
}
