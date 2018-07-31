//File: ce_ai.h
//Description: Reading analog input pins
//WebSite: http://cool-emerald.blogspot.com
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2018 Yan Naing Aye

#ifndef CE_AI_H
#define CE_AI_H

#include <string>
#include <fstream>
#include <sstream>
#define AIPATH "/sys/bus/iio/devices/iio:device0/in_voltage"
using namespace std;

class CE_Ai{
	string fpath;
public:
	CE_Ai(long ain);
	int Read();
	template <typename T>
        string n2s(T Number);
    template <typename T>
        T s2n(const string &Text);
};

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


#endif
