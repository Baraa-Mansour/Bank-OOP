#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"
#include "clsMainScreen.h"
#include "clsLoginScreen.h"

int main()
{
    while (true)
    {
        clsLoginScreen::ShowLoginScreen();
        if (IsSystemLocked)
        {
            break;
        }
        clsMainScreen::ShowMainmenuScreen();
    }

    if (IsSystemLocked)
        cout << endl << endl << "System Locked!!" << endl;
    return 0;
}