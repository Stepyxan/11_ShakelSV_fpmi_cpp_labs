#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool IsEmptyFile(std::ifstream& file);
std::vector<std::string> ReadDataFromFile(const std::string input_file);
bool IsRussianLetter(char letter);
int CurMaxChainFind(const std::string line);
int MaxChainSearch(const std::vector<std::string>& file_lines);
std::vector<int> FindMaxChainLines(const std::vector<std::string>& file_lines, int max_chain);
void WriteResultData(const std::vector<std::string>& file_lines, const std::vector<int>& chain_counter);

int main() {
    try {       
        setlocale(LC_ALL, "1251");
        const std::string input_file("input.txt");
        std::vector<std::string> file_lines = ReadDataFromFile(input_file);
        int max_chain = MaxChainSearch(file_lines);
        std::vector<int> chain_counter = FindMaxChainLines(file_lines, max_chain);
        WriteResultData(file_lines, chain_counter);
    }
    catch (const std::string message) {
        std::cerr << message << std::endl;
    }
}

bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == EOF;
}

std::vector<std::string> ReadDataFromFile(const std::string input_file) {
    std::ifstream in(input_file);
    if (!in.is_open()) {
        throw "Error: could not open file \\" + input_file + "\\";
    }
    if (IsEmptyFile(in)) {
        throw "Error: file \\" + input_file + "\\ is empty";
    }
    std::vector<std::string> input_strings;
    std::string temp_string;
    while (std::getline(in, temp_string)) {
        input_strings.push_back(temp_string);
    }
    in.close();
    return input_strings;
}

bool IsRussianLetter(char ch) {
    ch = std::tolower((unsigned char)ch);
    return (ch >= char(-32) && ch <= char(-1)) || ch == char(-72);
}

int CurMaxChainFind(const std::string line) {
    int max_length = 0;
    int cur_length = 0;
    char prev_ch = ' ';
    for (int i = 0; i < line.length(); i++) {
        if (IsRussianLetter(line[i])) {
            char cur_ch = std::tolower((unsigned char)line[i]);
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
            prev_ch = ' ';
        }
    }
    return max_length;
}

int MaxChainSearch(const std::vector<std::string>& file_lines) {
    int max_chain = 0;
    int cur_chain = 0;
    int lines_count = file_lines.size();
    for (int i = 0; i < lines_count; i++) {
        cur_chain = CurMaxChainFind(file_lines[i]);
        if (max_chain < cur_chain) {
            max_chain = cur_chain;
        }
    }
    return max_chain;
}

std::vector<int> FindMaxChainLines(const std::vector<std::string>& file_lines, int max_chain) {
    std::vector<int> result_lines_numbers;
    int lines_count = file_lines.size();
    int counter = 0;
    for (int i = 0; i < lines_count; i++) {
        if (max_chain == CurMaxChainFind(file_lines[i]) && counter < 10) {
            counter++;
            result_lines_numbers.push_back(i);
        }
    }
    return result_lines_numbers;
}

void WriteResultData(const std::vector<std::string>& file_lines, const std::vector<int>& chain_counter) {
    int lines_count = chain_counter.size();
    std::cout << "lines with the maximum number of same Russian characters:" << std::endl;
    for (int i = 0; i < lines_count; i++) {
        std::cout << file_lines[chain_counter[i]] << std::endl;
    }
}