#include "function.h"
#include "admin.h"
#include "user.h"
#include "computer.h"
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
    COORD Position = {posX, posY};
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
            cout << "Thay đổi giá tiền của máy" << endl;
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
            cout << "Xóa tài khoản" << endl;
            break;
        case 5:
            cout << "Thoát" << endl;
            break;
        }
    }
}

void printMenuOption(string typeMenu, int option, bool isSelected)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(myConsole, isSelected ? 240 : 15);
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
        return 5;
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
        for (int i = 1; i <= optionCount; ++i)
            printMenuOption(typeMenu, i, i == selectOption);
    }
    else
        cout << "Menu not found!" << endl;
}

/*-------------------------------MENUS------------------------------------*/
void navigateMenu(const string &menuType, Admin &admin, int maxOption, function<void(int, bool &)> optionHandler)
{
    int selectOption = 1;
    bool exitMenu = false; // Biến cờ để kiểm soát thoát menu

    while (!exitMenu)
    {
        showMenu(menuType, selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? maxOption : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == maxOption) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            system("cls");
            optionHandler(selectOption, exitMenu); // Truyền biến exitMenu vào lambda để xử lý
            break;
        }
    }
}

void menuQLTK(Admin &admin)
{
    SetConsoleTitle(TEXT("Menu QLTK"));
    navigateMenu("QLTK", admin, 5, [&](int selectOption, bool &exitMenu)
                 {
        switch (selectOption)
        {
        case 1: 
            // Xem danh sách tài khoản
            break;
        case 2: 
            addAccount(admin);
            break;
        case 3: 
            TTTT(admin);
            break;
        case 4: 
            Recharge(admin);
            break;
        case 5: 
            exitMenu = true; // Khi người dùng chọn "Thoát", thoát khỏi menu
            break;
        } });
}

void menuTTTT(Admin &admin, User &user)
{
    SetConsoleTitle(TEXT("Menu TTTT"));
    navigateMenu("TTTT", admin, 5, [&](int selectOption, bool &exitMenu)
                 {
        switch (selectOption)
        {
        case 1: 
            seenUser(admin, user);
            break;
        case 2: 
            changePassword(user);
            break;
        case 3: 
            resetBalance(admin, user);
            break;
        case 4:
            deleteAccount(admin, user);
            exitMenu = true;
            break;
        case 5: 
            exitMenu = true; // Khi người dùng chọn "Thoát", thoát khỏi menu
            break;
        } });
}

void menuQLMC(Admin &admin)
{
    SetConsoleTitle(TEXT("Menu QLMC"));
    navigateMenu("QLMC", admin, 7, [&](int selectOption, bool &exitMenu)
                 {
        switch (selectOption)
        {
        case 1: 
            // Xem danh sách máy con
            break;
        case 2: 
            addComputer(admin);
            break;
        case 3: 
            changeCost(admin);
            break;
        case 7: 
            exitMenu = true; // Khi người dùng chọn "Thoát", thoát khỏi menu
            break;
        } });
}

void menuAdmin(Admin &admin)
{
    SetConsoleTitle(TEXT("Menu Admin"));
    ShowCursor(false);
    navigateMenu("ADMIN", admin, 4, [&](int selectOption, bool &exitMenu)
                 {
        switch (selectOption)
        {
        case 1: 
            menuQLTK(admin); break;
        case 2: 
            menuQLMC(admin); break;
        case 3: 
            break;
        case 4: 
            cout << "Thoát" << endl;
            exitMenu = true;
            return;
        } });
    ShowCursor(true);
}
/*-------------------------------QLTK------------------------------------*/
void addAccount(Admin &admin)
{
    ShowCursor(true);
    admin.addAccount();
    ShowCursor(false);
    cout << "\n(Nhấn ENTER để thoát)" << endl;
    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");
}

void TTTT(Admin &admin)
{
    ShowCursor(true);
    User user;
    int count = 0;
    cout << "(Nhập sai quá 3 lần tự động thoát)" << endl;
    while (count++ < 3)
    {
        cout << "Nhập tên tài khoản: ";
        string name;
        cin >> name;
        user.setName(name);
        if (checkUser(user))
        {
            system("cls");
            ShowCursor(false);
            menuTTTT(admin, user);
            return;
        }
        system("cls");
        cout << "(Nhập sai quá 3 lần tự động thoát: " << count << " lần)" << endl;
        cout << "Không tìm thấy tài khoản!" << endl;
    }
    system("cls");
    ShowCursor(false);
}

