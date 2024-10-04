#include "function.h"
#include "admin.h"
#include "user.h"


int main()
{
    SetConsoleOutputCP(65001);

    Account account;
    if (account.login())
    {
        if (account.getRole() == "ADMIN")
        {
            Admin admin(account.getId(), account.getName(), account.getPass());
            menuAdmin(admin);
        }
        else
        {
            User user(account.getId(), account.getName(), account.getPass());
        }
    }

    return 0;
}