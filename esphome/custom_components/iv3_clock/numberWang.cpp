#include "numberWang.h"

void numberWang::Wanger(int x, uint8_t *wang)
{
    wang[0] = switcheroo[(int)floor(x / 1000)];
    wang[1] = switcheroo[(int)floor((x / 100) % 10)];
    wang[2] = switcheroo[(int)floor((x / 10) % 10)];
    wang[3] = switcheroo[(int)floor(x % 10)];
}