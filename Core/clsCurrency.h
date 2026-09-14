#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../Libs/clsString.h"
#include "../Libs/clsFile.h"


class clsCurrency
{

private:
    static const string _CurrencyFilePath;
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    double _Rate;

    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Seperator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
            stod(vCurrencyData[3]));
    }
    static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string stCurrencyRecord = "";

        stCurrencyRecord += Currency.Country + Seperator;
        stCurrencyRecord += Currency.CurrencyCode + Seperator;
        stCurrencyRecord += Currency.CurrencyName + Seperator;
        stCurrencyRecord += to_string(Currency.Rate);

        return stCurrencyRecord;
    }

    static void _SaveCurrencyVectorToFile(vector<clsCurrency> vCurrencies)
    {
        vector<string> vLines;

        for (const clsCurrency& Currency : vCurrencies)
        {
            string Line = _ConverCurrencyObjectToLine(Currency);
            vLines.push_back(Line);
        }
        clsFile::SaveLineVector(vLines, _CurrencyFilePath);
    }

    void _Update()
    {
        vector <clsCurrency> _vCurrencys = GetAllCurrencies();

        for (clsCurrency& Currency : _vCurrencys)
        {
            if (Currency.CurrencyCode == CurrencyCode)
            {
                Currency = *this;
                break;
            }
        }
        _SaveCurrencyVectorToFile(_vCurrencys);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    clsCurrency()
    {
        _Mode = EmptyMode;
        _Country = "";
        _CurrencyCode = "";
        _CurrencyName = "";
        _Rate = 0;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string GetCountry()
    {
        return _Country;
    }
    string GetCurrencyCode()
    {
        return _CurrencyCode;
    }
    string GetCurrencyName()
    {
        return _CurrencyName;
    }
    double GetRate()
    {
        return _Rate;
    }

    __declspec(property(get = GetCountry)) string Country;
    __declspec(property(get = GetCurrencyCode)) string CurrencyCode;
    __declspec(property(get = GetCurrencyName)) string CurrencyName;
    __declspec(property(get = GetRate)) double Rate;

    void UpdateRate(double NewRate)
    {
        if (NewRate <= 0)
            return;
        this->_Rate = NewRate;
        this->_Update();
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open(_CurrencyFilePath, ios::in); //read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open(_CurrencyFilePath, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());
    }

    static vector<clsCurrency> GetAllCurrencies()
    {
        vector<string> vLines = clsFile::GetAllLines(_CurrencyFilePath);
        vector<clsCurrency> vCurrencies;

        for (string& Line : vLines)
        {
            clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
            vCurrencies.push_back(Currency);
        }
        return vCurrencies;
    }

    double ConvertToUSD(double Amount)
    {
        return (double)(Amount / Rate);
    }

    double ConvertToOtherCurrency(double Amount, clsCurrency Currency2)
    {
        double AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode == "USD")
        {
            return AmountInUSD;
        }

        return (double)(AmountInUSD * Currency2.Rate);
    }
};
const string clsCurrency::_CurrencyFilePath = "D:/courses/Course 11/Bank-OOP/Data/Currencies.txt";