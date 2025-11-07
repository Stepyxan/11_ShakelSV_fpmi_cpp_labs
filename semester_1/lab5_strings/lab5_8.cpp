#include <iostream>
#include <string>

bool is_digit(char ch);
void string_input(std::string &str);
bool is_digits_only(const std::string &word);
void string_transform(std::string &str);

int main() {
    try {
        std::string str;
        string_input(str);
        string_transform(str);
        std::cout << "Your string after transformation:\n" << str;
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
    }
}

void string_transform(std::string &str) {
    int string_size = str.size();
    int insert_start_index = 0;
    while (insert_start_index < string_size && str[insert_start_index] == ' ') {
        ++insert_start_index;
    }
    if (insert_start_index == string_size) {
        throw "Error! Your string does not contain words";
    }
    int word_start_index = 0, word_end_index = 0;
    int i = insert_start_index;
    while (i < string_size) {
        word_start_index = i;
        while (i < string_size && str[i] != ' ') {
            ++i;
        }
        word_end_index = i;
        std::string word = str.std::string::substr(word_start_index, word_end_index - word_start_index);
        if (is_digits_only(word) && !word.empty()) {
            str.std::string::erase(word_start_index, word_end_index - word_start_index + 1);
            str.std::string::insert(insert_start_index, word + ' ');
            insert_start_index += word_end_index - word_start_index + 1;
        }
        else {
            ++i;
        }
    }
}

void string_input(std::string &str) {
    std::cout << "Enter string you want to transform:\n";
    std::getline(std::cin, str);
    if (str.empty()) {
        throw "Error! Your string is empty";
    }
}

bool is_digit(char ch) {
    if ('0' <= ch && ch <= '9') {
        return true;
    }
    else {
        return false;
    }
}

bool is_digits_only(const std::string &word) {
    for (char ch: word) {
        if (!is_digit(ch)) {
            return false;
        }
    }
    return true;
}