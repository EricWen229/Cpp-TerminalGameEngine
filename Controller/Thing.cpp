#include "Thing.h"

std::vector<UserControlThing *> Controller::users;
std::vector<AutoControlThing *> Controller::autos;
std::vector<Controller::Producer> Controller::producers;
int Controller::height, Controller::width;
Screen Controller::screen;
std::vector<int> Controller::ids;

void Controller::bound()
{
    int size = users.size();
    for (int i = 0; i < size; i++)
    {
        if (users[i] -> i < 0)
        {
            users[i] -> ifBound(true, false, false, false);
        }
        else if (users[i] -> i > height)
        {
            users[i] -> ifBound(false, true, false, false);
        }
        else if (users[i] -> j < 0)
        {
            users[i] -> ifBound(false, false, true, true);
        }
        else if (users[i] -> j > width)
        {
            users[i] -> ifBound(false, false, false, true);
        }
    }
    size = autos.size();
    for (int i = 0; i < size; i++)
    {
        if (autos[i] -> i < 0)
        {
            autos[i] -> ifBound(true, false, false, false);
        }
        else if (autos[i] -> i > height)
        {
            autos[i] -> ifBound(false, true, false, false);
        }
        else if (autos[i] -> j < 0)
        {
            autos[i] -> ifBound(false, false, true, true);
        }
        else if (autos[i] -> j > width)
        {
            autos[i] -> ifBound(false, false, false, true);
        }
    }
}

void Controller::bang()
{
    int sizeU = users.size();
    int sizeA = autos.size();
    for (int i = 0; i < sizeU; i++)
    {
        for (int j = i + 1; j < sizeU; j++)
        {
            users[i] -> ifBang(users[j]);
            users[j] -> ifBang(users[i]);
        }
        for (int k = 0; k < sizeA; k++)
        {
            users[i] -> ifBang(autos[k]);
            autos[k] -> ifBang(users[i]);
        }
    }
    for (int i = 0; i < sizeA; i++)
    {
        for (int j = i + 1; j < sizeA; j++)
        {
            autos[i] -> ifBang(autos[j]);
            autos[j] -> ifBang(autos[i]);
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
        autos.push_back(producers[i]());
    }
}

void Controller::shoot()
{
    int size = users.size();
    for (int i = 0; i < size; i++)
    {
        autos.push_back(users[i] -> shoot());
    }
    
    size = autos.size();
    for (int i = 0; i < size; i++)
    {
        autos.push_back(autos[i] -> shoot());
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
        int height = users[i] -> height, width = users[i] -> width;
        int top = users[i] -> i, left = users[i] -> j;
        SmartArray<char> buffer = screen.get(ids[i]);
        for (int a = 0; a < height; a++)
        {
            for (int b = 0; b < width; b++)
            {
                screen.get(ids[0])[top + a][left + b] = users[i] -> look[a][b];
            }
        }
    }
    
    size = autos.size();
    for (int i = 0; i < size; i++)
    {
        int height = autos[i] -> height, width = autos[i] -> width;
        int top = autos[i] -> i, left = autos[i] -> j;
        SmartArray<char> buffer = screen.get(ids[i]);
        for (int a = 0; a < height; a++)
        {
            for (int b = 0; b < width; b++)
            {
                screen.get(ids[0])[top + a][left + b] = autos[i] -> look[a][b];
            }
        }
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
}

void Controller::loop()
{
    screen.begin();
    while (!screen.isExit())
    {
        bound();
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
