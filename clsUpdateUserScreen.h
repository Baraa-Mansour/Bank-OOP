#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : public clsScreen

{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

    static void _ReadUserInfo(clsUser& User)
    {
        User.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");

        User.LastName = clsInputValidate::ReadString("\nEnter LastName: ");

        User.Email = clsInputValidate::ReadString("\nEnter Email: ");

        User.Phone = clsInputValidate::ReadString("\nEnter Phone: ");

        User.Password = clsInputValidate::ReadString("\nEnter Password: ");

        cout << "\nEnter Permissions: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;

        if (clsInputValidate::ReadYorN("\nDo you want to give full access? y/n? "))
            return -1;

        cout << "\nDo you want to give access to : \n ";

        if (clsInputValidate::ReadYorN("\nShow Client List? y/n? "))
            Permissions += clsUser::enPermissions::pListClients;

        if (clsInputValidate::ReadYorN("\nAdd New Client? y/n? "))
            Permissions += clsUser::enPermissions::pAddNewClient;

        if (clsInputValidate::ReadYorN("\nDelete Client? y/n? "))
            Permissions += clsUser::enPermissions::pDeleteClient;

        if (clsInputValidate::ReadYorN("\nUpdate Client? y/n? "))
            Permissions += clsUser::enPermissions::pUpdateClients;

        if (clsInputValidate::ReadYorN("\nFind Client? y/n? "))
            Permissions += clsUser::enPermissions::pFindClient;

        if (clsInputValidate::ReadYorN("\nTransactions? y/n? "))
            Permissions += clsUser::enPermissions::pTranactions;

        if (clsInputValidate::ReadYorN("\nManage Users? y/n? "))
            Permissions += clsUser::enPermissions::pManageUsers;

        if (clsInputValidate::ReadYorN("\nShow Login Register List? y/n? "))
            Permissions += clsUser::enPermissions::pLoginRegister;

        return Permissions;
    }

    static string _ReadExistUserName()
    {
        string UserName = "";

        UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString("");
        }

        return UserName;
    }
public:

    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = _ReadExistUserName();

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        if (clsInputValidate::ReadYorN("\nAre you sure you want to update this User y/n? "))
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult = User1.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User1);

                break;
            case clsUser::enSaveResults::svFaildEmptyObject:
                cout << "\nError User was not saved because it's Empty";

                break;
            }
        }
        Pause("Enter Any Key To Back To User Manage Menu ...");
    }
};
