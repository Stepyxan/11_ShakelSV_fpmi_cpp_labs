#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    if (n == 0 || n == 1) {
        std::cout << n;
    }
    else {
        int f1 = 0, f2 = 1;
        int temp;
        for (int i = 2; i <= n; i++) {
            temp = f2;
            f2 = f1 + f2;
            f1 = temp;
        }
        std::cout << f2;
    }
}