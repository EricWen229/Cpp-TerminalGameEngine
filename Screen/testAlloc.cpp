#define LogMode
#define AssertMode
#define ExtraRunMode
#include "../DiagHelper.h"

#include "Screen.h"
#include "../Array/Array.h"

int main()
{
    int id[6];
    SmartArray<char> s[6];
    
    Screen testA;
    testA.init(2, 2, 0);
    
    id[0] = testA.alloc(0, 0, 1, 1);
    id[1] = testA.alloc(0, 1, 1, 1);
    id[2] = testA.alloc(1, 0, 1, 1);
    id[3] = testA.alloc(1, 1, 1, 1);
    
    ExtraRun
    (for (int i = 0; i < 4; i++)
     Log(id[i] << "\t" << "../Screen/testAlloc.cpp/18"););
    Log("");
    
    for (int i = 0; i < 4; i++)
    {
        s[i] = testA.get(id[i]);
    }
    ExtraRun
    (for (int i = 0; i < 4; i++)
     Log(s[i][0] << "\t" << "../Screen/testAlloc.cpp/33"););
    Log("");
    
    for (int i = 0; i < 4; i++)
    {
        s[i][0][0] = (i + '0');
        Log(s[i][0][0] << "\t" << "../Screen/testAlloc.cpp/39");
    }
    Log("");
    
    ExtraRun
    (for (int i = 0; i < 4; i++)
     Log(s[i][0][0] << "\t" << "../Screen/testAlloc.cpp/45"););
    Log("");
    
    Log(testA.buffer[0][0] << testA.buffer[0][1] << "\t../Screen/testAlloc.cpp/47");
    Log(testA.buffer[1][0] << testA.buffer[1][1] << "\t../Screen/testAlloc.cpp/48");
    Log("");
    
    Log(testA.buffer[0] << "\t../Screen/testAlloc.cpp/52");
    Log(testA.buffer[1] << "\t../Screen/testAlloc.cpp/53");
}
