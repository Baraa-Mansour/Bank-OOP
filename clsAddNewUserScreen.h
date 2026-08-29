#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsAddNewUserScreen : public clsScreen
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

        return Permissions;
    }

    static string _ReadUniqueUserName()
    {
        string UserName = "";

        UserName = clsInputValidate::ReadString("\nPlease Enter UserName : ");
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString("");
        }

        return UserName;
    }

public:

    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = _ReadUniqueUserName();

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "\nError User was not saved because it's Empty";
            break;
        case clsUser::enSaveResults::svFaildUserExists:
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
        Pause("Enter Any Key To Back To User Manage Menu ...");
    }
};
