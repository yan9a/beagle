//File: ce_ao.h
//Description: pwm output
//WebSite: http://cool-emerald.blogspot.com
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2018 Yan Naing Aye

#ifndef CE_AO_H
#define CE_AO_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

#define CE_PWMPATH "/sys/class/pwm/pwmchip"
using namespace std;

class CE_Ao{
	string fpath;
	int m_chip;
	int m_output;
public:
	CE_Ao(int pwm_chip_no,int pwm_output_no);
	~CE_Ao();
	int Begin(int pwm_chip_no,int pwm_output_no);
	int Export();
	int Period(int t_ns);
	int Duty(int t_ns);
	int Enable(bool v);
	template <typename T>
        string n2s(T Number);
//    template <typename T>
//        T s2n(const string &Text);
};

#endif // CE_AO_H
