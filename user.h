#ifndef USER_H
#define USER_H 1

#include "Account.h"

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


// Hàm
User::User() : Account() {}

User::User( int &id, string &userName, string &password)
    : Account(id, userName, password,USER) {}

User::~User() {};

float User::getBalance() { return balance; }

void User::addBalance(float amount) { balance += amount; }

#endif