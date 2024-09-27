#include "function.h"
#include "admin.h"
#include "user.h"
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
            cout << "Quản lí tài khoản" << endl;
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
        }
    }
    else if (typeMenu == "QLTK")
    {
        switch (option)
        {
        case 1:
            cout << "Xem danh sách tài khoản" << endl;
            break;
        case 2:
            cout << "Thêm tài khoản" << endl;
            break;
        case 3:
            cout << "Thao tác với thông tin tài khoản" << endl;
            break;
        case 4:
            cout << "Nạp tiền" << endl;
            break;
        case 5:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "QLMC")
    {
        switch (option)
        {
        case 1:
            cout << "Xem danh sách máy con" << endl;
            break;
        case 2:
            cout << "Thêm máy con" << endl;
            break;
        case 3:
            cout << "Thao tác với thông tin máy con" << endl;
            break;
        case 4:
            cout << "Xem lịch sử sử dụng máy con" << endl;
            break;
        case 5:
            cout << "Chỉ định tài khoản vào máy con" << endl;
            break;
        case 6:
            cout << "Tính toán doanh thu ngày hôm nay" << endl;
            break;
        case 7:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "TTTT")
    {
        switch (option)
        {
        case 1:
            cout << "Xem thông tin tài khoản" << endl;
            break;
        case 2:
            cout << "Thay đổi mật khẩu" << endl;
            break;
        case 3:
            cout << "Reset số dư tài khoản" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
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

int getMenuOptionCount(const string &typeMenu)
{
    if (typeMenu == "ADMIN")
        return 4;
    if (typeMenu == "QLTK")
        return 5;
    if (typeMenu == "QLMC")
        return 7;
    if (typeMenu == "TTTT")
        return 4;
    if (typeMenu == "một menu khác")
        return 4; // số chức năng của menu

    // Mặc định nếu không tìm thấy menu
    return 0;
}

void showMenu(string typeMenu, int selectOption)
{
    int optionCount = getMenuOptionCount(typeMenu);
    if (optionCount > 0)
    {
        Gotoxy(0, 1);
        for (int i = 1; i <= optionCount; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else
    {
        cout << "Menu not found!" << endl;
    }
}

void seenUser(User &user)
{
    system("cls");
    cout << "(Nhấn ENTER để thoát)" << endl;
    cout << user;
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


void menuTTTT(User &user)
{
    SetConsoleTitle(TEXT("Menu TTTT"));
    int selectOption = 1;
    while (true)
    {
        showMenu("TTTT", selectOption);
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
                seenUser(user);
                break;
            case 2:

                break;
            case 3:
                break;
            case 4:
                return;
            }
            break;
        }
    }
}

// thao tác với thông tin tài khoản
void TTTT()
{
    ShowCursor(true);
    string name;
    User user;
    string pathFileUser = "./account/userAccount.txt";
    fstream fileUser(pathFileUser, ios::in);

    int i = 1;
    int count = 0;
    cout << "(Nhập sai quá 3 lần tự động thoát)" << endl;
    while (count < 3)
    {
        cout << "Nhập tên tài khoản: ";
        cin >> name;

        while (getUserFromFile(fileUser, user))
        {
            if (user.getName() == name)
            {
                i = 0;
                break;
            }
        }

        if (i)
        {
            cout << "Không tìm thấy tài khoản!" << endl;
            count++;
        }
        else
            break;
    }
    system("cls");
    ShowCursor(false);
    if (i)
        return;

    menuTTTT(user);

    fileUser.close();
}

void menuQLTK(Admin &admin)
{
    SetConsoleTitle(TEXT("Menu QLTK"));
    int selectOption = 1;
    while (true)
    {
        showMenu("QLTK", selectOption);
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
            system("cls");
            switch (selectOption)
            {
            case 1:
                break;
            case 2:
                ShowCursor(true);
                admin.addAccount();
                ShowCursor(false);
                break;
            case 3:
                TTTT();
                break;
            case 5:
                return;
            }
            break;
        }
    }
}

void menuQLMC(Admin &admin)
{
    SetConsoleTitle(TEXT("Menu QLMC"));
    int selectOption = 1;
    while (true)
    {
        showMenu("QLMC", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 7 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 7) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            system("cls");
            switch (selectOption)
            {
            case 1:
                break;
            case 2:
                ShowCursor(true);
                admin.addComputer();
                ShowCursor(false);
                break;
            case 3:
                break;
            case 7:
                return;
            }
            break;
        }
    }
}

void menuAdmin(Admin &admin)
{
    SetConsoleTitle(TEXT("Menu Admin"));
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
                menuQLTK(admin);
                break;
            case 2:
                menuQLMC(admin);
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

// int getNumberOfAccounts()
// {
//     int count;
//     fstream file("UserID.txt", ios::in);
//     if (!file.is_open())
//     {
//         cout << "Không thể mở file" << endl;
//         return -1;
//     }
//     file >> count;
//     file.close();
//     return count;
// }

// void updateNumberOfAccounts(int &count)
// {
//     fstream file("UserID.txt", ios::out);
//     if (!file.is_open())
//     {
//         cout << "Không thể mở file" << endl;
//         return;
//     }
//     file << count;
//     file.close();
// }

// int getNumberOfComputers()
// {
//     int count;
//     fstream file("ComputerID.txt", ios::in);
//     if (!file.is_open())
//     {
//         cout << "Không thể mở file" << endl;
//         return -1;
//     }
//     file >> count;
//     file.close();
//     return count;
// }

// void updateNumberOfComputers(int &count)
// {
//     fstream file("ComputerID.txt", ios::out);
//     if (!file.is_open())
//     {
//         cout << "Không thể mở file" << endl;
//         return;
//     }
//     file << count;
//     file.close();
// }