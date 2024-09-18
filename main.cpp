#include "user.h"
#include "admin.h"
#include "function.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);

    Account account;
    if (account.login())
    {
        if (account.getRole() == "ADMIN")
        {
            cout << "\nhi";
        }
    }

    return 0;
}