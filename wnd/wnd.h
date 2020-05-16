#pragma once
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

typedef struct _MSGBOXINFO
{
    LPCWSTR title;
    LPCWSTR desc;
    UINT msgType;
}mbinfo;

