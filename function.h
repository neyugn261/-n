#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <fstream>
#include <sstream>

#define KEY_ENTER 13
#define KEY_BACKSPACE 8

using namespace std;

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

void optionmenu(string tyMenu, int option)
{
}

#endif