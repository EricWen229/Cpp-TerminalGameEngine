#include "Controller.h"

UserControlSprite *Controller::users;
int Controller::height, Controller::width;
Screen Controller::screen;
std::vector<int> Controller::ids;
SmartArray<char> Controller::gameBuffer;

UserControlSprite::~UserControlSprite() {}

AutoControlSprite::~AutoControlSprite() {}

Sprite::Sprite() {}
Sprite::~Sprite() {}

void Sprite::moveTo(int newI, int newJ)
{
    if (i != newI || j != newJ)
    {
        for (int a = 0; a < height; a++)
        {
            for (int b = 0; b < width; b++)
            {
                Controller::gameBuffer[i + a][j + b] = ' ';
            }
        }
    }
    
    i = newI;
    j = newJ;
    Controller().bound(this);
    
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            Controller::gameBuffer[i + a][j + b] = look[a][b];
        }
    }
}

void Sprite::moveAdd(int deltaI, int deltaJ)
{
    moveTo(i + deltaI, j + deltaJ);
}


void Controller::bound(Sprite *thing)
{
    int height = screen.get(ids[0]) -> height,
        width = screen.get(ids[0]) -> width;
        
    if (thing -> i < 0)
    {
        thing -> i = 0;
        thing -> ifBound(OutBoundTop);
    }
    else if (thing -> i + thing -> height > height)
    {
        thing -> i = height - thing -> height;
        thing -> ifBound(OutBoundBottom);
    }
    
    if (thing -> j < 0)
    {
        thing -> j = 0;
        thing -> ifBound(OutBoundLeft);
    }
    else if (thing -> j + thing -> width > width)
    {
        thing -> j = width - thing -> width;
        thing -> ifBound(OutBoundRight);
    }
}

bool Controller::bangHelper(Sprite *a, Sprite *b)
{
    if (a -> i >= b -> i && a -> i >= b -> i + b -> height)
    {
        return false;
    }
    else if (a -> i <= b -> i && a -> i + a -> height <= b -> i)
    {
        return false;
    }
    else if (a -> j >= b -> j && a -> j >= b -> j + b -> width)
    {
        return false;
    }
    else if (a -> j <= b -> j && a -> j + a -> width <= b -> j)
    {
        return false;
    }
    return false;
}

void Controller::bang()
{
}

void Controller::clean()
{
}

void Controller::init(int h, int w)
{
    height = h;
    width = w;
    screen.init(h, w, user -> objectId);
    
    int id1 = screen.alloc(0, 0, 1, width);
    int id2 = screen.alloc(height - 1, 0, 1, width);
    int id3 = screen.alloc(1, 0, height - 2, 1);
    int id4 = screen.alloc(1, width - 6, height - 2, 1);
    int id5 = screen.alloc(1, width - 1, height - 2, 1);
    int id6 = screen.alloc(1, 1, height - 2, width - 7);
    int id7 = screen.alloc(1, width - 5, height - 2, 5);
    ids.push_back(id6);
    gameBuffer = screen.get(id6);
    ids.push_back(id7);
    
    SmartArray<char> sa = screen.get(id1);
    for (int i = 1; i < width - 1; i++)
    {
        sa[0][i] = '-';
    }
    sa[0][0] = sa[0][width - 6] = sa[0][width - 1] = '+';
    SmartArray<char> sb = screen.get(id2);
    for (int i = 1; i < width - 1; i++)
    {
        sb[0][i] = '-';
    }
    sb[0][0] = sb[0][width - 6] = sb[0][width - 1] = '+';
    SmartArray<char> sc = screen.get(id3);
    for (int i = 0; i < height - 2; i++)
    {
        sc[i][0] = '|';
    }
    SmartArray<char> sd = screen.get(id4);
    for (int i = 0; i < height - 2; i++)
    {
        sd[i][0] = '|';
    }
    SmartArray<char> se = screen.get(id5);
    for (int i = 0; i < height - 2; i++)
    {
        se[i][0] = '|';
    }
    
    user -> moveTo(0, 0);
}

void Controller::loop()
{
    Mailbox().begin();
    screen.begin();
    while (!screen.isExit())
    {
        bang();
        clean();
    }
    screen.end();
}
