#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"

using namespace std;

class clsManageUsersScreen : public clsScreen
{
private:
    enum enManageUsersMenueOptions 
    {
        eListUsers = 1,
        eAddNewUser = 2, 
        eDeleteUser = 3,
        eUpdateUser = 4, 
        eFindUser = 5, 
        eMainMenue = 6
    };


    static enManageUsersMenueOptions _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";

        enManageUsersMenueOptions Option = 
            (enManageUsersMenueOptions)clsInputValidate::ReadIntNumberBetween(1, 6, "", "Enter Number between 1 to 6? ");

        return Option;
    }
    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {
        system("cls");
        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
            _ShowListUsersScreen();
            break;

        case enManageUsersMenueOptions::eAddNewUser:
            _ShowAddNewUserScreen();
            break;

        case enManageUsersMenueOptions::eDeleteUser:
            _ShowDeleteUserScreen();
            break;

        case enManageUsersMenueOptions::eUpdateUser:
            _ShowUpdateUserScreen();
            break;

        case enManageUsersMenueOptions::eFindUser:
            _ShowFindUserScreen();
            break;
        case enManageUsersMenueOptions::eMainMenue:
        default:
            break;
        }

        if (ManageUsersMenueOption != eMainMenue)
        {
            cout << "Enter Any Key To Back To User Manage menu ...";
            system("pause > 0");
        }
    }
    static void _DrawUserManagemenuList()
    {
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }


    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        cout << "\nUpdate User Screen Will Be Here.\n";
    }

    static void _ShowFindUserScreen()
    {
        cout << "\nFind User Screen Will Be Here.\n";
    }

public:
    static void ShowManageUsersMenue()
    {
        enManageUsersMenueOptions Option;

        do
        {
            system("cls");
            _DrawScreenHeader("\t Manage Users Screen");
            _DrawUserManagemenuList();

            Option = _ReadManageUsersMenueOption();

            _PerformManageUsersMenueOption(Option);
        } while (Option != enManageUsersMenueOptions::eMainMenue);      
    }
};
