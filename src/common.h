#pragma once

#include <string>
#include <cstring>
#include <memory>
#include <cassert>
#include <exception>
#include <vector>
#include <iostream>

typedef unsigned char   ubyte;
typedef unsigned short  ushort;
typedef unsigned int    uint;

using namespace std;

std::vector<std::string> split(const std::string& str, char delim);
