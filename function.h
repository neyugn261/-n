#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include <functional>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

class Admin;
class User;

/*------------------------------------CONSOLE------------------------------------*/
void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);
void pressEnter();
/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option);
void printMenuOption(string typeMenu, int option, bool isSelected);
int getMenuOptionCount(const string &typeMenu);
void showMenu(string typeMenu, int selectOption);

void menuQLTK(Admin &admin);
/**/ void menuTTTT(Admin &admin, User &user);

void menuQLMC(Admin &admin);
void menuAdmin(Admin &admin);
/*-------------------------------QLTK------------------------------------*/
void seenListAccount(Admin &admin); // chưa đóng khung

void addAccount(Admin &admin);

void TTTT(Admin &admin);
/**/ void seenUser(Admin &admin, User &user);
/**/ void resetBalance(Admin &admin, User &user);
/**/ void changePassword(User &user);
/**/ void deleteAccount(Admin &admin, User &user);

void Recharge(Admin &admin);

/*------------------------------------QLMC------------------------------------*/
void seenListComputer(Admin &admin); // chưa làm

void addComputer(Admin &admin);

void deleteComputer(Admin &admin);

void changeCost(Admin &admin);

void seenHistory(Admin &admin); // chưa làm

void createSession(Admin &admin); // chưa làm vì khó :((

void caculateRevenue(Admin &admin); // chưa làm

/*------------------------------------Hóa đơn------------------------------------*/
void printInvoice(Admin &admin); // chưa làm
#endif