#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define SHUTDOWNHOUR 21
#define SHUTDOWMINUTE 40
#define MINUTEINMSEC 60000


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    struct tm* info;
    time_t currSecs;

    MessageBox(NULL, (LPCWSTR)L"Утилита \"AutoShutdown\" включена.", L"Предупреждение о включении", MB_ICONASTERISK | MB_ICONINFORMATION);

    while (true)
    {
        time(&currSecs);
        info = localtime(&currSecs);

        if (info->tm_hour >= SHUTDOWNHOUR && info->tm_min >= SHUTDOWMINUTE)
        {
            int msBoxId = MessageBox(NULL, (LPCWSTR)L"Через 5 минут компьютер выключется", L"Предупреждение о выключении", MB_ICONASTERISK | MB_ICONINFORMATION);
            break;

        }
        Sleep((DWORD)MINUTEINMSEC / 2);
    }
    Sleep((DWORD)MINUTEINMSEC * 5);

    MessageBox(NULL, (LPCWSTR)L"Компьютер выключется через 10 секунд", L"Выключение", MB_ICONASTERISK | MB_ICONINFORMATION);
    Sleep((DWORD)MINUTEINMSEC / 6);
    ExitWindowsEx(EWX_LOGOFF, SHTDN_REASON_MAJOR_APPLICATION);
    return 0;
}
