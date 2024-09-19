#include "user.h"


User::User() : Account() {}

User::User(int &id, string &userName, string &password)
    : Account(id, userName, password, "USER") {}

User::~User() {};

float User::getBalance() { return balance; }

void User::addBalance(float amount) { balance += amount; }



