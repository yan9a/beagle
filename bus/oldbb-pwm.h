#ifndef BBPWM_H_INCLUDED
#define BBPWM_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
//http://www.cplusplus.com/reference/fstream/fstream/
//ww.cplusplus.com/articles/D9j2Nwbp/
#define PWMPATH "/sys/devices/ocp.3/pwm_test_"
using namespace std;

class BBPWM{
	string fpath;
public:
	BBPWM(string header_pin);
	void Period(int t_ns);
	void Duty(int t_ns);
	void Run(bool v);
};

#endif // BBPWM_H_INCLUDED
