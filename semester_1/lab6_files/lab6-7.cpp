#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>

bool IsEmptyFile(std::wifstream& file);
std::vector<std::wstring> ReadDataFromFile(const std::string& input_file);
wchar_t ToLowerRussian(wchar_t ch);
bool IsRussianLetter(wchar_t letter);
int CurMaxChainFind(const std::wstring line);
int MaxChainSearch(const std::vector<std::wstring>& file_lines);
std::vector<int> FindMaxChainLines(const std::vector<std::wstring>& file_lines, int max_chain);
void WriteResultData(const std::vector<std::wstring>& file_lines, const std::vector<int>& chain_counter);

int main() {
    try {
        std::locale loc;
        try {
            loc = std::locale("ru_RU.UTF-8");
        }
        catch (...) {
            loc = std::locale("");
        }
        std::locale::global(loc);
        std::wcout.imbue(loc);

        const std::string input_file("input.txt");
        std::vector<std::wstring> file_lines = ReadDataFromFile(input_file);
        int max_chain = MaxChainSearch(file_lines);
        std::vector<int> chain_counter = FindMaxChainLines(file_lines, max_chain);
        WriteResultData(file_lines, chain_counter);
    }
    catch (const std::string& message) {
        std::cerr << message << std::endl;
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}

bool IsEmptyFile(std::wifstream& file) {
    return file.peek() == WEOF;
}

std::vector<std::wstring> ReadDataFromFile(const std::string& input_file) {
    std::wifstream in(input_file);
    in.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (!in.is_open()) {
        throw std::string("Error: could not open file \"") + input_file + "\"";
    }
    if (IsEmptyFile(in)) {
        throw std::string("Error: file \"") + input_file + "\" is empty";
    }

    std::vector<std::wstring> input_strings;
    std::wstring temp_string;

    while (std::getline(in, temp_string)) {
        input_strings.push_back(temp_string);
    }
    in.close();

    return input_strings;
}

wchar_t ToLowerRussian(wchar_t ch) {
    if (ch >= L'А' && ch <= L'Я') {
        return (wchar_t)(ch + 32);
    }
    if (ch == L'Ё') {
        return L'ё';
    }
    return ch;
}

bool IsRussianLetter(wchar_t ch) {
    wchar_t lower = ToLowerRussian(ch);
    return (lower >= L'а' && lower <= L'я') || (lower == L'ё');
}

int CurMaxChainFind(const std::wstring line) {
    int max_length = 0;
    int cur_length = 0;
    wchar_t prev_ch = L'\0';
    for (size_t i = 0; i < line.length(); i++) {
        if (IsRussianLetter(line[i])) {
            wchar_t cur_ch = ToLowerRussian(line[i]);

            if (cur_ch == prev_ch) {
                cur_length++;
            }
            else {
                cur_length = 1;
                prev_ch = cur_ch;
            }

            if (cur_length > max_length) {
                max_length = cur_length;
            }
        }
        else {
            cur_length = 0;
            prev_ch = L'\0';
        }
    }
    return max_length;
}

int MaxChainSearch(const std::vector<std::wstring>& file_lines) {
    int max_chain = 0;
    for (const auto& line : file_lines) {
        int cur_chain = CurMaxChainFind(line);
        if (max_chain < cur_chain) {
            max_chain = cur_chain;
        }
    }
    return max_chain;
}


std::vector<int> FindMaxChainLines(const std::vector<std::wstring>& file_lines, int max_chain) {
    std::vector<int> result_lines_numbers;
    int counter = 0;
    for (size_t i = 0; i < file_lines.size(); i++) {
        if (CurMaxChainFind(file_lines[i]) == max_chain && counter < 10) {
            result_lines_numbers.push_back((int)i);
            counter++;
        }
    }
    return result_lines_numbers;
}

void WriteResultData(const std::vector<std::wstring>& file_lines,
    const std::vector<int>& chain_counter) {
    std::wcout << L"Lines with the maximum number of same Russian characters:\n";

    for (int idx : chain_counter) {
        std::wcout << file_lines[idx] << L"\n";
    }
}
