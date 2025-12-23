#include "time_utility.h"
#include "train.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

TrainType StringToTrainType(const std::string& line);
std::string TrainTypeToString(TrainType type);
void InputCheck(std::ifstream& fin);
void PrintTrain(const Train& train);
std::vector<Train> ReadTrains(std::ifstream& fin);
void PrintSortedByDispatch(std::vector<Train>& trains);
void PrintTrainsInRange(const std::vector<Train>& trains, std::time_t t1, std::time_t t2);
void PrintTrainsToDestination(const std::vector<Train>& trains, const std::string& dest);
void PrintTrainsByTypeAndDestination(const std::vector<Train>& trains, TrainType type, const std::string& dest);
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

    TrainType type = TrainType::PASSENGER;
    std::cout << "Trains of type " << TrainTypeToString(type) << " to " << dest1 << ":\n";
    PrintTrainsByTypeAndDestination(trains, type, dest1);

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
            << " Type: " << TrainTypeToString(train.getType())
            << " Destination: " << train.getDestination()
            << " Dispatch: ";
    PrintTime(train.getDispatchTime());
    std::cout << " Travelling time: ";
    PrintTime(train.getTravellingTime());
}

std::vector<Train> ReadTrains(std::ifstream& fin) {
    using namespace time_utility;
    std::vector<Train> trains;
    TrainId id; std::string type_str; std::string dest;
    size_t disp_h, disp_m, trav_h, trav_m;

    while (fin >> id >> type_str >> dest >> disp_h >> disp_m >> trav_h >> trav_m) {
        try {
            std::time_t dispatch_time = SetTime(disp_h, disp_m);
            std::time_t travelling_time = SetTime(trav_h, trav_m);
            trains.emplace_back(id, StringToTrainType(type_str), dest, dispatch_time, travelling_time);
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
    std::cout << '\n';
}

void PrintTrainsInRange(const std::vector<Train>& trains, std::time_t t1, std::time_t t2) {
    for (const Train& train : trains) {
        if (train.getDispatchTime() >= t1 && train.getDispatchTime() <= t2) {
            PrintTrain(train);
        }
    }
    std::cout << '\n';
}

void PrintTrainsToDestination(const std::vector<Train>& trains, const std::string& dest) {
    for (const Train& train : trains) {
        if (train.getDestination() == dest) {
            PrintTrain(train);
        }
    }
    std::cout << '\n';
}

void PrintTrainsByTypeAndDestination(const std::vector<Train>& trains, TrainType type, const std::string& dest) {
    for (const Train& train : trains) {
        if (train.getType() == type && train.getDestination() == dest) {
            PrintTrain(train);
        }
    }
    std::cout << '\n';
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
    std::cout << '\n';
}

TrainType StringToTrainType(const std::string& line) {
    if (line == "PASSENGER") {
        return TrainType::PASSENGER;
    }
    if (line == "FREIGHT") {
        return TrainType::FREIGHT;
    } 
    if (line == "HIGH_SPEED") {
        return TrainType::HIGH_SPEED;
    }
    if (line == "SUBWAY") {
        return TrainType::SUBWAY;
    }
    if (line == "SPECIALIZED") {
        return TrainType::SPECIALIZED;
    } 
    throw std::out_of_range("Incorrect TrainType: " + line);
}

std::string TrainTypeToString(TrainType type) {
    if (type == TrainType::PASSENGER) {
        return "PASSENGER";
    }
    if (type == TrainType::FREIGHT) {
        return "FREIGHT";
    }
    if (type == TrainType::HIGH_SPEED) {
        return "HIGH_SPEED";
    }
    if (type == TrainType::SUBWAY) {
        return "SUBWAY";
    }
    if (type == TrainType::SPECIALIZED) {
        return "SPECIALIZED";
    }
    return "UNKNOWN";
}

