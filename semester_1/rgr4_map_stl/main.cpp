#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <limits>

struct Mark {
    std::string subject_;
    size_t mark_;

    Mark(const std::string& subject = "", size_t mark = 0)
        : subject_(subject), mark_(mark) {
    }

    bool isFailedMark() const {
        return mark_ >= 1 && mark_ <= 3;
    }
};

struct StudentData {
    std::string name_;
    size_t number_;
    std::vector<Mark> marks_;

    StudentData(const std::string& name = "", size_t number = 0)
        : name_(name), number_(number) {
    }

    void addMark(const Mark& mark) {
        marks_.push_back(mark);
    }

    void printData() const {
        std::cout << "[" << name_ << ", " << number_ << "] :\n";
        for (const Mark& mark : marks_) {
            std::cout << mark.subject_ << " - " << mark.mark_ << " ";
        }
    }

    double calculateAverage() const {
        if (marks_.empty()) {
            return 0.0;
        }
        double sum = 0.0;
        for (const Mark& mark : marks_) {
            sum += mark.mark_;
        }
        return sum / marks_.size();
    }

    bool hasSubject(const std::string& subject) const {
        for (const Mark& mark : marks_) {
            if (subject == mark.subject_) {
                return true;
            }
        }
        return false;
    }

    size_t getMarkForSubject(const std::string& subject) const {
        for (const Mark& mark : marks_) {
            if (subject == mark.subject_) {
                return mark.mark_;
            }
        }
        return 0;
    }

    size_t getGradeSum() const {
        size_t current_sum = 0;
        for (const Mark& mark : marks_) {
            current_sum += mark.mark_;
        }
        return current_sum;
    }

    bool hasFailedGrades() const {
        for (const Mark& mark : marks_) {
            if (mark.isFailedMark()) {
                return true;
            }
        }
        return false;
    }

    std::vector<Mark> getFailedMarks() const {
        std::vector<Mark> result;
        for (const Mark& mark : marks_) {
            if (mark.isFailedMark()) {
                result.push_back(mark);
            }
        }
        return result;
    }
};

void inputCheck(std::ifstream& fin);
std::map<size_t, StudentData> readDataFromFile(const std::string& file);
void printDataSortedByNumber(const std::map<size_t, StudentData>& record_books);
void calculateAndPrintAverages(const std::map<size_t, StudentData>& record_books);
std::vector<const StudentData*> getStudentsSortedAlphabetOrder(const std::map<size_t, StudentData>& record_books);
void printAlphabeticalOrder(const std::map<size_t, StudentData>& record_books);
std::vector<std::pair<double, const StudentData*>> getStudentsSortedByGradeDesc(const std::map<size_t, StudentData>& record_books);
std::pair<double, double> getCorrectRangeBorders();
void printStudentsInScoreRange(const std::map<size_t, StudentData>& record_books, double min_grade, double max_grade);
void printStudentsByPassedSubject(const std::map<size_t, StudentData>& record_books, const std::string& subject);
void printSubjectsStatistics(const std::map<size_t, StudentData>& record_books);
void printSubjectsAverages(const std::map<size_t, StudentData>& record_books);
void printStudentsWithMaxGradeSum(const std::map<size_t, StudentData>& record_books);
void printStudentsWithFailedGrades(const std::map<size_t, StudentData>& record_books);

int main() {
    std::string input_file("input.txt");
    std::map<size_t, StudentData> record_books = readDataFromFile(input_file);
    if (record_books.empty()) {
        std::cerr << "Error: No data loaded from file\n";
        return 1;
    }
    printDataSortedByNumber(record_books);
    calculateAndPrintAverages(record_books);
    printAlphabeticalOrder(record_books);

    std::pair<double, double> range = getCorrectRangeBorders();
    double min_grade = range.first;
    double max_grade = range.second;
    printStudentsInScoreRange(record_books, min_grade, max_grade);

    std::cout << "Enter subject title to search: ";
    std::string subject;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, subject);
    printStudentsByPassedSubject(record_books, subject);

    printSubjectsStatistics(record_books);
    printSubjectsAverages(record_books);
    printStudentsWithMaxGradeSum(record_books);
    printStudentsWithFailedGrades(record_books);
}

