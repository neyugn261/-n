#include "user.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>

#define KEY_ENTER 13

User::User() : Account()
{
    role = "USER";
    balance = "0.000";
}

User::User(string id, string name, string password) : Account(id, name, password)
{
    role = "USER";
}
User::~User() {};

string User::getBalance() { return balance; }

void User::setBalance(string balance)
{
    this->balance = balance;
}

void User::changePassword(string newPassword)
{
    password = newPassword;
    updateAccountToFile(*this);
}

void User ::seenUser()
{
    system("cls");
    cout << *this;
    cout << "\n(Nhấn ENTER để thoát)" << endl;
    while (true)
    {
        int key = _getch();
        if (key == KEY_ENTER)
        {
            system("cls");
            return;
        }
    }
}

/*------------------------------------Friend------------------------------------*/
bool getUserFromFile(fstream &file, User &user)
{
    string line;
    getline(file, line);
    if (line == "")
        return false;
    stringstream ss(line);
    getline(ss, user.id, '|');
    getline(ss, user.name, '|');
    getline(ss, user.password, '|');
    getline(ss, user.role, '|');
    getline(ss, user.balance);

    return true;
}

ostream &operator<<(ostream &out, User &user)
{
    cout << "ID: " << user.getId() << endl;
    cout << "Tài khoản: " << user.getName() << endl;
    cout << "Mật khẩu: " << user.getPass() << endl;
    cout << "Số dư: " << user.getBalance() << endl;
    return out;
}

bool checkUser(User &user)
{
    string filename = "./account/userAccount.txt";
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    User temp;
    while (getUserFromFile(file, temp))
    {
        if (temp.name == user.name)
        {
            user = temp;
            return true;
        }
    }
    file.close();
    return false;
}

void updateAccountToFile(User &account)
{
    // sửa file: userAcount
    string path1 = "./account/userAccount.txt";
    fstream file1(path1, ios::in);
    if (!file1.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string tempPath1 = "./account/temp1.txt";
    fstream tempFile1(tempPath1, ios::out);
    if (!tempFile1.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    // sửa file: listAccount
    string path2 = "./account/listAccount.txt";
    fstream file2(path2, ios::in);
    if (!file2.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string tempPath2 = "./account/temp2.txt";
    fstream tempFile2(tempPath2, ios::out);
    if (!tempFile2.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    User temp1;
    while (getUserFromFile(file1, temp1))
    {
        if (temp1.name == account.name)
        {
            temp1 = account;
        }
        tempFile1 << temp1.id << "|" << temp1.name << "|" << temp1.password << "|" << temp1.role << "|" << temp1.balance << endl;
    }

    User temp2;
    while (getAccountFromFile(file2, temp2))
    {
        if (temp2.name == account.name)
        {
            temp2 = account;
        }
        tempFile2 << temp2.name << "|" << temp2.password << "|" << temp2.role << endl;
    }

    file1.close();
    tempFile1.close();
    file2.close();
    tempFile2.close();

    system("del .\\account\\userAccount.txt");
    system("rename .\\account\\temp1.txt userAccount.txt");

    system("del .\\account\\listAccount.txt");
    system("rename .\\account\\temp2.txt listAccount.txt");
}