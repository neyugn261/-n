#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

using namespace std;

/*------------------------------------CONSOLE------------------------------------*/

void ShowCursor(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

void Gotoxy(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option)
{
    if (typeMenu == "ADMIN")
    {
        switch (option)
        {
        case 1:
            cout << "Quản lí người dùng" << endl;
            break;
        case 2:
            cout << "Quản lí máy con" << endl;
            break;
        case 3:
            cout << "Hóa đơn" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
            break;
        default:
            break;
        }
    }
    else if (typeMenu == "QLND")
    {
        switch (option)
        {
        case 1:
            cout << "Xem danh sách người dùng" << endl;
            break;
        case 2:
            cout << "Thêm người dùng" << endl;
            break;
        case 3:
            cout << "Thao tác với thông tin người dùng" << endl;
            break;
        case 4:
            cout << "Nạp tiền" << endl;
            break;
        case 5:
            cout << "Thoát" << endl;
            break;
        default:
            break;
        }
    }
}

void printMenuOption(string typeMenu, int option, bool isSelected)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = isSelected ? 240 : 15;
    SetConsoleTextAttribute(myConsole, color);
    optionMenu(typeMenu, option);
    SetConsoleTextAttribute(myConsole, 15);
}

void showMenu(string typeMenu, int selectOption)
{
    if (typeMenu == "ADMIN")
    {
        Gotoxy(0, 1);
        for (int i = 1; i <= 4; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "QLND")
    {
        Gotoxy(0, 1);
        for (int i = 1; i <= 5; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
}

void menuQLND()
{
    SetConsoleTitle (TEXT("Menu QLND"));
    int selectOption = 1;
    while (true)
    {
        showMenu("QLND", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 5 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 5) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            if (selectOption == 5)
            {
                system("cls");
                return;
            }
            cout << "Chọn " << selectOption << endl;
            break;
        }
    }
    ShowCursor(true);
}

void menuAdmin()
{
    SetConsoleTitle (TEXT("Menu Admin"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("ADMIN", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            system("cls");
            switch (selectOption)
            {
            case 1:
                menuQLND();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                cout << "Thoát" << endl;
                return;
            }
            break;     
        }
    }
    ShowCursor(true);
}

/*------------------------------------Other------------------------------------*/
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

#endif