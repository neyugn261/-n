#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include "admin.h"
//#include "user.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8


/*------------------------------------CONSOLE------------------------------------*/

void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option);

void printMenuOption(string typeMenu, int option, bool isSelected);

int getMenuOptionCount(const string &typeMenu);

void showMenu(string typeMenu, int selectOption);

void menuQLND(Admin &admin);

void menuQLMC();

void menuAdmin(Admin &admin);

/*------------------------------------Other------------------------------------*/





#endif