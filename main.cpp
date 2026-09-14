#include <iostream>
#include <iomanip>

#include "Libs/clsInputValidate.h"
#include "Libs/clsUtil.h"

#include "Core/clsBankClient.h"

#include "Screens/clsMainScreen.h"
#include "Screens/Login/clsLoginScreen.h"


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