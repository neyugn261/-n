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


#endif