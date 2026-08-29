#pragma once
#include<iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"

using namespace std;


class clsMainScreen : public clsScreen
{
private:
    enum enMainMenueOptions 
    {
        eListClients = 1, 
        eAddNewClient = 2, 
        eDeleteClient = 3,
        eUpdateClient = 4, 
        eFindClient = 5, 
        eShowTransactionsMenue = 6,
        eManageUsers = 7, 
        eLogout = 8
    };


	static void _DrawMainmenuList()
	{
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
	}
    static enMainMenueOptions _GetMainmenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        return (enMainMenueOptions)clsInputValidate::ReadIntNumberBetween(1, 8, "");
    }
    static void _PerformMainmenuOption(enMainMenueOptions Option)
    {
        system("cls");

        switch (Option)
        {
        case clsMainScreen::eListClients:
            _ShowAllClientsScreen();
            break;
        case clsMainScreen::eAddNewClient:
            _ShowAddNewClientsScreen();
            break;
        case clsMainScreen::eDeleteClient:
            _ShowDeleteClientScreen();
            break;
        case clsMainScreen::eUpdateClient:
            _ShowUpdateClientScreen();
            break;
        case clsMainScreen::eFindClient:
            _ShowFindClientScreen();
            break;
        case clsMainScreen::eShowTransactionsMenue:
            _ShowTransactionsMenue();
            break;
        case clsMainScreen::eManageUsers:
            _ShowManageUsersMenue();
            break;
        case clsMainScreen::eLogout:
            _Logout();
            break;
        default:
            break;
        }

        if ((Option != enMainMenueOptions::eLogout) &&
            (Option != enMainMenueOptions::eShowTransactionsMenue) &&
            (Option != enMainMenueOptions::eManageUsers))
        {
            cout << "Enter Any Key To Back To Mainmenu ...";
            system("pause > 0");
        }
    }


    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("");
    }
public:
	static void ShowMainmenuScreen()
	{
        enMainMenueOptions Option;
        
        do
        {
            system("cls");
            _DrawScreenHeader("\t\tMainmenu");
            _DrawMainmenuList();

            Option = _GetMainmenuOption();

            _PerformMainmenuOption(Option);
        } while (Option != enMainMenueOptions::eLogout);
	}
};

