#ifndef ADMIN_H
#define ADMIN_H

#include "account.h"

class User;

// Class
class Admin : public Account
{
private:
    float balance;

public:
    Admin();
    Admin(string id, string name, string password);
    ~Admin();

    void addAccount();
    void addComputer();
    void recharge(User &user, string money);
    void resetBalance(User &user);
};

/*------------------------------------Other------------------------------------*/
int getNumberOfAccounts();
void updateNumberOfAccounts(int &count);
int getNumberOfComputers();
void updateNumberOfComputers(int &count);

#endif