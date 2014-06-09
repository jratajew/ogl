#pragma once

#include <string>
#include <cstring>
#include <memory>
#include <cassert>
#include <exception>
#include <vector>
#include <list>
#include <iostream>
#include <cassert>

typedef unsigned char   ubyte;
typedef unsigned short  ushort;
typedef unsigned int    uint;

const size_t cMaxUByte = ubyte(-1);

using namespace std;

std::vector<std::string> split(const std::string& str, char delim);

class KeyboardListener
{
public:
    virtual void KeyDown(unsigned char key, int x, int y) = 0;
    virtual void SpecialKeyDown(int key, int x, int y) = 0;
    virtual void KeyUp(unsigned char key, int x, int y) = 0;
    virtual void SpecialKeyUp(int key, int x, int y) = 0;
};