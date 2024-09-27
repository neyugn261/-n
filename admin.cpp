#include "admin.h"
#include "computer.h"
#include "user.h"
#include <fstream>
#include <sstream>
#include <iomanip>

// #include "function.h"

Admin::Admin() : Account() {}

Admin::Admin(string id, string adminName, string password)
    : Account(id, adminName, password, "ADMIN") {}

Admin::~Admin() {};

int getNumberOfAccounts()
{
    int count;
    fstream file("./account/UserID.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

void updateNumberOfAccounts(int &count)
{
    fstream file("./account/UserID.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << count;
    file.close();
}

int getNumberOfComputers()
{
    int count;
    fstream file("./computer/ComputerID.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

void updateNumberOfComputers(int &count)
{
    fstream file("./computer/ComputerID.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << count;
    file.close();
}

void Admin::addAccount()
{
    string filename = "./account/listAccount.txt";
    User newAccount;

    system("cls");

    while (true)
    {
        cin >> newAccount;
        if (!checkUser(newAccount))
        {
            system("cls");
            break;
        }
        else
        {
            cout << "\nTài khoản đã được sử dụng !" << endl;
            
        }
    }

    newAccount.assignRoleIsUser();

    int count = getNumberOfAccounts();
    count++;
    stringstream ss;
    ss << setw(4) << setfill('0') << count;
    string id = "USER" + ss.str();
    newAccount.setId(id);
    updateNumberOfAccounts(count);

    fstream userFile("./account/userAccount.txt", ios::out | ios::app);
    if (userFile.is_open())
    {
        userFile << newAccount.getId() << "|" << newAccount.getName() << "|" << newAccount.getPass() << "|" << newAccount.getRole() << "|" << newAccount.getBalance() << endl;
        userFile.close();
    }
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }

    fstream listFile("./account/listAccount.txt", ios::out | ios::app);
    if (listFile.is_open())
    {
        listFile << newAccount.getName() << "|" << newAccount.getPass() << "|" << newAccount.getRole() << endl;
        listFile.close();
    }
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }
    system("cls");
}

void Admin::addComputer()
{
    string filename = "./computer/listComputer.txt";
    Computer newComputer;
    newComputer.enterCost();

    int count = getNumberOfComputers();
    count++;
    stringstream ss;
    ss << setw(2) << setfill('0') << count;
    string id = "MAY" + ss.str();
    newComputer.setId(id);

    updateNumberOfComputers(count);

    fstream file("./computer/listComputer.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << newComputer.getId() << "|" << newComputer.getCost() << "|" << newComputer.getStatus() << "|" << newComputer.getRevenue() << endl;
        file.close();
    }
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }

    system("cls");
}
