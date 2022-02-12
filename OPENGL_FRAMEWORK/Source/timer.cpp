#include "timer.h"

StopWatch::StopWatch() :
    prevTime(LARGE_INTEGER{0}),
    currTime(LARGE_INTEGER{ 0 })
{    

    QueryPerformanceFrequency( &frequency ) ;

    #define TARGET_RESOLUTION 1         // 1-millisecond target resolution
    TIMECAPS tc;
    

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
    {
        // Error; application can't continue.
        auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(Handle, 12);
        std::cout << " Error: "; 
        SetConsoleTextAttribute(Handle, 7);
        std::cout << "application can't continue " << std::endl;
    }

    wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
    timeBeginPeriod(wTimerRes); 

    //print out in the console
    auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Handle, 11);
    std::cout << " Timer ";
    SetConsoleTextAttribute(Handle, 10);
    std::cout << "Created" << std::endl;
    SetConsoleTextAttribute(Handle, 7);
}

StopWatch::~StopWatch()
{
    timeEndPeriod(wTimerRes);
    //print out in the console
    auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Handle, 11);
    std::cout << " Timer ";
    SetConsoleTextAttribute(Handle, 12);
    std::cout << "Deleted!" << std::endl;
    SetConsoleTextAttribute(Handle, 7);
}

double StopWatch::LIToSecs( LARGE_INTEGER & L) {
     return ((double)L.QuadPart /(double)frequency.QuadPart) ;
 }
 
void StopWatch::startTimer( )
{
    //print out in the console
    auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Handle, 11);
    std::cout << " Timer ";
    SetConsoleTextAttribute(Handle, 14);
    std::cout << "Started!" << std::endl;
    SetConsoleTextAttribute(Handle, 7);

    QueryPerformanceCounter(&prevTime) ;
}
 
double StopWatch::getElapsedTime() 
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&currTime) ;
    time.QuadPart = currTime.QuadPart - prevTime.QuadPart;
    prevTime = currTime;
    return LIToSecs( time) ;
}

void StopWatch::waitUntil(long long time)
{
    LARGE_INTEGER nowTime;
    LONGLONG timeElapsed;
    while (true)
    {
        QueryPerformanceCounter(&nowTime);
        timeElapsed = ((nowTime.QuadPart - prevTime.QuadPart) * 1000 / frequency.QuadPart);
        if (timeElapsed > time)
            return;
        else if (time - timeElapsed > 1)
            Sleep(1);
    }
}