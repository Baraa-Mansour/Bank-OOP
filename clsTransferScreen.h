#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : public clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber;
        cout << "\nBalance     : " << Client.Balance;
        cout << "\n___________________\n";
    }

    static string _ReadExistAccoutNumber(string Meesage)
    {
        string AccountNumber = "";

        AccountNumber = clsInputValidate::ReadString(Meesage);
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString("");
        }

        return AccountNumber;
    }

    static double _ReadTransferAmount(clsBankClient FromClient)
    {
        double Amount =  clsInputValidate::ReadNumberBetween<double>(0, std::numeric_limits<double>::max(), "\nPlease enter Transfer amount? ");
        while (Amount > FromClient.Balance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadNumberBetween<double>(0, std::numeric_limits<double>::max(), "");
        }
        return Amount;
    }
public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t  Transfer Screen");

        string FromAccountNumber = _ReadExistAccoutNumber("\nPlease Enter Account Number To Transfer From: ");
        clsBankClient FromClient = clsBankClient::Find(FromAccountNumber);
        _PrintClient(FromClient);

        string ToAccountNumber = _ReadExistAccoutNumber("\nPlease Enter Account Number To Transfer To: ");
        clsBankClient ToClient = clsBankClient::Find(ToAccountNumber);
        _PrintClient(ToClient);

        double Amount = _ReadTransferAmount(FromClient);

        if (clsInputValidate::ReadYorN("\nAre you sure you want to perform this operation? y/n? "))
        {
            if (FromClient.Transfer(Amount, ToClient))
            {
                cout << "\nTransfer done successfully\n";
                FromClient.RegisterTransferLog(Amount, ToClient, CurrentUser.UserName);
            }
            else
                cout << "\nTransfer Faild \n";
        }

        _PrintClient(FromClient);
        _PrintClient(ToClient);

        Pause("Enter Any Key To Back To Transaction Menu ...");
    }
};
