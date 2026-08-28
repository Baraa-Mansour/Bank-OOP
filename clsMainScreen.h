#pragma once
#include<iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"

using namespace std;


class clsMainScreen : clsScreen
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
        eExit = 8
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
        case clsMainScreen::eExit:
            _ShowEndScreen();
            break;
        default:
            break;
        }

        if (Option != enMainMenueOptions::eExit)
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
        cout << "\nUpdate Client Screen Will be here...\n";

    }

    static void _ShowFindClientScreen()
    {
        cout << "\nFind Client Screen Will be here...\n";

    }

    static void _ShowTransactionsMenue()
    {
        cout << "\nTransactions Menue Will be here...\n";

    }

    static void _ShowManageUsersMenue()
    {
        cout << "\nUsers Menue Will be here...\n";

    }

    static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";

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
        } while (Option != enMainMenueOptions::eExit);
	}
};

