#pragma once
#include <iostream>

#include "../../Libs/clsInputValidate.h"

#include "../../Core/clsPerson.h"
#include "../../Core/clsBankClient.h"

#include "../clsScreen.h"



class clsDeleteClientScreen : public clsScreen
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
    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            _ShowAccessDeniedScreen();
            return;
        }
        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = _ReadExistAccoutNumber();

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        if (clsInputValidate::ReadYorN("\nAre you sure you want to delete this client y/n? "))
        {
            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
        Pause();
    }
};

