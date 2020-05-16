#define _CRT_SECURE_NO_WARNINGS

#include "wnd/wnd.h"

#define SHUTDOWNHOUR 21
#define SHUTDOWMINUTE 35
#define MINUTEINMSEC 60000





DWORD WINAPI AttantionMsgBox(LPVOID param)
{
    mbinfo* mbParam = (mbinfo*)param;

    MessageBox(NULL, mbParam->title, mbParam->desc, mbParam->msgType);
}




int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{

    struct tm* info;
    time_t currSecs;
    HANDLE alertThread;
    mbinfo mbinfoArr[3];

    mbinfoArr[0].title = L"Утилита \"AutoShutdown\" включена."; mbinfoArr[0].desc = L"Предупреждение о включении"; mbinfoArr[0].msgType = MB_ICONASTERISK | MB_ICONINFORMATION;
    mbinfoArr[1].title = L"Через 5 минут компьютер выключется"; mbinfoArr[1].desc = L"Предупреждение о выключении"; mbinfoArr[1].msgType = MB_ICONASTERISK | MB_ICONINFORMATION;
    mbinfoArr[2].title = L"Компьютер выключется через 10 секунд"; mbinfoArr[2].desc = L"Выключение"; mbinfoArr[2].msgType = MB_ICONASTERISK | MB_ICONINFORMATION;
    
    
    alertThread = CreateThread(NULL, 0, AttantionMsgBox, &mbinfoArr[0], 0, 0);

    while (true)
    {
        time(&currSecs);
        info = localtime(&currSecs);

        if (info->tm_hour >= SHUTDOWNHOUR && info->tm_min >= SHUTDOWMINUTE)
        {

            alertThread = CreateThread(NULL, 0, AttantionMsgBox, &mbinfoArr[1], 0, 0);
            break;
        }
        Sleep((DWORD)MINUTEINMSEC);
    }

    Sleep((DWORD)MINUTEINMSEC * 5);


    alertThread = CreateThread(NULL, 0, AttantionMsgBox, &mbinfoArr[2], 0, 0);

    Sleep((DWORD)MINUTEINMSEC / 6);
    system("shutdown -s -f -t 0");
    return 0;
}
