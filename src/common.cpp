#include "common.h"

#include <sstream>

std::vector<std::string> split(const std::string& str, char delim)
{
	using namespace std;
	vector<string> elems;
	stringstream ss(str);
	string elem;
	while(getline(ss, elem, delim))
	{
		elems.push_back(elem);
	}
	return elems;
}