void inputCheck(std::ifstream& fin) {
    if (!fin.is_open()) {
        throw "Error: Cannot open input file\n";
    }
    if (fin.peek() == EOF) {
        throw "Error: Input file is empty\n";
    }
}

std::map<size_t, StudentData> readDataFromFile(const std::string& file) {
    std::map<size_t, StudentData> record_books;
    std::ifstream fin(file);

    try {
        inputCheck(fin);
    }
    catch (const char* message) {
        std::cerr << message;
        fin.close();
        return record_books;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name;
        size_t number;
        iss >> name >> number;
        StudentData record_book(name, number);
        std::string subject;
        size_t mark;
        while (iss >> subject >> mark) {
            if (mark >= 1 && mark <= 10) {
                record_book.addMark(Mark(subject, mark));
            }
        }
        record_books[number] = record_book;
    }

    fin.close();
    return record_books;
}

void printDataSortedByNumber(const std::map<size_t, StudentData>& record_books) {
    std::cout << "Students sorted by record book number:\n";
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        std::cout << "Student : ";
        pair.second.printData();
        std::cout << std::endl;
    }
}

void calculateAndPrintAverages(const std::map<size_t, StudentData>& record_books) {
    std::cout << "Average students scores:\n";
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        double avg_score = pair.second.calculateAverage();
        std::cout << "[" << pair.second.name_ << ", " << pair.second.number_
            << "] : " << std::fixed << std::setprecision(2) << avg_score << std::endl;
    }
}

std::vector<std::pair<double, const StudentData*>> getStudentsSortedByGradeDesc(const std::map<size_t, StudentData>& record_books) {
    std::vector<std::pair<double, const StudentData*>> result;
    for (const std::pair<const size_t, StudentData>& pair : record_books) {
        result.push_back({ pair.second.calculateAverage(), &pair.second });
    }
    std::sort(result.begin(), result.end(),
        [](const std::pair<double, const StudentData*>& a, const std::pair<double, const StudentData*>& b) {
            return a.first > b.first;
        });
    return result;
}

std::vector<const StudentData*> getStudentsSortedAlphabetOrder(const std::map<size_t, StudentData>& record_books) {
    std::vector<const StudentData*> sorted_students;
    for (const std::pair<const size_t, StudentData>& pair : record_books) {
        sorted_students.push_back(&pair.second);
    }
    std::sort(sorted_students.begin(), sorted_students.end(),
        [](const StudentData* a, const StudentData* b) {
            if (a->name_ == b->name_) {
                return a->calculateAverage() > b->calculateAverage();
            }
            return a->name_ < b->name_;
        });
    return sorted_students;
}

void printAlphabeticalOrder(const std::map<size_t, StudentData>& record_books) {
    std::cout << "List of students in alphabetical order:\n";
    std::vector<const StudentData*> sorted_students = getStudentsSortedAlphabetOrder(record_books);
    size_t counter = 1;
    for (const StudentData* student : sorted_students) {
        std::cout << counter++ << ": " << student->name_
            << ", " << student->number_
            << ", " << std::fixed << std::setprecision(2)
            << student->calculateAverage() << std::endl;
    }
}

