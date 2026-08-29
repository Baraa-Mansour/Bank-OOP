#pragma once
#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"

using namespace std;


class clsTransactionsScreen : public clsScreen
{
private:
    enum enTransactionsMenueOptions 
    {
        eDeposit = 1, 
        eWithdraw = 2,
        eShowTotalBalance = 3, 
        eShowMainMenue = 4
    };


    static void _DrawTransactionmenuList()
    {
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }
    static enTransactionsMenueOptions _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";

        enTransactionsMenueOptions Choice = 
            (enTransactionsMenueOptions)clsInputValidate::ReadIntNumberBetween(1, 4, "", "Enter Number between 1 to 4? ");

        return Choice;
    }
    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        system("cls");

        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
            _ShowDepositScreen();
            break;

        case enTransactionsMenueOptions::eWithdraw:
            _ShowWithdrawScreen();
            break;

        case enTransactionsMenueOptions::eShowTotalBalance:
            _ShowTotalBalancesScreen();
            break;

        case enTransactionsMenueOptions::eShowMainMenue:
        default:
            break;
        }
    }


    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

public:
    static void ShowTransactionsMenue()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            _ShowAccessDeniedScreen();
            return;
        }
        enTransactionsMenueOptions Option;
        do
        {
            system("cls");
            _DrawScreenHeader("\t  Transactions Screen");
            _DrawTransactionmenuList();

            Option = _ReadTransactionsMenueOption();

            _PerformTransactionsMenueOption(Option);

        } while (Option != enTransactionsMenueOptions::eShowMainMenue);
    }
};
