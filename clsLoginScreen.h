#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : public clsScreen
{

private:

    static  bool _Login(string UserName, string Password)
    {
        CurrentUser = clsUser::Find(UserName, Password);

        return !CurrentUser.IsEmpty();
    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");

        short FailedLoginCounter = 1;
        string UserName = clsInputValidate::ReadString("Enter UserName: ");
        string Password = clsInputValidate::ReadString("Enter Password: ");

        while (!_Login(UserName, Password) && FailedLoginCounter != 3)
        {
            cout << "\nInvalid UserName/Password, Try Again." << endl;
            cout << "You Have [" << (3-FailedLoginCounter) << "] Trials To Login" << endl << endl;

            FailedLoginCounter++;

            UserName = clsInputValidate::ReadString("Enter UserName: ");
            Password = clsInputValidate::ReadString("Enter Password: ");
        }

        if (FailedLoginCounter == 3)
        {
            IsSystemLocked = true;
        }
    }
};
