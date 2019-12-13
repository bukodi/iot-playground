#ifndef _SCREENS_H /* include guards */
#define _SCREENS_H

#include <Arduino.h>

class Screen
{
public:
    int id;
    char *name;
    void (*screenProc)(Screen *pScreen);
    unsigned long refreshPeriod;
    unsigned long lastPrinted;

    Screen(int pid, char *pname, unsigned long prefreshPeriod, void (*pscreenProc)(Screen *pScreen))
    {
        id = pid;
        name = pname;
        screenProc = pscreenProc;
        refreshPeriod = prefreshPeriod;
    }
};

class ScreenMgr
{
public:
    static void init()
    {
        screenArray = nullptr;
        screenArraySize = 0;
        currentScreenIdx = 0;
        longpressDuration = 1000;
        longpressStartred = false;
        longpressShouldClear = false;
    }

    static void add(Screen *screen);
    static void processUIActions();
    static Screen *currentScreen();

    static Screen **screenArray;
    static int screenArraySize;
    static int currentScreenIdx;
    static unsigned long longpressStartred;
    static unsigned long longpressDuration;
    static bool longpressShouldClear;

private:
    ScreenMgr()
    {
        // Disable instances
    }
};

#endif /* _SCREENS_H */