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

Admin::Admin() : Account()
{
    role = "ADMIN";
}

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
        cout << "Thêm máy thành công!" << endl;
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
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }
}
void Admin ::recharge(User &user, string money)
{
    string temp1 = user.getBalance();
    temp1.erase(remove(temp1.begin(), temp1.end(), '.'), temp1.end());
    int x = stoi(temp1);
    int y = stoi(money);
    int z = x + y;
    temp1 = std::to_string(z);

    // Định dạng lại chuỗi để thêm dấu chấm
    int insertPosition = temp1.length() - 3; // Vị trí chèn dấu chấm
    while (insertPosition > 0)
    {
        temp1.insert(insertPosition, "."); // Thêm dấu chấm
        insertPosition -= 3;               // Giảm vị trí thêm dấu chấm 3 đơn vị
    }

    user.setBalance(temp1);
    updateAccountToFile(user);
}

void Admin ::resetBalance(User &user){
    string temp = "0.000";
    user.setBalance(temp);
}

/*------------------------------------Other------------------------------------*/
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
