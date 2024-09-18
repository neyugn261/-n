#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include "function.h"

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
    bool login();          // chua lam
    void changePassword(); // chua lam

    friend istream &operator>>(istream &in, Account &account);
    friend bool checkAccount(Account &account);                      // chua lam
    friend bool getAccountFromFile(fstream &file, Account &account); // chualam
};

// Hàm
Account::Account() : id(-1) {}

Account::Account(int &id, string &name, string &password, string role)
    : id(id), name(name), password(password), role(role) {}

Account::~Account() {};

string Account::getName() { return name; }

string Account::getPass() { return password; }

int Account::getId() { return id; }

string Account::getRole() { return role; }

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
        }
    }
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
    while (getAccountFromFile(file, temp))
    {
        if (temp.name == account.name && temp.password == account.password)
        {
            account.role = temp.role;
            account.id = temp.id;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Hàm này cần thêm cái dòng thông báo
bool Account::login()
{
    system("cls");
    int count = 0;
    while (count < 3)
    {
        cin >> *this;
        if (checkAccount(*this))
        {   
            system("cls");
            return true;
        }
        else count++;
    }
    return false;
}

istream &operator>>(istream &in, Account &account)
{
    cout << "Name: ";
    in >> account.name;
    cout << "Password: ";
    enterpassword(account.password);
    account.role = "USER";
    return in;
}

#endif