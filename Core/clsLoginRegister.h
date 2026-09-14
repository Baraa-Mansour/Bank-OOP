#pragma once
#include <iostream>
#include <string>

#include "../Libs/clsDate.h"
#include "../Libs/clsFile.h"
#include "../Libs/clsUtil.h"

#include "../Global.h"


using namespace std;


class clsLoginRegister
{
private:
    static const string _RegisterLoginFilePath;
	string _UserName;
	string _Password;
	string _DateTime;
	int _Permissions;

    clsLoginRegister()
    {
        this->UserName = CurrentUser.UserName;
        this->Password = CurrentUser.Password;
        this->DateTime = clsDate::GetSystemDateTimeString();
        this->Permissions = CurrentUser.Permissions;
    }

    static string _ConverObjectToLine(clsLoginRegister Object, string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += Object.DateTime + Seperator;
        LoginRecord += Object.UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(Object.Password, ENCRYPTION_KEY) + Seperator;
        LoginRecord += to_string(Object.Permissions);
        return LoginRecord;
    }
    static clsLoginRegister _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        clsLoginRegister LoginRegisterRecord;

        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);

        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2], ENCRYPTION_KEY);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

    static void _SaveObjectToFile(clsLoginRegister Object)
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
        clsLoginRegister Object = clsLoginRegister();

        _SaveObjectToFile(Object);
	}

    static  vector <clsLoginRegister> GetLoginRegisterList()
    {
        vector<string> vLines = clsFile::GetAllLines(_RegisterLoginFilePath);
        vector <clsLoginRegister> vLoginRegisterRecord;

        for (string Line : vLines)
        {
            clsLoginRegister Record = _ConvertLoginRegisterLineToRecord(Line);
            vLoginRegisterRecord.push_back(Record);
        }

        return vLoginRegisterRecord;
    }
};
const string clsLoginRegister::_RegisterLoginFilePath = "Data\\LoginRegister.txt";
