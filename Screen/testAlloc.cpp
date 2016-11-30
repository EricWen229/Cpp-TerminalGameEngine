#define LogMode
#define AssertMode
#define ExtraRunMode
#include "../DiagHelper.h"

#include <vector>
#include "../Array/Array.h"

typedef int Id;

struct ManBook
{
    int left;
    int top;
    int width;
    int height;
};

class Screen
{
    public:
        static int height, width;
        static SmartArray<char> buffer;
        static std::vector<ManBook> books;
        
    public:
        void init(int h, int w);
        
        Id alloc(int top, int left, int height, int width);
        SmartArray<char> get(Id id);
        void free(Id id);
};

SmartArray<char> Screen::buffer;
int Screen::width, Screen::height;
std::vector<ManBook> Screen::books;

void Screen::init(int h, int w)
{
    height = h;
    width = w;
    buffer = createArray<char>(height, width + 1);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = ' ';
        }
        buffer[i][width] = '\0';
    }
}

Id Screen::alloc(int top, int left, int height, int width)
{
    int size = books.size();
    
    ManBook book;
    book.left = left;
    book.top = top;
    book.height = height;
    book.width = width;
    
    books.push_back(book);
    return size;
}

SmartArray<char> Screen::get(Id id)
{
    if (id == -1)
    {
        return SmartArray<char>();
    }
    else
    {
        ManBook book = books[id];
        Log("id " << id);
        Log("top: " << books[id].top);
        Log("left: " << books[id].left);
        return createArray(book.top, book.left, book.height, book.width, buffer);
    }
}

void Screen::free(Id id)
{
    if (id == -1)
    {
        return;
    }
    else
    {
        books.erase(books.begin() + id);
    }
}

int main()
{
    int id[6];
    SmartArray<char> s[6];
    
    /* Screen testA; */
    /* testA.init(2, 2, 0); */
    
    /* id[0] = testA.alloc(0, 0, 1, 1); */
    /* id[1] = testA.alloc(0, 1, 1, 1); */
    /* id[2] = testA.alloc(1, 0, 1, 1); */
    /* id[3] = testA.alloc(1, 1, 1, 1); */
    
    /* ExtraRun */
    /* (for (int i = 0; i < 4; i++) */
    /*  Log(id[i] << "\t" << "../Screen/testAlloc.cpp/18");); */
    /* Log(""); */
    
    /* for (int i = 0; i < 4; i++) */
    /* { */
    /*     s[i] = testA.get(id[i]); */
    /* } */
    /* ExtraRun */
    /* (for (int i = 0; i < 4; i++) */
    /*  Log(s[i][0] << "\t" << "../Screen/testAlloc.cpp/33");); */
    /* Log(""); */
    
    /* for (int i = 0; i < 4; i++) */
    /* { */
    /*     s[i][0][0] = (i + '0'); */
    /*     Log(s[i][0][0] << "\t" << "../Screen/testAlloc.cpp/39"); */
    /* } */
    /* Log(""); */
    
    /* ExtraRun */
    /* (for (int i = 0; i < 4; i++) */
    /*  Log(s[i][0][0] << "\t" << "../Screen/testAlloc.cpp/45");); */
    /* Log(""); */
    
    /* Log(testA.buffer[0][0] << testA.buffer[0][1] << "\t../Screen/testAlloc.cpp/47"); */
    /* Log(testA.buffer[1][0] << testA.buffer[1][1] << "\t../Screen/testAlloc.cpp/48"); */
    /* Log(""); */
    
    /* Log(testA.buffer[0] << "\t../Screen/testAlloc.cpp/52"); */
    /* Log(testA.buffer[1] << "\t../Screen/testAlloc.cpp/53"); */
    
    Screen testB;
    testB.init(12, 20);
    
    ExtraRun
    (
        for (int i = 0; i < 12; i++)
        Log(testB.buffer[i] << "\t../Screen/testAlloc.cpp/62");
    );
    
    id[0] = testB.alloc(0, 0, 1, 20);
    id[1] = testB.alloc(11, 0, 1, 20);
    id[2] = testB.alloc(1, 0, 10, 1);
    id[3] = testB.alloc(1, 12, 10, 1);
    id[4] = testB.alloc(1, 19, 10, 1);
    id[5] = testB.alloc(1, 1, 10, 11);
    
    ExtraRun
    (for (int i = 0; i < 6; i++)
     Log(id[i] << "\t" << "../Screen/testAlloc.cpp/67"););
    Log("");
    
    for (int i = 0; i < 6; i++)
    {
        s[i] = testB.get(id[i]);
    }
    ExtraRun
    (for (int i = 0; i < 6; i++)
     Log(s[i][0] << "\t" << "../Screen/testAlloc.cpp/76"););
    Log("");
    
    for (int i = 1; i < 19; i++)
    {
        s[0][0][i] = '-';
    }
    s[0][0][0] = s[0][0][12] = s[0][0][19] = '+';
    ExtraRun
    (
        for (int i = 0; i < 12; i++)
        Log(testB.buffer[i]);
    );
    Log("");
    
    for (int i = 1; i < 19; i++)
    {
        s[1][0][i] = '-';
    }
    s[1][0][0] = s[1][0][12] = s[1][0][19] = '+';
    ExtraRun
    (
        for (int i = 0; i < 12; i++)
        Log(testB.buffer[i]);
    );
    Log("");
    
    for (int i = 0; i < 10; i++)
    {
        s[2][i][0] = '|';
    }
    ExtraRun
    (
        for (int i = 0; i < 12; i++)
        Log(testB.buffer[i]);
    );
    Log("");
    
    for (int i = 0; i < 10; i++)
    {
        s[3][i][0] = '|';
    }
    ExtraRun
    (
        for (int i = 0; i < 12; i++)
        Log(testB.buffer[i]);
    );
    Log("");
    
    for (int i = 0; i < 10; i++)
    {
        s[4][i][0] = '|';
    }
    ExtraRun
    (
        for (int i = 0; i < 12; i++)
        Log(testB.buffer[i]);
    );
    Log("");
}
