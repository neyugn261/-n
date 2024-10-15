#ifndef USER_H
#define USER_H

#include "account.h"

// Class
class User : public Account
{
private:
    string balance;   

public:
    User(string id = "", string name = "", string password = "");
    ~User();

    string getBalance();
    void setBalance(string balance);

    void changePassword(string passWord);

    friend bool getUserFromFile(fstream &file, User &user);
    friend ostream &operator<<(ostream &out, User &user);
    friend bool checkUser(User &user);
    friend void updateAccountToFile(User &user);
};

/*------------------------------------Friend------------------------------------*/
bool getUserFromFile(fstream &file, User &user);
ostream &operator<<(ostream &out, User &user);
bool checkUser(User &user);
void updateAccountToFile(User &user);

#endif