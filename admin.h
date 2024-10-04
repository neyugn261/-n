#ifndef ADMIN_H
#define ADMIN_H

#include "account.h"

class User;
class Computer;

// Class
class Admin : public Account
{
private:
    float balance;

public: 
    Admin(string id = "", string name = "", string password = "");
    ~Admin();

    void addAccount();
    void deleteAccount(User &user);
    void addComputer();
    void recharge(User &user);
    void resetBalance(User &user);
    void chagneCostCom(Computer &Computer);
    void seenUser(User &user);
};

/*------------------------------------Other------------------------------------*/
int getNumberOfAccounts();
void updateNumberOfAccounts(int &count);
int getNumberOfComputers();
void updateNumberOfComputers(int &count);
bool dataOfEmptyId(fstream &file, int &count);
int numberFromEmptyId();


#endif