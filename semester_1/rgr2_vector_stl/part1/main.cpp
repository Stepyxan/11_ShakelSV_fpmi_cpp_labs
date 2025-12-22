#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void EnterVector(std::vector<int>& numbers);
void PrintVector(const std::vector<int>& numbers);
int VectorSum(const std::vector<int>& numbers);
int EqualCount(const std::vector<int>& numbers, int value);
int CountGreater(const std::vector<int>& numbers, int n);
void ReplaceZerosWithAverage(std::vector<int>& numbers);
void AddIntervSumToElems(std::vector<int>& numbers, int l, int r);
void ReplaceEvenAbs(std::vector<int>& numbers);
bool AlreadyInVector(std::vector<int>& in_vector, int value);
void DeleteAbsDuplicates(std::vector<int>& numbers);

int main() {
    std::vector<int> numbers;
    EnterVector(numbers);
    std::cout << "The resulting vector:\n";
    PrintVector(numbers);

    int sum = VectorSum(numbers);
    std::cout << "Sum of vector elements = " << sum << '\n';
    
    std::cout << "Amount of vector elements: " << numbers.size() << '\n';

    int value = 10;
    std::cout << "Amount of elements are equal " << value << " : "
        << EqualCount(numbers, value) << '\n';
    
    int n = 10;
    std::cout << "Amount of elements are bigger than " << n << " : "
        << CountGreater(numbers, n) << '\n';
    
    ReplaceZerosWithAverage(numbers);
    std::cout << "Vector after replacing zeros with elems average: \n";
    PrintVector(numbers);
    
    int l = 0, r = 2;
    AddIntervSumToElems(numbers, l, r);
    std::cout << "Vector after adding the sum of the range elements ["
        << l << ", " << r << "] to each element:\n";
    PrintVector(numbers);

    ReplaceEvenAbs(numbers);
    std::cout << "Vector after replacing even numbers with max and min elements difference:\n";
    PrintVector(numbers);

    DeleteAbsDuplicates(numbers);
    std::cout << "Vector after deleting duplicates by abs:\n";
    PrintVector(numbers);
}

void EnterVector(std::vector<int>& numbers) {
    std::cout << "Enter vector elements:\n";
    int num;
    while (std::cin >> num) {
        numbers.push_back(num);
    }
} 

void PrintVector(const std::vector<int>& numbers) {
    std::cout << '[';
    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i];
        if (i < numbers.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ']';
    std::cout << std::endl;
}

int VectorSum(const std::vector<int>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

int EqualCount(const std::vector<int>& numbers, int value) {
    return std::count(numbers.begin(), numbers.end(), value);
}

int CountGreater(const std::vector<int>& numbers, int n) {
    return std::count_if(numbers.begin(), numbers.end(), [n](int num) {return num > n;});
}

void ReplaceZerosWithAverage(std::vector<int>& numbers) {
    int average = VectorSum(numbers) / (numbers.empty() ? 1 : numbers.size());
    std::replace_if(numbers.begin(), numbers.end(), [](int num) {return num == 0;}, average);
}

void AddIntervSumToElems(std::vector<int>& numbers, int l, int r) {
    if (l > r) {
        std::swap(l, r);
    }
    if (l < 0 || r >= numbers.size()) {
        return;
    }
    int interv_sum = std::accumulate(numbers.begin() + l, numbers.begin() + r + 1, 0);
    for (int& num : numbers) {
        num += interv_sum;
    }
}

void ReplaceEvenAbs(std::vector<int>& numbers) {
    if (numbers.empty()) {
        return;
    }
    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());
    int diff = max - min;
    std::replace_if(numbers.begin(), numbers.end(), [&](int num) {return std::abs(num) % 2 == 0;}, diff);
}

bool AlreadyInVector(std::vector<int>& in_vector, int value) {
    if (std::find(in_vector.begin(), in_vector.end(), std::abs(value)) != in_vector.end()) {
        return true;
    }
    in_vector.push_back(std::abs(value));
    return false;
}

void DeleteAbsDuplicates(std::vector<int>& numbers) {
    std::vector<int> in_vector;
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
        [&](int num) {return AlreadyInVector(in_vector, num);}), numbers.end());
}