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

    void addAccount();
};

// Hàm
Admin::Admin() : Account() {}

Admin::Admin(int &id, string &adminName, string &password)
    : Account(id, adminName, password, "ADMIN") {}

Admin::~Admin() {};

void Admin::addAccount()
{
    string filename = "listAccount.txt";
    User newAccount;
    cin >> newAccount;
    int newId = getMaxId(filename);
    fstream file("account.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << newId << "|" << newAccount.getName() << "|" << newAccount.getPass() << "|" << newAccount.getRole() << endl;
        file.close();
    }
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }
}

bool getAccountFromFile(fstream &file, Account &account)
{
    string line;
    getline(file, line);
    if (line == "")
        return false;
    stringstream ss(line);
    string idStr;
    getline(ss, idStr, '|');
    getline(ss, account.name, '|');
    getline(ss, account.password, '|');
    getline(ss, account.role);

    // Chuyển đổi ID từ chuỗi sang số nguyên
    account.id = stoi(idStr);
    
    return true;
}



#endif