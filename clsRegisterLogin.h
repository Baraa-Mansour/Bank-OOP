#pragma once
#include <iostream>
#include <string>
#include "Global.h"
#include "clsDate.h"
#include "clsFile.h"

using namespace std;


class clsRegisterLogin
{
private:
    static const string _RegisterLoginFilePath;
	string _UserName;
	string _Password;
	string _DateTime;
	int _Permissions;

    clsRegisterLogin()
    {
        this->UserName = CurrentUser.UserName;
        this->Password = CurrentUser.Password;
        this->DateTime = clsDate::GetSystemDateTimeString();
        this->Permissions = CurrentUser.Permissions;
    }

    static string _ConverObjectToLine(clsRegisterLogin Object, string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += Object.UserName + Seperator;
        LoginRecord += Object.Password + Seperator;
        LoginRecord += to_string(Object.Permissions);
        return LoginRecord;
    }
    static void _SaceObjectToFile(clsRegisterLogin Object)
    {
        string Line = _ConverObjectToLine(Object);
        clsFile::SaveLine(Line, _RegisterLoginFilePath);
    }

public:
    std::string GetUserName() const { return _UserName; }
    std::string GetPassword() const { return _Password; }
    std::string GetDateTime() const { return _DateTime; }
    int GetPermissions() const { return _Permissions; }

    // Setters
    void SetUserName(const std::string& value) { _UserName = value; }
    void SetPassword(const std::string& value) { _Password = value; }
    void SetDateTime(const std::string& value) { _DateTime = value; }
    void SetPermissions(int value) { _Permissions = value; }

    // Property definitions
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
    __declspec(property(get = GetDateTime, put = SetDateTime)) string DateTime;
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static void RigisterLogin()
	{
        clsRegisterLogin Object = clsRegisterLogin();

        _SaceObjectToFile(Object);
	}
};
const string clsRegisterLogin::_RegisterLoginFilePath = "LoginRegister.txt";
