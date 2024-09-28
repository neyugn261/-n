#ifndef ADMIN_H
#define ADMIN_H 

#include "account.h"

// Class
class Admin : public Account
{
private:
    float balance;

public:
    Admin();
    Admin(string id, string adminName, string password);
    ~Admin();

    void addAccount();
    void addComputer();
};

/*------------------------------------Other------------------------------------*/
int getNumberOfAccounts();
void updateNumberOfAccounts(int &count);
int getNumberOfComputers();
void updateNumberOfComputers(int &count);


#endif