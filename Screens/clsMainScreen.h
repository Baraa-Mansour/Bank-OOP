#pragma once
#include <iostream>
#include <iomanip>

#include "../Libs/clsInputValidate.h"

#include "clsScreen.h"
#include "Transaction/clsTransactionsScreen.h"
#include "User/clsManageUsersScreen.h"
#include "Login/clsLoginRegisterScreen.h"
#include "Currency/clsCurrencyExchangeMainScreen.h"
#include "Client/clsClientListScreen.h"
#include "Client/clsAddNewClientScreen.h"
#include "Client/clsDeleteClientScreen.h"
#include "Client/clsUpdateClientScreen.h"
#include "Client/clsFindClientScreen.h"

#include "../Global.h"


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
        eLoginRegister = 8,
        eCurrencyExchange = 9,
        eLogout = 10
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
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
	}
    static enMainMenueOptions _GetMainmenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        return (enMainMenueOptions)clsInputValidate::ReadNumberBetween<short>(1, 10, "");
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
        case clsMainScreen::eLoginRegister:
            _ShowLoginRegisterScreen();
            break;
        case clsMainScreen::eCurrencyExchange:
            _ShowCurrencyExchangeMainScreen();
            break;
        case clsMainScreen::eLogout:
            _Logout();
            break;
        default:
            break;
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

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
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

