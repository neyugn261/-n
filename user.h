#ifndef USER_H
#define USER_H 

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
    friend bool checkUser(User &user);
    friend bool getUserFromFile(fstream &file, User &user);
    friend ostream &operator<<(ostream &out, User &user);
};
bool checkUser(User &user);
ostream &operator<<(ostream &out, User &user);
#endif