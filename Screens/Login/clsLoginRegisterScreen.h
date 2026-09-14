#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

#include "../../Core/clsUser.h"
#include "../../Core/clsLoginRegister.h"

#include "../clsScreen.h"

#include "../../Global.h"


class clsLoginRegisterScreen : public clsScreen
{

private:

    static void _PrintLoginRegisterRecordLine(clsLoginRegister LoginRegisterRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    }

    static void _DrawTableHeader()
    {
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

public:

    static void ShowLoginRegisterScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            _ShowAccessDeniedScreen();
            return;
        }
        vector <clsLoginRegister> vLoginRegisterRecord = clsLoginRegister::GetLoginRegisterList();

        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        _DrawTableHeader();

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else
        {
            for (clsLoginRegister& Record : vLoginRegisterRecord)
            {
                _PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }
        }   

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        Pause();
    }
};
