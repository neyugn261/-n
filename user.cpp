#include "user.h"


User::User() : Account() {
    balance = "0.000";
}

User::~User() {};

string User::getBalance() { return balance; }





