#include "account.h"
#include <fstream>
#include <sstream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

Account::Account() : id(-1) {}

Account::Account(int &id, string &name, string &password, string role)
    : id(id), name(name), password(password), role(role) {}

Account::~Account() {};

string Account::getName() { return name; }

string Account::getPass() { return password; }

int Account::getId() { return id; }

string Account::getRole() { return role; }

void Account::assignRoleIsUser() { role = "USER"; }

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
        else
        {
            cout << "\nĐăng nhập thất bại" << endl;
            count++;
        }
    }
    cout << "Đăng nhập sai quá 3 lần !" << endl;
    ;
    return false;
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

istream &operator>>(istream &in, Account &account)
{
    cout << "Username: ";
    in >> account.name;
    cout << "Password: ";
    enterpassword(account.password);
    return in;
}

void enterpassword(string &password)
{
    password = "";
    int i = 0;
    while (true)
    {
        char ch = getch();
        if (ch == KEY_ENTER)
            break;
        else if (ch == KEY_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password += ch;
            i++;
            cout << "•";
        }
    }
}
