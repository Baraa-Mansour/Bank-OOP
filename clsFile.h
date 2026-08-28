#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;


class clsFile
{
public:
	static vector<string> GetAllLines(string FilePath)
	{
		vector<string> vLines;
		fstream File;

		File.open(FilePath, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				vLines.push_back(Line);
			}

			File.close();
		}

		return vLines;
	}
	static void SaveLineVector(vector<string> vLines, string FilePath) // Override File
	{
		fstream File;
		File.open(FilePath, ios::out);

		if (File.is_open())
		{
			for (const string& Line : vLines)
				File << Line << endl;

			File.close();
		}
	}
	static void SaveLine(string Line, string FilePath)
	{
		fstream File;
		File.open(FilePath, ios::app);

		if (File.is_open())
		{
			File << Line << endl;

			File.close();
		}
	}
};

