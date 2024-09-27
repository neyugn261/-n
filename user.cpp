#include "user.h"
#include <fstream>
#include <sstream>
#include <iomanip>

User::User() : Account()
{
    balance = "0.000";
}

User::~User() {};

string User::getBalance() { return balance; }

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
            return true;
        }
    }
    file.close();
    return false;
}

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

ostream &operator<<(ostream &out, User &user){
    cout<<"ID: "<<user.getId()<<endl;
    cout<<"Tài khoản: "<<user.getName()<<endl;
    cout<<"Mật khẩu: "<<user.getPass()<<endl;
    cout<<"Số dư: "<<user.getBalance()<<endl;
    return out;
}