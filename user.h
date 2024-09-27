#ifndef USER_H
#define USER_H 1

#include "account.h"

// Class
class User : public Account
{
private:
    string balance;

public:
    User();
    User(string id, string userName, string password);
    ~User();

    string getBalance();
};

#endif