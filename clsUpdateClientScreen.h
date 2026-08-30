#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : public clsScreen

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

    static void _ReadClientInfo(clsBankClient& Client)
    {
        Client.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");

        Client.LastName = clsInputValidate::ReadString("\nEnter LastName: ");

        Client.Email = clsInputValidate::ReadString("\nEnter Email: ");

        Client.Phone = clsInputValidate::ReadString("\nEnter Phone: ");

        Client.PinCode = clsInputValidate::ReadString("\nEnter PinCode: ");

        Client.Balance = clsInputValidate::ReadNumber<double>("\nEnter Account Balance: ");
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

    static void ShowUpdateClientScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            _ShowAccessDeniedScreen();
            return;
        }
        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = clsUpdateClientScreen::_ReadExistAccoutNumber();

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);

        if (clsInputValidate::ReadYorN("\nAre you sure you want to update this client y/n? "))
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
                cout << "\nAccount Updated Successfully :-)\n";

                _PrintClient(Client1);
                break;
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }

        Pause();
    }
};
