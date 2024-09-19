#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
using namespace std;
// Class
class Account
{
protected:
    int id;
    string name;
    string password;
    string role;

public:
    Account();
    Account(int &id, string &name, string &password, string role);
    ~Account();

    string getName();
    string getPass();
    int getId();
    string getRole();
    bool login();          
    void assignRoleIsUser();
    void changePassword(); // chua lam

    friend istream &operator>>(istream &in, Account &account);
    friend bool checkAccount(Account &account);                      
    friend bool getAccountFromFile(fstream &file, Account &account); 
};

bool checkAccount(Account &account);
bool getAccountFromFile(fstream &file, Account &account);
istream &operator>>(istream &in, Account &account);
void enterpassword(string &password);

#endif