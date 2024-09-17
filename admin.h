#ifndef ADMIN_H
#define ADMIN_H 1

#include "Account.h"

// Class
class Admin : public Account
{
private:
    float balance;

public:
    Admin();
    Admin(int &id, string &adminName, string &password);
    ~Admin();
};

// Hàm
Admin::Admin() : Account() {}

Admin::Admin( int &id, string &adminName, string &password)
    : Account(id, adminName, password,ADMIN) {}

Admin::~Admin() {};

#endif