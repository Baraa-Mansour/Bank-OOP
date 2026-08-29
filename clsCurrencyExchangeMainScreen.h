#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"


using namespace std;

class clsCurrencyExchangeMainScreen : public clsScreen
{

private:
    enum enCurrenciesMainMenueOptions 
    {
        eListCurrencies = 1,
        eFindCurrency = 2, 
        eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5
    };


    static void _DrawCurrencyList()
    {
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exhange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }

    static enCurrenciesMainMenueOptions ReadCurrenciesMainMenueOptions()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        enCurrenciesMainMenueOptions Choice = 
            (enCurrenciesMainMenueOptions)clsInputValidate::ReadIntNumberBetween(1, 5, "", "Enter Number between 1 to 5? ");
        return Choice;
    }
    static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions)
    {
        system("cls");
        switch (CurrenciesMainMenueOptions)
        {

        case enCurrenciesMainMenueOptions::eListCurrencies:
            _ShowCurrenciesListScreen();
            break;

        case enCurrenciesMainMenueOptions::eFindCurrency:
            _ShowFindCurrencyScreen();
            break;

        case enCurrenciesMainMenueOptions::eUpdateCurrencyRate:
            _ShowUpdateCurrencyRateScreen();
            break;

        case enCurrenciesMainMenueOptions::eCurrencyCalculator:
            _ShowCurrencyCalculatorScreen();
            break;

        case enCurrenciesMainMenueOptions::eMainMenue:
        default:
            break;

        }
    }


    static void _ShowCurrenciesListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        cout << "\nCurrency Calculator Screen Will Be Here.\n";
    }

public:
    static void ShowCurrenciesMenue()
    {
        enCurrenciesMainMenueOptions Option;
        do
        {
            system("cls");
            _DrawScreenHeader("    Currancy Exhange Main Screen");
            _DrawCurrencyList();

            Option = ReadCurrenciesMainMenueOptions();
            _PerformCurrenciesMainMenueOptions(Option);
        } while (Option != enCurrenciesMainMenueOptions::eMainMenue);
    }
};
