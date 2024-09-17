#ifndef _SESSION_H
#define _SESSION_H 1

#include <iostream>
#include <ctime>
#include "computer.h"
#include "account.h"
using namespace std;

class Session
{
private:
    int sessionId;
    Account *account;
    Computer *computer;
    time_t startTime;
    time_t endTime;
    bool isActive;

public:
    Session();
    Session(int sessionId, Account &account, Computer &computer);

    void endSession();
    int getSessionId();
};

Session::Session() : sessionId(-1), account(nullptr), computer(nullptr), isActive(false) {}

Session::Session(int sessionId, Account &account, Computer &computer)
    : sessionId(sessionId), account(&account), computer(&computer), isActive(true)
{
    computer.startUsage();
    startTime = time(nullptr);
}

void Session::endSession()
{
    if (isActive)
    {
        endTime = time(0);
        computer->endUsage();
        isActive = false;
    }
}

int Session::getSessionId() { return sessionId; }

#endif