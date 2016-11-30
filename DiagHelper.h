#ifndef DiagHelper_H
#define DiagHelper_H

#ifdef LogMode
#include <iostream>
#include <fstream>
#include <mutex>
std::mutex logFileMutex;
#define Log(info) \
    { \
    logFileMutex.lock(); \
    std::ofstream logFile("./logFile", std::ios::app); \
    logFile << info << std::endl; \
    logFile.close(); \
    logFileMutex.unlock(); \
    }
#else
#define Log(info) \
    ;
#endif

#ifdef AssertMode
#include <assert.h>
#define Assert(a) \
    assert(a);
#else
#define Assert(a) \
    ;
#endif

#ifdef DebugMode
#define Run(r) \
    r;
#else
#define Run(r) \
    ;
#endif

#endif
