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
#include <map>

typedef unsigned char   ubyte;
typedef unsigned short  ushort;
typedef unsigned int    uint;

const size_t cMaxUByte = ubyte(-1);

using namespace std;

std::vector<std::string> split(const std::string& str, char delim);

class InputListener
{
public:
    InputListener() 
        : m_MousePosX(0), m_MousePosY(0), m_MousePosX_Prev(0), m_MousePosY_Prev(0)
    {
        memset(m_KeyState, 0, sizeof(m_KeyState));
        memset(m_MouseState, 0, sizeof(m_MouseState));
    }

    enum MouseButton
    {
        MOUSE_BUTTON_LEFT = 0,
        MOUSE_BUTTON_MIDDLE,
        MOUSE_BUTTON_RIGHT,

        MOUSE_BUTTON_COUNT
    };

    inline void KeyDown(unsigned char key, int x, int y)
    {
        if(!m_KeyState[key])
            KeyDownImpl(key);
        m_KeyState[key] = true;
        ResetMousePos(x, y);
    }

    inline void SpecialKeyDown(int key, int x, int y)
    {
        ResetMousePos(x, y);
        SpecialKeyDownImpl(key);
        // TODO
    }

    inline void KeyUp(unsigned char key, int x, int y)
    {
        if(m_KeyState[key])
            KeyUpImpl(key);
        ResetMousePos(x, y);
        m_KeyState[key] = false;
    }

    inline void SpecialKeyUp(int key, int x, int y)
    {
        ResetMousePos(x, y);
        SpecialKeyUpImpl(key);
        // TODO
    }

    inline void MouseButtonDown(MouseButton b, int x, int y)
    {
        ResetMousePos(x, y);
        m_MouseState[b] = true;
        MouseButtonDownImpl(b);
    }

    inline void MouseButtonUp(MouseButton b, int x, int y)
    {
        ResetMousePos(x, y);
        m_MouseState[b] = false;
        MouseButtonUpImpl(b);
    }

    inline void MouseMotionActive(int x, int y)
    {
        NewMousePos(x, y);
        MouseMoved();
    }

    inline void MouseMotionPassive(int x, int y)
    {
        NewMousePos(x, y);
        MouseMoved();
    }

    inline bool KeyState(unsigned char key) const { return m_KeyState[key]; }
    inline bool MouseButtonState(MouseButton button) const { return m_MouseState[button]; }
    inline int  MouseX() const { return m_MousePosX; }
    inline int  MouseY() const { return m_MousePosY; }
    inline int  MouseX_delta() const { return m_MousePosX - m_MousePosX_Prev; }
    inline int  MouseY_delta() const { return m_MousePosY - m_MousePosY_Prev; }


protected:
    virtual void KeyDownImpl(unsigned char key) = 0;
    virtual void KeyUpImpl(unsigned char key) = 0;

    virtual void SpecialKeyDownImpl(int key) = 0;
    virtual void SpecialKeyUpImpl(int key) = 0;

    virtual void MouseButtonDownImpl(MouseButton b) = 0;
    virtual void MouseButtonUpImpl(MouseButton b) = 0;

    virtual void MouseMoved() = 0;

private:
    inline void ResetMousePos(int x, int y)
    {
        m_MousePosX_Prev = m_MousePosX = x;
        m_MousePosY_Prev = m_MousePosY = y;
    }

    inline void NewMousePos(int x, int y)
    {
        m_MousePosX_Prev = m_MousePosX;
        m_MousePosY_Prev = m_MousePosY;
        m_MousePosX = x;
        m_MousePosY = y;    
    }
    
    bool m_KeyState[cMaxUByte];
    bool m_MouseState[MOUSE_BUTTON_COUNT];

    int m_MousePosX;
    int m_MousePosY;

    int m_MousePosX_Prev;
    int m_MousePosY_Prev;
};