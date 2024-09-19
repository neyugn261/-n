#ifndef USER_H
#define USER_H 1

#include "account.h"

//Class
class User : public Account
{
private:
    float balance;

public:
    User();
    User(int &id, string &userName, string &password);
    ~User();

    void addBalance(float amount);
    float getBalance();
};



#endif