#include "bbpwm.h"

BBPWM::BBPWM(string header_pin)
{
    fpath = PWMPATH+header_pin+".17";
}

void BBPWM::Period(int t_ns)
{
    ofstream wfile;
    string path=fpath;
    path+="/period";
    wfile.open(path.c_str());
    if (wfile.is_open()) {wfile << t_ns;}
    wfile.close();
}


void BBPWM::Duty(int t_ns)
{
    ofstream wfile;
    string path=fpath;
    path+="/duty";
    wfile.open(path.c_str());
    if (wfile.is_open()) {wfile << t_ns;}
    wfile.close();
}

void BBPWM::Run(bool v)
{
    ofstream wfile;
    string path=fpath;
    path+="/run";
    wfile.open(path.c_str());
    if (wfile.is_open()) {wfile << (v?"1":"0");}
    wfile.close();
}
