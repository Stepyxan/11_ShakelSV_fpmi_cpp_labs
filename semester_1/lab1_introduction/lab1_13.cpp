#include <iostream>

int main()
{
    int n;
    if (!(std::cin >> n) || n < 0) {
        std::cout << "error";
        std::exit(1);
    }
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