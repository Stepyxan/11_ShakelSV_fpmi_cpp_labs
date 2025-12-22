#include <iostream>
#include <vector>
#include <set>

std::set<int> compute_primes(int n) {
    std::set<int> primes;
    std::vector<bool> is_prime(n + 1);
    for (int i = 2; i <= n; ++i) {
        is_prime[i] = true;
    }
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.insert(i);
        }
        for (int j = i * i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }
    return primes;
}

int main() {
    int n;
    std::cout << "Input a natural number N: \n";
    if (!(std::cin >> n) || (n < 1)) {
        std::cerr << "Error: N must be natural";
        std::exit(1);
    }
    std::set<int> primes = compute_primes(n);
    std::cout << "Primes no greater than N: \n";
    for(std::set<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
        std::cout << *it << ' ';
    }
}