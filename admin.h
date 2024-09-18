#ifndef ADMIN_H
#define ADMIN_H 1

#include "Account.h"
#include <fstream>
#include <sstream>

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
    : Account(id, adminName, password, ADMIN) {}

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
    string idStr, roleStr;
    getline(ss, idStr, '|');
    getline(ss, account.name, '|');
    getline(ss, account.password, '|');
    getline(ss, roleStr);

    // Chuyển đổi ID từ chuỗi sang số nguyên
    account.id = stoi(idStr);

    // Chuyển đổi vai trò từ chuỗi sang enum
     if (roleStr == "USER")
        account.role = Account::USER;
    else if (roleStr == "ADMIN")
        account.role = Account::ADMIN;
    return true;
}

bool checkAccount(Account &account)
{
    string filename = "listAccount.txt";
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    Account temp;
    while(getAccountFromFile(file,temp)){
        if(temp.name == account.name, temp.password == account.password){
            account.role = temp.role;
            account.id = temp.id;
            file.close();
            return true;
        }
    }
    file.close();
    return false;    
}

#endif