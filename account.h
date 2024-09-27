#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
using namespace std;
// Class
class Account
{
protected:
    string id;
    string name;
    string password;
    string role;

public:
    Account();
    Account(string id, string name, string password, string role);
    ~Account();

    string getName();
    string getPass();
    string getId();
    string getRole();
    void setId(string Id);

    bool login();
    void assignRoleIsUser();
    void changePassword(); // chua lam

    friend istream &operator>>(istream &in, Account &account);
    friend bool checkAccount(Account &account);
    friend bool getAccountFromFile(fstream &file, Account &account);
};

#endif