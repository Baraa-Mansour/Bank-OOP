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

        string UserName = clsInputValidate::ReadString("Enter UserName: ");
        string Password = clsInputValidate::ReadString("Enter Password: ");

        while (!_Login(UserName, Password))
        {
            cout << "\nInvalid UserName/Password, Try Again." << endl << endl;

            UserName = clsInputValidate::ReadString("Enter UserName: ");
            Password = clsInputValidate::ReadString("Enter Password: ");
        }
    }
};
