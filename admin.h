#ifndef ADMIN_H
#define ADMIN_H 1

#include "account.h"

// Class
class Admin : public Account
{
private:
    float balance;

public:
    Admin();
    Admin(int &id, string &adminName, string &password);
    ~Admin();

    void addAccount();
};
bool getAccountFromFile(fstream &file, Account &account);
int getMaxId(string &filename);
#endif