void seenUser(Admin &admin, User &user)
{
    admin.seenUser(user);
    cout << "\n(Nhấn ENTER để thoát)" << endl;
    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");
}

void resetBalance(Admin &admin, User &user)
{
    system("cls");
    admin.resetBalance(user);
    updateAccountToFile(user);
    cout << "Đặt lại số dư tài khoản thành công!" << endl;
    cout << "\n(Nhấn ENTER để quay lại)" << endl;
    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");
}

void changePassword(User &user)
{
    ShowCursor(true);
    while (true)
    {
        string password1, password2;
        cout << "Nhập mật khẩu mới: ";
        enterpassword(password1);
        cout << "\nNhập lại mật khẩu: ";
        enterpassword(password2);
        if (password1 == password2)
        {
            user.changePassword(password1);
            break;
        }
        cout << "\nMật khẩu không khớp, vui lòng nhập lại!" << endl;
    }
    ShowCursor(false);
    cout << "\nThay đổi mật khẩu thành công!" << endl;
    cout << "\n(Nhấn ENTER để thoát)" << endl;
    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");
}

void Recharge(Admin &admin)
{
    ShowCursor(true);
    User user;
    int count = 0;
    cout << "(Nhập sai quá 3 lần tự động thoát)" << endl;
    while (count++ < 3)
    {
        cout << "Nhập tên tài khoản: ";
        string name;
        cin >> name;
        user.setName(name);

        if (checkUser(user))
        {
            system("cls");
            cout << "Nhập số tiền cần nạp: ";
            admin.recharge(user);
            cout << "Nạp tiền thành công!" << endl;
            cout << "\n(Nhấn ENTER để thoát)";
            while (_getch() != KEY_ENTER)
            {
            }
            system("cls");
            break;
        }
        system("cls");
        cout << "(Nhập sai quá 3 lần tự động thoát: " << count << " lần)" << endl;
        cout << "Không tìm thấy tài khoản!" << endl;
    }
    ShowCursor(false);
    if (count >= 3)
    {
        system("cls");
        cout << "Đã nhập sai quá 3 lần!" << endl;
        cout << "\n(Nhấn ENTER để thoát)";
        while (_getch() != KEY_ENTER)
        {
        }
        system("cls");
    }
}

void deleteAccount(Admin &admin, User &user)
{
    system("cls");
    cout << "Đã xóa tài khoản: " << user.getName() << endl;
    admin.deleteAccount(user);
    cout << "\n(Nhấn ENTER để thoát)";
    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");    
}

/*------------------------------------QLMC------------------------------------*/
void addComputer(Admin &admin)
{
    ShowCursor(true);
    admin.addComputer();
    ShowCursor(false);
    cout << "Thêm máy thành công!" << endl;
    cout << "\n(Nhấn ENTER để thoát)" << endl;

    while (_getch() != KEY_ENTER)
    {
    }
    system("cls");
}

void changeCost(Admin &admin)
{
    ShowCursor(true);
    Computer computer;
    int count = 0;
    cout << "(Nhập sai quá 3 lần tự động thoát)" << endl;
    while (count++ < 3)
    {
        cout << "Nhập ID máy: ";
        string name;
        cin >> name;
        stringstream ss;
        string id = "MAY" + (stringstream() << setw(2) << setfill('0') << name).str();
        computer.setId(id);
        if (checkCom(computer))
        {
            system("cls");
            cout << "Giá tiền trên một giờ của máy hiện tại là: " << computer.getCost() << endl;
            cout << "Nhập giá tiền mới: ";
            admin.chagneCostCom(computer);
            cout << "Thay đổi thành công!" << endl;
            ShowCursor(false);
            cout << "\n(Nhấn ENTER để quay lại)" << endl;
            while (_getch() != KEY_ENTER)
            {
            }
            system("cls");

            return;
        }
        system("cls");
        cout << "(Nhập sai quá 3 lần tự động thoát: " << count << " lần)" << endl;
        cout << "Không tìm thấy máy!" << endl;
    }
    if (count >= 3)
    {
        system("cls");
        cout << "Đã nhập sai quá 3 lần!" << endl;
        cout << "\n(Nhấn ENTER để thoát)";
        while (_getch() != KEY_ENTER)
        {
        }
        system("cls");
    }
    ShowCursor(false);
}
/*------------------------------------Other------------------------------------*/