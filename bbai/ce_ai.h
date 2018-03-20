//File: ce_ai.h
//Description: Reading analog input pins
//WebSite: http://cool-emerald.blogspot.sg
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2017 Yan Naing Aye

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

#endif
