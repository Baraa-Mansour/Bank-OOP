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
        clsMainScreen::ShowMainmenuScreen();
    }
    return 0;
}