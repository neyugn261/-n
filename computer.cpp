#include "computer.h"
#include <string>
#include <algorithm>
Computer::Computer() : status("NotInUse"), revenue("0.000") {}

Computer::~Computer() {};

string Computer::getId() { return id; }

string Computer::getStatus() { return status; }

string Computer::getCost() { return pricePerHour; }

string Computer::getRevenue() { return revenue; }

void Computer::setId(string iD) { id = iD; }

void Computer::startUsage() { status = "InUse"; }

void Computer::endUsage() { status = "NotInUse"; }

void Computer::enterCost()
{
    cout << "Nhập số tiền trên 1 giờ của máy: ";
    int n;
    cin >> n;

    pricePerHour = std::to_string(n);

    // Định dạng lại chuỗi để thêm dấu chấm
    int insertPosition = pricePerHour.length() - 3; // Vị trí chèn dấu chấm
    while (insertPosition > 0)
    {
        pricePerHour.insert(insertPosition, "."); // Thêm dấu chấm
        insertPosition -= 3;                      // Giảm vị trí thêm dấu chấm 3 đơn vị
    }
}