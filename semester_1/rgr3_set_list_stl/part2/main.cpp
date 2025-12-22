#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Author {
    std::string last_name_;
    std::string first_name_;
    std::string patronymic_;

    bool operator<(const Author& rhs) const {
        return last_name_ < rhs.last_name_;
    }

    bool operator==(const Author& rhs) const {
        return last_name_ == rhs.last_name_ &&
            first_name_ == rhs.first_name_ &&
            patronymic_ == rhs.patronymic_;
}

};

struct Book {
    int udc_;
    std::string title_;
    int year_;
    std::list<Author> authors_;

    bool operator<(const Book& rhs) const {
        return title_ < rhs.title_;
    }

    void PrintBook() const {
        std::cout << "UDC: " << udc_ << "\n" 
            << "Title: " << title_ << "\n" 
            << "Year: " << year_ << "\n" 
            << "Authors:\n";
        for (const auto& a : authors_) {
            std::cout << " " << a.last_name_ << " " << a.first_name_ << " " << a.patronymic_ << "\n"; 
        }
        std::cout << "\n";
    }
};

class Library {
private:
    std::list<Book> books;

public:
    void AddBook(const Book& book) {
        books.push_back(book);
        books.sort();
    }

    void DeleteBookByTitle(const std::string& book_name) {
        std::list<Book>::iterator iter = std::find_if(books.begin(), books.end(),
            [&](const Book& book) {return book.title_ == book_name;});
        if (iter != books.end()) {
            books.erase(iter);
            std::cout << "Book " << book_name << " deleted successfully\n";
        }
        else {
            std::cout << "There is no book with this title in library\n";
        }
    }

    void AddBookAuthor(const std::string& book_name, const Author& author) {
        for (Book& book : books) {
            if (book.title_ == book_name) {
                book.authors_.push_back(author);
                book.authors_.sort();
            }
        }
    }

    void DeleteBookAuthor(const std::string& book_name, const Author& author) {
        for (Book& book : books) {
            if (book.title_ == book_name) {
                book.authors_.remove(author);
            }
        }
    }

    void SearchBookByTitle(const std::string& title) const {
        std::cout << "Books with title " << title << " :\n";
        for (const Book& book : books) {
            if (book.title_ == title) {
                book.PrintBook();
            }
        }
    }

    void SearchBookByAuthor(const Author& author) const {
        std::cout << "Books from author " << author .last_name_ << " :\n";
        for (const Book& book : books) {
            if (std::find(book.authors_.begin(), book.authors_.end(), author) != book.authors_.end()) {
                book.PrintBook();
            }
        }
    }

    void PrintAllBooks() const {
        if (books.empty()) {
            std::cout << "Library is empty\n;";
            return;
        }
        for (const Book& book : books) {
            book.PrintBook();
        }
    }
};


void InputCheck(std::ifstream& fin) {
    if (!fin.is_open()) {
        throw "Error: Cannot open input file\n";
    }
    if (fin.peek() == EOF) {
        throw "Error: Input file is empty\n";
    }
}

Author StringToAuthor(const std::string line) {
    std::istringstream iss(line);
    Author author;
    iss >> author.last_name_ >> author.first_name_ >> author.patronymic_;
    return author;
}


int main() {
    std::ifstream fin("input.txt");
    try {
        InputCheck(fin);
    }
    catch (const char* message) {
        std::cerr << message;
        return 1;
    }

    Library lib;
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) {
            continue;
        }
        Book new_book;
        new_book.udc_ = std::stoi(line);
        if (!std::getline(fin, new_book.title_)) {
            break;
        }
        if (!std::getline(fin, line)) {
            break;
        }
        new_book.year_ = std::stoi(line);
        while (std::getline(fin, line)) {
            if (line.empty()) {
                break;
            }
            Author author = StringToAuthor(line);
            new_book.authors_.push_back(author);
        }
        new_book.authors_.sort();
        lib.AddBook(new_book);
    } 
    std::cout << "Your lib after file reading:\n";
    lib.PrintAllBooks();

    Book new_book{123, "New Book", 2025, {{"Petrov", "Ivan", "Ivanovich"}}};
    std::cout << "New book to add:\n";
    new_book.PrintBook();

    lib.AddBook(new_book);
    std::cout << "Lib after added new book:\n";
    lib.PrintAllBooks();

    std::string title = "New Book";
    lib.SearchBookByTitle(title);

    Author new_author{"Pavlov", "Pavel", "Pavlovich"};
    std::cout << "New author was added:\n";
    lib.AddBookAuthor(title, new_author);
    lib.SearchBookByTitle(title);
    
    std::cout << "New author was deleted:\n";
    lib.DeleteBookAuthor(title, new_author);
    lib.SearchBookByTitle(title);

    Author search_author{"Petrov", "Ivan", "Ivanovich"};
    lib.SearchBookByAuthor(search_author);

    std::cout << "Library after New book deleting:\n";
    lib.DeleteBookByTitle("New Book"); 
    lib.PrintAllBooks();
}
