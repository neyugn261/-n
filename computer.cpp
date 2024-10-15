#include "computer.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>

Computer::Computer() : status("NotInUse"), revenue("0.000") {}

Computer::~Computer() {};

string Computer::getId() { return id; }

string Computer::getStatus() { return status; }

string Computer::getCost() { return pricePerHour; }

string Computer::getRevenue() { return revenue; }

void Computer::setId(string iD) { id = iD; }

void Computer::setCost(string cost) { pricePerHour = cost; }

void Computer::setStatus(string Status) { status = Status; }

void Computer::startUsage() { status = "InUse"; }

void Computer::endUsage() { status = "NotInUse"; }

void Computer::enterCost()
{

    while (true)
    {
        cin >> pricePerHour;

        // Kiểm tra xem chuỗi có phải toàn số không
        if (all_of(pricePerHour.begin(), pricePerHour.end(), ::isdigit))
        {
            break;
        }
        cout << "Giá trị nhập vào không hợp lệ. Vui lòng nhập lại!\n";
    }

    // Định dạng lại chuỗi để thêm dấu chấm
    int insertPosition = pricePerHour.length() - 3;
    {
        pricePerHour.insert(insertPosition, ".");
        insertPosition -= 3;
    }
}

/*------------------------------------Friend------------------------------------*/
bool getComFromFile(fstream &file, Computer &computer)
{
    string line;
    getline(file, line);
    if (line.empty())
        return false;
    stringstream ss(line);
    getline(ss, computer.id, '|');
    getline(ss, computer.pricePerHour, '|');
    getline(ss, computer.status, '|');
    getline(ss, computer.revenue);

    return true;
}
void updateComToFile(Computer &computer)
{
    // sửa file: lisComputer
    string path1 = "./computer/listComputer.txt";
    fstream file1(path1, ios::in);
    if (!file1.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string tempPath1 = "./computer/temp1.txt";
    fstream tempFile1(tempPath1, ios::out);
    if (!tempFile1.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    Computer temp1;
    while (getComFromFile(file1, temp1))
    {
        if (temp1.id == computer.id)
        {
            temp1 = computer;
        }
        tempFile1 << temp1.id << "|" << temp1.pricePerHour << "|" << temp1.status << "|" << temp1.revenue << endl;
    }

    file1.close();
    tempFile1.close();

    system("del .\\computer\\listComputer.txt");
    system("rename .\\computer\\temp1.txt listComputer.txt");
}

bool checkCom(Computer &computer)
{
    string filename = "./computer/listComputer.txt";
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    Computer temp;
    while (getComFromFile(file, temp))
    {
        if (temp.id == computer.id)
        {
            computer = temp;
            return true;
        }
    }
    file.close();
    return false;
}