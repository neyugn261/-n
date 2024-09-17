#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
#include <conio.h>
#include "function.h"
using namespace std;

// Class
class Account
{
public:
    enum Role
    {
        USER,
        ADMIN
    };

protected:
    int id;
    string name;
    string password;
    Role role;

public:
    Account();
    Account(int &id, string &name, string &password,Role role);
    ~Account();

    string getName();
    string getPass();
    int getId();
    Role getRole();

    friend istream &operator>>(istream &in, Account &account);
};

// Hàm
Account::Account() : id(-1), role(USER) {}

Account::Account(int &id, string &name, string &password, Role role)
    : id(id), name(name), password(password), role(role) {}

Account::~Account() {};

string Account::getName() { return name; }

string Account::getPass() { return password; }

int Account::getId() { return id; }

Account::Role Account::getRole() { return role; }

void enterpassword(string &password)
{
    password = "";
    int i = 0;
    while (true)
    {
        char ch = getch();
        if (ch == KEY_ENTER)
            break;
        if (ch != KEY_BACKSPACE)
        {
            password += ch;
            i++;
            cout << "•";
        }
        else
        {
            if (i > 0)
            {
                i--;
                cout << "\b \b";
            }
            else
            {
                cout << " \b"; // cần check
            }
        }
    }
}

istream &operator>>(istream &in, Account &account)
{
    cout << "Name: ";
    in >> account.name;
    cout << "Password: ";
    enterpassword(account.password);
    return in;
}

#endif