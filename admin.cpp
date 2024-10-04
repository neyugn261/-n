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
            break;
        else
        {
            cout << "\nTài khoản đã được sử dụng, vui lòng nhập tài khoản khác!" << endl;
        }
    }

    newAccount.assignRoleIsUser();

    int count = numberFromEmptyId();

    if (count == -1)
    {
        count = getNumberOfAccounts();
        count++;
        updateNumberOfAccounts(count);
    }
    stringstream ss;
    ss << setw(4) << setfill('0') << count;
    string id = "USER" + ss.str();
    newAccount.setId(id);
    cout << "\nTạo tài khoản thành công với ID là: " << newAccount.getId() << endl;

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

void Admin::deleteAccount(User &user)
{
    // Paths for userAccount and listAccount files
    string path1 = "./account/userAccount.txt";
    string tempPath1 = "./account/temp1.txt";
    string path2 = "./account/listAccount.txt";
    string tempPath2 = "./account/temp2.txt";

    string path3 = "./account/emptyID.txt";

    fstream file1(path1, ios::in);
    fstream tempFile1(tempPath1, ios::out);
    fstream file2(path2, ios::in);
    fstream tempFile2(tempPath2, ios::out);

    // File open error handling
    if (!file1.is_open() || !tempFile1.is_open() || !file2.is_open() || !tempFile2.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    // Update userAccount.txt
    User temp1;
    while (getUserFromFile(file1, temp1))
    {
        if (temp1.getName() == user.getName())
        {
            string temp = temp1.getId();
            string numberPart = temp.substr(4);
            size_t pos = numberPart.find_first_not_of('0');
            temp = (pos != string::npos) ? numberPart.substr(pos) : "0";

            fstream file3(path3, ios::app);
            file3 << temp << endl;
            file3.close();

            continue; //
        }
        tempFile1 << temp1.getId() << "|" << temp1.getName() << "|" << temp1.getPass() << "|" << temp1.getRole() << "|" << temp1.getBalance() << endl;
    }

    // Update listAccount.txt
    User temp2;
    while (getAccountFromFile(file2, temp2)) // Assuming getAccountFromFile is implemented for generic accounts
    {
        if (temp2.getName() == user.getName())
        {
            continue;
        }
        tempFile2 << temp2.getName() << "|" << temp2.getPass() << "|" << temp2.getRole() << endl;
    }

    // Close all files
    file1.close();
    tempFile1.close();
    file2.close();
    tempFile2.close();

    // Replace original files with temp files
    system("del .\\account\\userAccount.txt");
    system("rename .\\account\\temp1.txt userAccount.txt");

    system("del .\\account\\listAccount.txt");
    system("rename .\\account\\temp2.txt listAccount.txt");
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

bool dataOfEmptyId(fstream &file, int &count)
{
    string line;
    getline(file, line);
    if (line.empty())
        return false;
    else
    {
        count = stoi(line);
        return true;
    }
}

int numberFromEmptyId()
{
    int count = -1;

    string path1 = "./account/emptyID.txt";
    string tempPath1 = "./account/temp1.txt";

    fstream file1(path1, ios::in);
    fstream tempFile1(tempPath1, ios::out);

    if (dataOfEmptyId(file1, count))
    {
        int ans = count;
        while (dataOfEmptyId(file1, count))
        {
            tempFile1 << count << endl;
        }
        file1.close();
        tempFile1.close();
        system("del .\\account\\emptyID.txt");
        system("rename .\\account\\temp1.txt emptyID.txt");
        return ans;
    }

    return count;
}
