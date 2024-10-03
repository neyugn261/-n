#include "admin.h"
#include "computer.h"
#include "user.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <algorithm>

#define KEY_ENTER 13

// #include "function.h"

Admin::Admin(string id, string name, string password) : Account(id, name, password)
{
    role = "ADMIN";
}

Admin::~Admin() {};

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
            cout << "\nTạo tài khoản thành công!" << endl;
            break;
        }
        else
        {
            cout << "\nTài khoản đã được sử dụng, vui lòng nhập tài khoản khác!" << endl;
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

    // thay đổi file userAccount.txt
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

    // thay đổi file listAccount.txt
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
}

void Admin::addComputer()
{
    string filename = "./computer/listComputer.txt";
    Computer newComputer;
    cout << "Nhập giá tiền trên 1 giờ của máy: ";
    newComputer.enterCost();

    int count = getNumberOfComputers();
    count++;
    stringstream ss;
    ss << setw(2) << setfill('0') << count;
    newComputer.setId("MAY" + ss.str());

    updateNumberOfComputers(count);

    fstream file("./computer/listComputer.txt", ios::out | ios::app);
    if (file)
    {
        file << newComputer.getId() << "|" << newComputer.getCost() << "|" << newComputer.getStatus() << "|" << newComputer.getRevenue() << endl;
    }
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }
}
void Admin ::recharge(User &user)
{
    string money;
    cin >> money;

    string balance = user.getBalance();
    balance.erase(remove(balance.begin(), balance.end(), '.'), balance.end());

    int total = stoi(balance) + stoi(money);
    string formattedBalance = to_string(total);

    int insertPosition = formattedBalance.length() - 3;
    while (insertPosition > 0)
    {
        formattedBalance.insert(insertPosition, ".");
        insertPosition -= 3;
    }

    user.setBalance(formattedBalance);
    updateAccountToFile(user);
}
void Admin ::resetBalance(User &user)
{
    user.setBalance("0.000");
}
void Admin ::chagneCostCom(Computer &computer)
{
    computer.enterCost();
    updateComToFile(computer);
}

void Admin ::seenUser(User &user)
{
    cout << user;
}

/*------------------------------------Other------------------------------------*/
int getNumberOfAccounts()
{
    int count = -1;
    fstream file("./account/UserID.txt", ios::in);
    if (!file)
        cout << "Không thể mở file" << endl;
    else
        file >> count;
    file.close(); // kiểm tra có cần thiết ko
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
    file.close(); // kiểm tra có cần thiết ko
}

int getNumberOfComputers()
{
    int count = -1;
    fstream file("./computer/ComputerID.txt", ios::in);
    if (!file)
        cout << "Không thể mở file" << endl;
    else
        file >> count;
    file.close();
    return count;
}

void updateNumberOfComputers(int &count)
{
    fstream file("./computer/ComputerID.txt", ios::out);
    if (!file)
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << count;
    file.close();
}
