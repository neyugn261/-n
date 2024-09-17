#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
using namespace std;

class Account
{
private:
    int id;
    string username;
    string password;
    float balance;

public:
    Account();
    Account(int &id, string &username, string &password);
    ~Account();

    int getId() const;
    string getUsername() const;
    void addBalance(float amount);
    float getBalance() const;
    //   void deductBalance(float amount) { balance -= amount; }
};

Account::Account(int &id, string &username, string &password)
    : id(id), username(username), password(password), balance(0.0f) {}

Account::Account() : id(-1), balance(0.0f) {}

Account::~Account(){} ;

int Account::getId() const { return id; }

string Account::getUsername() const { return username; }

float Account::getBalance() const { return balance; }

void Account::addBalance(float amount) { balance += amount; }

#endif