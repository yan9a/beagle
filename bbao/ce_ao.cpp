//File: ce_ao.cpp
//Description: pwm output
//WebSite: http://cool-emerald.blogspot.com
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2018 Yan Naing Aye

#include "ce_ao.h"

CE_Ao::CE_Ao(int pwm_chip_no,int pwm_output_no)
{
    Begin(pwm_chip_no,pwm_output_no);
}

CE_Ao::~CE_Ao()
{
// if unexported, pwm cannot be exported again, requiring reboot
//    ofstream wfile;
//    string epath=CE_PWMPATH;
//    epath+=n2s(m_chip)+"/unexport";
//    wfile.open(epath.c_str());
//    if (wfile.is_open()) {
//        wfile << m_output;
//    }
//    wfile.close();
}

int CE_Ao::Begin(int pwm_chip_no,int pwm_output_no)
{
    m_chip=pwm_chip_no;
    m_output=pwm_output_no;
    fpath = CE_PWMPATH+n2s(m_chip)+"/pwm"+n2s(m_output);
    if(Export()<0) return -1;
    return 0;
}

int CE_Ao::Export()
{
    ofstream wfile;
    int r=-1;
    string epath=CE_PWMPATH;
    epath+=n2s(m_chip)+"/export";
    wfile.open(epath.c_str());
    if (wfile.is_open()) {
        wfile << m_output;
        r=0;
    }
    wfile.close();
    return r;
}

int CE_Ao::Period(int t_ns)
{
    ofstream wfile;
    string path=fpath;
    int r=-1;

    path+="/period";
    wfile.open(path.c_str());
    if (wfile.is_open()) {
        wfile << t_ns;
        r=0;
    }
    wfile.close();
    return r;
}


int CE_Ao::Duty(int t_ns)
{
    ofstream wfile;
    string path=fpath;
    int r=-1;

    path+="/duty_cycle";
    wfile.open(path.c_str());
    if (wfile.is_open()) {
        wfile << t_ns;
        r=0;
    }
    wfile.close();
    return r;
}

int CE_Ao::Enable(bool v)
{
    ofstream wfile;
    string path=fpath;
    int r=-1;

    path+="/enable";
    wfile.open(path.c_str());
    if (wfile.is_open()) {
        wfile << (v?1:0);
        r=0;
    }
    wfile.close();
    return r;
}

template <typename T>
    string CE_Ao::n2s(T Number)
    {
     ostringstream ss;
     ss << Number;
     return ss.str();
    }

//template <typename T>
//    T CE_Ao::s2n(const string &Text)
//    {
//     istringstream ss(Text);
//     T result;
//     return ss >> result ? result : 0;
//    }
