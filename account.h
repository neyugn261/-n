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
    Account(string id = "", string name = "", string password = "");
    ~Account();

    string getName();
    string getPass();
    string getId();
    string getRole();
    void setId(string Id);
    void setName(string Name);

    bool login();
    void assignRoleIsUser();

    friend istream &operator>>(istream &in, Account &account);
    friend bool checkAccount(Account &account);
    friend bool getAccountFromFile(fstream &file, Account &account);
};

/*------------------------------------Friend------------------------------------*/
bool checkAccount(Account &account);
bool getAccountFromFile(fstream &file, Account &account);
istream &operator>>(istream &in, Account &account);
/*------------------------------------Other------------------------------------*/
void enterpassword(string &password);

#endif