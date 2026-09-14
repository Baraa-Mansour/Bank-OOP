#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"

#include "../Libs/clsString.h"
#include "../Libs/clsFile.h"
#include "../Libs/clsUtil.h"


using namespace std;


class clsUser : public clsPerson
{
private:
    static const string _UsersFilePath;
    enum enMode 
    { 
        EmptyMode = 0, 
        UpdateMode = 1, 
        AddNewMode = 2 
    };


    string _UserName;
    string _Password;
    int _Permissions;

    enMode _Mode;
    bool _MarkedForDelete = false;

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string UserName, string Password, int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }


    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5], 2), stoi(vUserData[6]));
    }
    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password, 2) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;
    }
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static void _SaveUserToFile(clsUser User)
    {
        string Line = _ConverUserObjectToLine(User);

        clsFile::SaveLine(Line, _UsersFilePath);
    }
    static void _SaveUserVectorToFile(vector<clsUser> vUsers)
    {
        vector<string> vLines;
        string Line = "";

        for (const clsUser& User : vUsers)
        {
            if (!User._MarkedForDelete)
            {
                Line = _ConverUserObjectToLine(User);
                vLines.push_back(Line);
            }
        }

        clsFile::SaveLineVector(vLines, _UsersFilePath);
    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open(_UsersFilePath, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    void _Update()
    {
        bool IsFound = false;

        vector <clsUser> vUsers = clsUser::GetAllUsers();

        for (clsUser& User : vUsers)
        {
            if (User.UserName == UserName)
            {
                User = *this;
                IsFound = true;
                break;
            }
        }

        if (IsFound)
        {
            _SaveUserVectorToFile(vUsers);
        }
    }
    void _AddNew()
    {
        clsFile::SaveLine(_ConverUserObjectToLine(*this), _UsersFilePath);
    }

public:
    enum enPermissions 
    {
        pListClients = 1, 
        pAddNewClient = 2, 
        pDeleteClient = 4,
        pUpdateClients = 8, 
        pFindClient = 16, 
        pTranactions = 32, 
        pManageUsers = 64,
        pLoginRegister = 128
    };
    enum enSaveResults 
    { 
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2 
    };


    // Properties
    string GetUserName()
    {
        return _UserName;
    }
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
    // ---------------  
    
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetAllUsers()
    {
        vector<clsUser> vUsers;
        vector<string> vLines = clsFile::GetAllLines(_UsersFilePath);

        for (string& Line : vLines)
        {
            clsUser User = _ConvertLinetoUserObject(Line);
            vUsers.push_back(User);
        }

        return vUsers;
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open(_UsersFilePath, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }

        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName, string Password)
    {
        clsUser User = clsUser::Find(UserName);

        if (User.IsEmpty())
            return User;

        return User.Password == Password ? User : _GetEmptyUserObject();
    }

    enSaveResults Save()
    {
        switch (this->_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFaildEmptyObject;

        case enMode::UpdateMode:
            this->_Update();
            return enSaveResults::svSucceeded;

        case enMode::AddNewMode:
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                this->_AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        default:
            return enSaveResults::svFaildEmptyObject;
        }
    }

    bool Delete()
    {
        bool IsFound = false;
        vector <clsUser> _vUsers = clsUser::GetAllUsers();

        for (clsUser& User : _vUsers)
        {
            if (User.UserName == _UserName)
            {
                User._MarkedForDelete = true;
                IsFound = true;

                break;
            }
        }

        if (IsFound)
        {
            _SaveUserVectorToFile(_vUsers);
            *this = _GetEmptyUserObject();
        }

        return IsFound;
    }

    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        return (this->Permissions & Permission) == Permission;
    }
};
const string clsUser::_UsersFilePath = "Data\\Users.txt";
