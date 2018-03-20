#ifndef CEUTIL_H
#define CEUTIL_H
#include <string>
#include <sstream>
using namespace std;

template <typename T>
string ToString(T Number)
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T FromString(const string &Text)
{
	istringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}
#endif
