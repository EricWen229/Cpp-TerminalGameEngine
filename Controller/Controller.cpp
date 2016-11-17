#include "Controller.h"

std::vector<UserControlThing *> Controller::users;
std::vector<AutoControlThing *> Controller::autos;
std::vector<Controller::Producer> Controller::producers;
int Controller::height, Controller::width;
Screen Controller::screen;
std::vector<int> Controller::ids;
SmartArray<char> Controller::gameBuffer;

Thing::Thing(ObjectType o): objectType(o) {}
Thing::~Thing() {}

void Thing::moveTo(int newI, int newJ)
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
    Controller::boundHelper(this);
    
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            Controller::gameBuffer[i + a][j + b] = look[a][b];
        }
    }
}

void Thing::moveAdd(int deltaI, int deltaJ)
{
    moveTo(i + deltaI, j + deltaJ);
}

UserControlThing::UserControlThing(ObjectType o): Thing(o) {}

AutoControlThing::AutoControlThing(ObjectType o): Thing(o) {}

void Controller::boundHelper(Thing *thing)
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

bool Controller::bangHelper(Thing *a, Thing *b)
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
    int sizeU = users.size();
    int sizeA = autos.size();
    for (int i = 0; i < sizeU; i++)
    {
        for (int j = i + 1; j < sizeU; j++)
        {
            if (bangHelper(users[i], users[j]))
            {
                users[i] -> ifBang(users[j]);
                users[j] -> ifBang(users[i]);
            }
        }
        for (int k = 0; k < sizeA; k++)
        {
            if (bangHelper(users[i], autos[k]))
            {
                users[i] -> ifBang(autos[k]);
                autos[k] -> ifBang(users[i]);
            }
        }
    }
    for (int i = 0; i < sizeA; i++)
    {
        for (int j = i + 1; j < sizeA; j++)
        {
            if (bangHelper(autos[i], autos[j]))
            {
                autos[i] -> ifBang(autos[j]);
                autos[j] -> ifBang(autos[i]);
            }
        }
    }
}

void Controller::clean()
{
    int size = users.size();
    for (int i = 0; i < size; i++)
    {
        if (!users[i] -> live())
        {
            delete users[i];
            users.erase(users.begin() + i);
        }
    }
    
    size = autos.size();
    for (int i = 0; i < size; i++)
    {
        if (!autos[i] -> live())
        {
            delete autos[i];
            autos.erase(autos.begin() + i);
        }
    }
}

void Controller::produce()
{
    int size = producers.size();
    for (int i = 0; i < size; i++)
    {
        AutoControlThing *p = producers[i]();
        if (p != null)
        {
            autos.push_back(p);
        }
    }
}

void Controller::shoot()
{
    int size = users.size();
    for (int i = 0; i < size; i++)
    {
        AutoControlThing *bullet = users[i] -> shoot();
        if (bullet != null)
        {
            autos.push_back(bullet);
        }
    }
    
    size = autos.size();
    for (int i = 0; i < size; i++)
    {
        AutoControlThing *bullet = autos[i] -> shoot();
        if (bullet != null)
        {
            autos.push_back(bullet);
        }
    }
}

void Controller::handle()
{
    int size = autos.size();
    for (int i = 1; i < size; i++)
    {
        autos[i] -> handle();
    }
}

void Controller::draw()
{
    int size = users.size();
    for (int i = 0; i < size; i++)
    {
        users[i] -> moveAdd(0, 0);
    }
}

void Controller::init
(int h, int w, Interface *i,
 UserControlThing *u[], int nUser,
 Producer ps[], int nProducer)
{
    height = h;
    width = w;
    for (int i = 0; i < nProducer; i++)
    {
        producers.push_back(ps[i]);
    }
    screen.init(h, w, i, ::handle);
    
    for (int i = 0; i < nUser; i++)
    {
        users.push_back(u[i]);
    }
    
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
    
    users[0] -> moveTo(0, 0);
}

void Controller::loop()
{
    screen.begin();
    while (!screen.isExit())
    {
        bang();
        clean();
        produce();
        handle();
        shoot();
        handle();
        draw();
    }
    screen.end();
    
    int size = users.size();
    for (int i = 0; i < size; i++)
    {
        delete users[i];
    }
    size = autos.size();
    for (int i = 0; i < size; i++)
    {
        delete autos[i];
    }
}
