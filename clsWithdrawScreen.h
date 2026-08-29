#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : public clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber;
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.Balance;
        cout << "\n___________________\n";
    }

    static string _ReadExistAccoutNumber()
    {
        string AccountNumber = "";

        AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString("");
        }

        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = _ReadExistAccoutNumber();

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = clsInputValidate::ReadDblNumberBetween(0, std::numeric_limits<double>::max(), "\nPlease enter deposit amount? ");

        if (clsInputValidate::ReadYorN("\nAre you sure you want to perform this transaction? "))
        {
            if (Client1.Withdraw(Amount))
            {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.Balance << endl;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client1.Balance << endl;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};
