#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsLoginRegister.h"

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

        bool IsFailedLogIn = false;
        short FailedLoginCounter = 0;

        string UserName = "";
        string Password = "";

        do
        {
            if (IsFailedLogIn)
            {
                FailedLoginCounter++;
                cout << "\nInvalid UserName/Password, Try Again." << endl;
                cout << "You Have [" << (3 - FailedLoginCounter) << "] Trials To Login" << endl << endl;
            }

            if (FailedLoginCounter == 3)
            {
                IsSystemLocked = true;
                return;
            }

            UserName = clsInputValidate::ReadString("Enter UserName: ");
            Password = clsInputValidate::ReadString("Enter Password: ");

            IsFailedLogIn = !_Login(UserName, Password);

        } while (IsFailedLogIn);

        clsLoginRegister::RigisterLogin();
    }
};
