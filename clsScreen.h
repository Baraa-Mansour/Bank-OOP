#pragma once
#include<iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;


class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.UserName << "\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static void _ShowAccessDeniedScreen()
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        Pause("Enter Any Key To Back To Mainmenu ...");
    }

    static bool _CheckAccessRights(clsUser::enPermissions Permission)
    {
        return CurrentUser.CheckAccessPermission(Permission);
    }

    static void Pause(string Message = "Enter Any Key To Back To Mainmenu ...")
    {
        cout << Message;
        system("pause > 0");
    }
};

