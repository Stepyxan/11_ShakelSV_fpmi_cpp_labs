#include "time_utility.h"
#include "train.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

void InputCheck(std::ifstream& fin);
void PrintTrain(const Train& train);
std::vector<Train> ReadTrains(std::ifstream& fin);
void PrintSortedByDispatch(std::vector<Train>& trains);
void PrintTrainsInRange(const std::vector<Train>& trains, std::time_t t1, std::time_t t2);
void PrintTrainsToDestination(const std::vector<Train>& trains, const std::string& dest);
void PrintTrainsByTypeAndDestination(const std::vector<Train>& trains, int type_int, const std::string& dest);
void PrintFastestTrainToDestination(std::vector<Train>& trains, const std::string& dest);

int main() {
    using namespace time_utility;

    std::ifstream fin("input.txt");
    try {
        InputCheck(fin);
    }
    catch (const char* message) {
        std::cerr << message;
        return 1;
    }

    std::vector<Train> trains = ReadTrains(fin);

    std::cout << "Trains sorted by dispatch time:\n";
    PrintSortedByDispatch(trains);

    std::time_t t1 = SetTime(9, 45);
    std::time_t t2 = SetTime(11, 50);
    std::cout << "Trains in time range from";
    PrintTime(t1);
    std::cout << " to ";
    PrintTime(t2);
    std::cout << ":\n";
    PrintTrainsInRange(trains, t1, t2);

    std::string dest1 = "Minsk";
    std::cout << "Trains to " << dest1 << ":\n";
    PrintTrainsToDestination(trains, dest1);

    int type_int = 0;
    std::cout << "Trains of type " << type_int << " to " << dest1 << ":\n";
    PrintTrainsByTypeAndDestination(trains, type_int, dest1);

    std::cout << "Fastest train to " << dest1 << ":\n";
    PrintFastestTrainToDestination(trains, dest1);

    return EXIT_SUCCESS;
}

void InputCheck(std::ifstream& fin) {
    if (!fin.is_open()) {
        throw "Error: Cannot open input file\n";
    }
    if (fin.peek() == EOF) {
        throw "Error: Input file is empty\n";
    }
}

void PrintTrain(const Train& train) {
    std::cout << "Train: #" << train.getId()
            << " Type: " << static_cast<int>(train.getType())
            << " Destination: " << train.getDestination()
            << " Dispatch: ";
    PrintTime(train.getDispatchTime());
    std::cout << " Travelling time: ";
    PrintTime(train.getTravellingTime());
    std::cout << '\n';
}

std::vector<Train> ReadTrains(std::ifstream& fin) {
    using namespace time_utility;
    std::vector<Train> trains;
    TrainId id; int type; std::string dest;
    size_t disp_h, disp_m, trav_h, trav_m;

    while (fin >> id >> type >> dest >> disp_h >> disp_m >> trav_h >> trav_m) {
        try {
            std::time_t dispatch_time = SetTime(disp_h, disp_m);
            std::time_t travelling_time = SetTime(trav_h, trav_m);
            trains.emplace_back(id, TrainType(type), dest, dispatch_time, travelling_time);
        }
        catch (const std::out_of_range& error) {
            std::cerr << "Error: " << error.what() << '\n';
            continue;
        }
    }
    return trains;
}

void PrintSortedByDispatch(std::vector<Train>& trains) {
    std::sort(trains.begin(), trains.end());
    for (const Train& train : trains) {
        PrintTrain(train);
    }
}

void PrintTrainsInRange(const std::vector<Train>& trains, std::time_t t1, std::time_t t2) {
    for (const Train& train : trains) {
        if (train.getDispatchTime() >= t1 && train.getDispatchTime() <= t2) {
            PrintTrain(train);
        }
    }
}

void PrintTrainsToDestination(const std::vector<Train>& trains, const std::string& dest) {
    for (const Train& train : trains) {
        if (train.getDestination() == dest) {
            PrintTrain(train);
        }
    }
}

void PrintTrainsByTypeAndDestination(const std::vector<Train>& trains, int type_int, const std::string& dest) {
    for (const Train& train : trains) {
        if (train.getType() == TrainType(type_int) && train.getDestination() == dest) {
            PrintTrain(train);
        }
    }
}

void PrintFastestTrainToDestination(std::vector<Train>& trains, const std::string& dest) {
    Train* best = nullptr;
    for (Train& train : trains) {
        if (train.getDestination() == dest) {
            if (!best || train.getTravellingTime() < best->getTravellingTime()) {
                best = &train;
            }
        }
    }
    if (best != nullptr) {
        PrintTrain(*best);
    } else {
        std::cout << "No trains found to " << dest << "\n";
    }
}