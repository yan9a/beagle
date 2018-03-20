//File: ce_ai.cpp
//Description: Reading analog input pins
//WebSite: http://cool-emerald.blogspot.sg
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2017 Yan Naing Aye

#include "ce_ai.h"

template <typename T>
    string CE_Ai::n2s(T Number)
    {
     ostringstream ss;
     ss << Number;
     return ss.str();
    }

template <typename T>
    T CE_Ai::s2n(const string &Text)
    {
     istringstream ss(Text);
     T result;
     return ss >> result ? result : 0;
    }

CE_Ai::CE_Ai(long ain)
{
    fpath = AIPATH+n2s(ain)+"_raw";
}

int CE_Ai::Read()
{
    string str;
    ifstream rfile;
    int val=0;
    rfile.open(fpath.c_str());
	if (rfile.is_open()) {
		if (getline(rfile,str)) {
			val = s2n<int>(str);
		}
	}
	rfile.close();
	return val;
}

