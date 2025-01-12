#ifndef __NUMBERWANG__
#define __NUMBERWANG__

#include <Arduino.h>
#include <math.h>

class numberWang
{
private:
    uint8_t switcheroo[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

public:
    numberWang(){};

    void Wanger(int x, uint8_t *wang)
    {
        wang[0] = switcheroo[(int)floor(x / 1000)];
        wang[1] = switcheroo[(int)floor((x / 100) % 10)];
        wang[2] = switcheroo[(int)floor((x / 10) % 10)];
        wang[3] = switcheroo[(int)floor(x % 10)];
    }
};

#endif