#include "account.h"
#include <fstream>
#include <sstream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

Account::Account(string id, string name, string password) : id(id), name(name), password(password) {}

Account::~Account() {}

string Account::getName() { return name; }

string Account::getPass() { return password; }

string Account::getId() { return id; }

string Account::getRole() { return role; }

void Account::setId(string Id) { id = Id; }

void Account::setName(string Name) { name = Name; }

void Account::assignRoleIsUser() { role = "USER"; }

bool Account::login()
{
    system("cls");
    int count = 0;
    while (count++ < 3)
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
        }
    }
    system("cls");
    cout << "Đã nhập sai quá 3 lần!" << endl;
    cout << "\n(Nhấn ENTER để thoát)";
    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");
    return false;
}

/*------------------------------------Other------------------------------------*/

bool checkAccount(Account &account)
{
    string filename = "./account/listAccount.txt";
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
    if (!getline(file, line) || line.empty())
        return false;

    stringstream ss(line);
    getline(ss, account.name, '|');
    getline(ss, account.password, '|');
    getline(ss, account.role);

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
/*------------------------------------Other------------------------------------*/
void enterpassword(string &password)
{
    password.clear();
    char ch;
    while (true)
    {
        ch = getch();
        if (ch == KEY_ENTER)
            break;
        else if (ch == KEY_BACKSPACE && !password.empty())
        {
            cout << "\b \b";
            password.pop_back();
        }
        else if (ch != KEY_BACKSPACE)
        {
            password += ch;
            cout << "•";
        }
    }
}