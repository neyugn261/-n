#ifndef _SESSION_H
#define _SESSION_H 1

#include <iostream>
#include "mtime.h"
#include "computer.h"
#include "user.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include <thread>
#include <windows.h>

using namespace std;

class Session
{
private:
    string id;
    string status;
    string cost;
    Time startTime;
    Time endTime;

public:
    Session(User &user, Computer &computer);
    void endSession();

    string getId();
    string getCost();
    string getStatus();

    void endSession(User &user, Computer &computer);

    void setId(string Id);
};

Session::Session(User &user, Computer &computer)
{
    user.setStatus("ONLINE");
    updateAccountToFile(user);
    computer.setStatus("InUse");
    updateComToFile(computer);

    status = "ACTIVE";
    cost = "0.000";
    // xử lí tiền
    string balance = user.getBalance();
    balance.erase(remove(balance.begin(), balance.end(), '.'), balance.end());
    string cost = computer.getCost();

    double temp = stod(balance) / stod(cost) * 3600;
    int seconds = int(temp);
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;

    Time time(hours, minutes, seconds);

    thread threadRunSesssion(runSession, user, computer, time);
    //  runSession(user, computer, time);
    threadRunSesssion.join();
}

string Session::getId() { return id; }

string Session::getCost() { return cost; }

string Session::getStatus() { return status; }

void Session::setId(string Id) { id = Id; }

void Session::endSession(User &user, Computer &computer)
{
    user.setStatus("OFFLINE");
    computer.setStatus("NotInUse");
}

void runSession(User &user, Computer &computer, Time &time)
{

    string path = "./session/" + user.getId() + "_" + computer.getId() + ".txt";

    fstream file(path, ios::out);

    while (true)
    {
        file.seekp(0);
        file << time;
        Time temp;
        file >> temp;
        time = temp;
        time--;

        if (time.isZero())
        {

            user.setStatus("OFFLINE");
            computer.setStatus("NotInUse");

            // xóa file
            // thanh toán
            break;
        }
        Sleep(1000);
    }

    file.close();
}

#endif