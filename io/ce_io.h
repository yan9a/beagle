//File: ce_io.h
//Description: Controlling GPIO pins
//WebSite: http://cool-emerald.blogspot.com
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2018 Yan Naing Aye

#ifndef CE_IO_H
#define CE_IO_H

#include <string>
#include <fstream>
#include <sstream>
#define IOPATH "/sys/class/gpio/"
using namespace std;
typedef enum {INPUT=0,OUTPUT=1} iodir;
typedef enum {LOW=0,HIGH=1} digitalval;

class CE_IO{
	string fpath;
	int gpioNumber;
public:
    CE_IO();
	CE_IO(int gpiono,iodir mode);
	~CE_IO();
	int Begin(int gpiono,iodir mode);
	digitalval Read();
	int Write(digitalval b);
	int Export();
	int SetDirection(iodir mode);
	template <typename T>
        string ToString(T Number);
};


template <typename T>
string CE_IO::ToString(T a)
{
 ostringstream ss;
 ss << a;
 return ss.str();
}

CE_IO::CE_IO()
{

}

CE_IO::CE_IO(int gpiono,iodir mode)
{
    Begin(gpiono,mode);
}

int CE_IO::Begin(int gpiono,iodir mode)
{
    gpioNumber=gpiono;
    fpath = IOPATH;
    fpath+="gpio"+ToString(gpioNumber)+"/value";
    if(Export()<0) return -1;
    if(SetDirection(mode)<0) return -1;
    return 0;
}

int CE_IO::Export()
{
    ofstream wfile;
    int r=-1;
    string epath=IOPATH;
    epath+="export";
    wfile.open(epath.c_str());
    if (wfile.is_open()) {
        wfile << gpioNumber;
        r=0;
    }
    wfile.close();
    return r;
}

int CE_IO::SetDirection(iodir mode)
{
    ofstream wfile;
    int r=-1;
    string dirpath=IOPATH;
    dirpath+="gpio"+ToString(gpioNumber)+"/direction";
    wfile.open(dirpath.c_str());
    string modestr[2]={"in","out"};
    if (wfile.is_open()) {
        wfile << modestr[mode];
        r=0;
    }
    wfile.close();
    return r;
}


CE_IO::~CE_IO()
{
    ofstream wfile;
    string epath=IOPATH;
    epath+="unexport";
    //unexport the gpio
    wfile.open(epath.c_str());
    if (wfile.is_open()) {wfile << gpioNumber;}
    wfile.close();
}

digitalval CE_IO::Read()
{
    ifstream rfile;
    string str;
    digitalval rdv=LOW;
    rfile.open(fpath.c_str());
	if (rfile.is_open()) {
		getline(rfile,str);
	}
    else {
        str="";
    }
	rfile.close();
	if(str=="1") rdv=HIGH;
    return rdv;
}

int CE_IO::Write(digitalval b)
{
    ofstream wfile;
    int r=-1;
    wfile.open(fpath.c_str());
	if (wfile.is_open()) {
        wfile << b;
        r=0;
	}
	wfile.close();
    return r;
}

#endif
