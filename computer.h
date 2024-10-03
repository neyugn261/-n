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
    ~Computer();

    string getId();
    string getStatus();
    string getCost();
    string getRevenue();
    void setId(string iD);
    void setCost(string cost);

    void enterCost();
    void startUsage();
    void endUsage();

    friend bool getComFromFile(fstream &file, Computer &Computer);
    friend bool checkCom(Computer &computer);
    friend void updateComToFile(Computer &computer);
    friend bool checkCom(Computer &com);
};

bool getComFromFile(fstream &file, Computer &computer);
bool checkCom(Computer &computer);
void updateComToFile(Computer &computer);
bool checkCom(Computer &computer);

#endif