std::pair<double, double> getCorrectRangeBorders() {
    std::cout << "Enter range borders to search\n";
    double min_grade, max_grade;
    std::cout << "Enter min grade (1.0-10.0): ";   
    if (!(std::cin >> min_grade) || min_grade < 1.0 || min_grade > 10.0) {
        min_grade = 1.0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter max grade (1.0-10.0): ";
    if (!(std::cin >> max_grade) || max_grade < 1.0 || max_grade > 10.0) {
        max_grade = 10.0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (min_grade > max_grade) {
        std::swap(min_grade, max_grade);
    }
    return {min_grade, max_grade};
}

void printStudentsInScoreRange(const std::map<size_t, StudentData>& record_books, double min_grade, double max_grade) {
    std::cout << "Students with average grade from [" << min_grade << "] to [" << max_grade << "]:\n";
    std::vector<std::pair<double, const StudentData*>> sorted_students = getStudentsSortedByGradeDesc(record_books);
    bool found_any = false;
    for (const std::pair<double, const StudentData*>& pair : sorted_students) {
        if (pair.first >= min_grade && pair.first <= max_grade) {
            std::cout << "[" << pair.second->name_ << ", " << pair.second->number_ << "] with average: "
                << std::fixed << std::setprecision(2) << pair.first << "\n";
            found_any = true;
        }
    }
    if (!found_any) {
        std::cout << "No students found in the range ["
            << min_grade << ", " << max_grade << "]\n";
    }
}

void printStudentsByPassedSubject(const std::map<size_t, StudentData>& record_books, const std::string& subject) {
    std::cout << "Students who passed " << subject << ":\n";
    bool subject_found = false;
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        if (pair.second.hasSubject(subject)) {
            size_t mark = pair.second.getMarkForSubject(subject);
            std::cout << "[" << pair.second.name_ << ", " << pair.second.number_ << "] : "
                << subject << " - " << mark << '\n';
            subject_found = true;
        }
    }
    if (!subject_found) {
        std::cout << "Nobody passed " << subject << "\n";
    }
}

void printSubjectsStatistics(const std::map<size_t, StudentData>& record_books) {
    std::cout << "Subjects statistics (number of students per subject):\n";
    std::map<std::string, size_t> subject_count;
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        std::set<std::string> unique_subjects;
        for (const Mark& mark : pair.second.marks_) {
            unique_subjects.insert(mark.subject_);
        }
        for (const std::string& subject : unique_subjects) {
            subject_count[subject]++;
        }
    }
    for (const std::pair<std::string, size_t>& pair : subject_count) {
        std::cout << pair.first << ": " << pair.second << " students\n";
    }
}

void printSubjectsAverages(const std::map<size_t, StudentData>& record_books) {
    std::cout << "Average scores by subject:\n";
    std::map<std::string, std::pair<size_t, size_t>> subjects_statistics;
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        for (const Mark& mark : pair.second.marks_) {
            subjects_statistics[mark.subject_].first += mark.mark_;
            subjects_statistics[mark.subject_].second++;
        }
    }
    std::vector<std::pair<std::string, double>> subject_averages;
    for (const std::pair<std::string, std::pair<size_t, size_t>>& pair : subjects_statistics) {
        double average = static_cast<double>(pair.second.first) / pair.second.second;
        subject_averages.push_back(std::make_pair(pair.first, average));
    }
    std::sort(subject_averages.begin(), subject_averages.end(),
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second > b.second;
        });
    for (const std::pair<std::string, double>& subject : subject_averages) {
        std::cout << subject.first << " : " << std::fixed << std::setprecision(2)
            << subject.second << std::endl;
    }
}

void printStudentsWithMaxGradeSum(const std::map<size_t, StudentData>& record_books) {
    std::cout << "Students with maximum grade sum:\n";
    if (record_books.empty()) {
        std::cout << "No students found\n";
        return;
    }
    size_t max_sum = 0;
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        size_t current_sum = pair.second.getGradeSum();
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    std::cout << "Maximum sum: " << max_sum << "\nStudents:\n";
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        if (pair.second.getGradeSum() == max_sum) {
            std::cout << "[" << pair.second.name_ << ", " << pair.second.number_ << "]\n";
        }
    }
}

void printStudentsWithFailedGrades(const std::map<size_t, StudentData>& record_books) {
    std::cout << "Students with failed grades (1, 2, 3):\n";
    bool student_found = false;
    for (const std::pair<size_t, StudentData>& pair : record_books) {
        if (pair.second.hasFailedGrades()) {
            std::cout << "[" << pair.second.name_ << ", " << pair.second.number_ << "]:\n";
            std::vector<Mark> failed_grades = pair.second.getFailedMarks();
            for (const Mark& mark : failed_grades) {
                std::cout << "  " << mark.subject_ << " - " << mark.mark_ << "\n";
            }
            student_found = true;
        }
    }
    if (!student_found) {
        std::cout << "No students with failed grades found\n";
    }
}