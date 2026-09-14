#pragma once
#include <iostream>
#include <iomanip>

#include "../../Libs/clsUtil.h"

#include "../../Core/clsBankClient.h"

#include "../clsScreen.h"


class clsTotalBalancesScreen : public clsScreen
{

private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Balance;
    }
    static void _DrawTableHeader()
    {
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance" << endl;
        cout << setw(16) << left << "" << "_______________________________________________________";
        cout << "__________________________\n" << endl;
    }
    static void _DrawTableFooter(double TotalBalances)
    {
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t  ( " << clsUtil::NumberToText((int)TotalBalances) << ")" << endl;
    }

public:

    static void ShowTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetAllClients();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);
        _DrawTableHeader();

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
        {
            for (clsBankClient Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        }
            
        _DrawTableFooter(TotalBalances);
        Pause("Enter Any Key To Back To Transaction Menu ...");
    }
};
