#ifndef _COMPUTER_H
#define _COMPUTER_H 1

#include <iostream>
using namespace std;

class Computer
{
private:
    int id;
    bool isInUse;
    float pricePerHour;

public:
    Computer();
    Computer(int id);
    ~Computer();

    int getId();
    bool getIsUse();
    float getCost();
    void startUsage();
    void endUsage();
};

Computer::Computer() : id(-1), isInUse(false) {}

Computer::Computer(int id) : id(id), isInUse(false), pricePerHour(0) {}

Computer::~Computer() {};

int Computer::getId() { return id; }

bool Computer::getIsUse() { return isInUse; }

float Computer::getCost() { return pricePerHour; }

void Computer::startUsage() { isInUse = true; }

void Computer::endUsage(){ isInUse = false;}



#endif
