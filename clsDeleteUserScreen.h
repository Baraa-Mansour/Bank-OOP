#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsDeleteUserScreen : public clsScreen
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
        cout << "\nUser Name   : " << User.UserName;
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
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\tDelete User Screen");

        string UserName = _ReadExistUserName();

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);


        if (clsInputValidate::ReadYorN("\nAre you sure you want to delete this User y/n? "))
        {

            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
        Pause("Enter Any Key To Back To User Manage Menu ...");
    }
};
