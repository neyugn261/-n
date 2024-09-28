#ifndef _COMPUTER_H
#define _COMPUTER_H 1

#include <iostream>
using namespace std;

class Computer
{
private:
    string id;
    string status;
    string pricePerHour;
    string revenue;

public:
    Computer();
    Computer(int id);
    ~Computer();

    string getId();
    string getStatus();
    string getCost();
    string getRevenue();
    void setId(string iD);

    void enterCost();
    void startUsage();
    void endUsage();
    
};

#endif