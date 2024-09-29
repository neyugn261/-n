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
            cout << "Thay đổi gia tiền của máy" << endl;
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
                admin.addAccount();
                break;
            case 3:
                TTTT(admin);
                break;
            case 4:
                BfRecharge(admin);
                break;
            case 5:
                return;
            }
            break;
        }
    }
}

void menuTTTT(Admin &admin, User &user)
{
    SetConsoleTitle(TEXT("menu TTTT"));
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
                user.seenUser();
                break;
            case 2:
                changePassword(user);
                break;
            case 3:
                resetBalance(admin,user);
                break;
            case 4:
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
/*-------------------------------Tương tác thông tin------------------------------------*/
void TTTT(Admin &admin)
{
    ShowCursor(true);
    string name;
    User user;

    int count = 0;
    cout << "(Nhập sai quá 3 lần tự động thoát)" << endl;
    while (count < 3)
    {
        cout << "Nhập tên tài khoản: ";
        cin >> name;
        user.setName(name);
        if (checkUser(user))
        {
            system("cls");
            ShowCursor(false);
            menuTTTT(admin,user);
            break;
        }
        count++;
        system("cls");
        cout << "(Nhập sai quá 3 lần tự động thoát: " << count << " lần)" << endl;
        cout << "Không tìm thấy tài khoản!" << endl;
    }
    system("cls");
    ShowCursor(false);
}

void resetBalance(Admin &admin, User &user)
{
    system("cls");
    admin.resetBalance(user);
    updateAccountToFile(user);
    cout << "Đặt lại số dư tài khoản thành công!" << endl;
    cout << "\n(Nhấn ENTER để quay lại)" << endl;
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

void changePassword(User &user)
{
    ShowCursor(true);
    system("cls");
    while (true)
    {
        string password1;
        cout << "Nhập mật khẩu mới: ";
        enterpassword(password1);
        string password2;
        cout << "\nNhập lại mật khẩu: ";
        enterpassword(password2);
        if (password1 == password2)
        {
            user.changePassword(password1);
            break;
        }
        else
            cout << "\nMật khẩu không khớp, vui lòng nhập lại!" << endl;
    }
    ShowCursor(false);
    cout << "\nThay đổi mật khẩu thành công!" << endl;
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

void BfRecharge(Admin &admin)
{
    ShowCursor(true);
    string name;
    User user;

    int count = 0;
    cout << "(Nhập sai quá 3 lần tự động thoát)" << endl;
    while (count < 3)
    {
        cout << "Nhập tên tài khoản: ";
        cin >> name;
        user.setName(name);
        if (checkUser(user))
        {
            system("cls");
            cout << "Nhập số tiền cần nạp: ";
            string n;
            cin >> n;
            admin.recharge(user, n);
            cout << "Nạp tiền thành công!" << endl;
            cout << "\n(Nhất ENTER để thoát)";
            while (true)
            {
                int key = _getch();
                if (key == KEY_ENTER)
                {
                    ShowCursor(false);
                    system("cls");
                    return;
                }
            }
        }
        system("cls");
        count++;
        cout << "(Nhập sai quá 3 lần tự động thoát: " << count << " lần)" << endl;
        cout << "Không tìm thấy tài khoản!" << endl;
    }
    system("cls");
    ShowCursor(false);
}
/*------------------------------------Other------------------------------------*/