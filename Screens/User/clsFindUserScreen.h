#pragma once
#include <iostream>

#include "../../Libs/clsInputValidate.h"

#include "../../Core/clsPerson.h"
#include "../../Core/clsUser.h"

#include "../clsScreen.h"


class clsFindUserScreen : public clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

    static string _ReadExistUserName()
    {
        string UserName = "";

        UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString("");
        }

        return UserName;
    }

public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");

        string UserName = _ReadExistUserName();

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);
        Pause("Enter Any Key To Back To User Manage Menu ...");
    }
};
