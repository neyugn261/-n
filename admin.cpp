#include "admin.h"
#include <fstream>
#include <sstream>


Admin::Admin() : Account() {}

Admin::Admin(int &id, string &adminName, string &password)
    : Account(id, adminName, password, "ADMIN") {}

Admin::~Admin() {};

void Admin::addAccount()
{
    string filename = "listAccount.txt";
    Account newAccount;
    cin >> newAccount;
    newAccount.assignRoleIsUser();
    int newId = getMaxId(filename);
    fstream file("listAccount.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << newId + 1<< "|" << newAccount.getName() << "|" << newAccount.getPass() << "|" << newAccount.getRole() << endl;
        file.close();
    }
    else
    {
        cout << "Không thể mở file " << filename << endl;
    }
    system("cls");
}


int getMaxId(string &filename)
{
    fstream file(filename, ios::in);
    int maxId = 0;
    string line;

    if (file.is_open())
    {
        file.seekg(0, ios::end); // Di chuyển con trỏ tới cuối file
        if (file.tellg() != 0)   // kiểm tra file có dữ liệu
        {
            // Đọc dòng cuối cùng
            file.seekg(-1, ios::cur);
            bool keepLooping = true;
            while (keepLooping)
            {
                char ch;
                file.get(ch);
                if ((int)file.tellg() <= 1)
                {
                    file.seekg(0);
                    keepLooping = false;
                }
                else if (ch == '\n')
                {
                    keepLooping = false;
                }
                else
                {
                    file.seekg(-2, ios::cur); //-2 vì khi get thì con trỏ di chuyển
                }
            }
        }

        getline(file, line);
        stringstream ss(line);
        ss >> maxId;
    }
    file.close();
    return maxId;
}