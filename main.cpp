#include "function.h"
#include "admin.h"


using namespace std;

int main()
{
    SetConsoleOutputCP(65001);

    Account account;
    if (account.login())
    {
        if (account.getRole() == "ADMIN")
        {
            string id = account.getId();
            string name = account.getName();
            string pass = account.getPass();

            Admin admin(id, name, pass);
            menuAdmin(admin);
        }
    }

    return 0;
}