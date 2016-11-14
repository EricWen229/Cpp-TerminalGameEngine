#include "Thing.h"

std::vector<Thing *> Controller::things;
std::vector<Controller::Producer> Controller::producers;
int Controller::height, Controller::width;
bool Controller::exit;

void Controller::bang()
{
    int size = things.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            things[i] -> ifBang(*things[j]);
            things[j] -> ifBang(*things[i]);
        }
    }
}

void Controller::bound()
{
    int size = things.size();
    for (int i = 0; i < size; i++)
    {
        things[i] -> ifBound(height, width);
    }
}

void Controller::clean()
{
    int size = things.size();
    for (int i = 0; i < size; i++)
    {
        if (!things[i] -> live())
        {
            delete things[i];
            things.erase(things.begin() + i);
        }
    }
}

void Controller::produce()
{
    int size = producers.size();
    for (int i = 0; i < size; i++)
    {
        things.push_back(producers[i]());
    }
}

void Controller::handle()
{
    int size = things.size();
    /* 默认第一个元素是用户控制的 */
    for (int i = 1; i < size; i++)
    {
        ((AutoControlThing *)(things[i])) -> handle();
    }
}

void Controller::draw()
{
    int size = things.size();
    for (int i = 0; i < size; i++)
    {
        int height = things[i] -> height, width = things[i] -> width;
        int x = things[i] -> x, y = things[i] -> y;
        for (int a = 0; a < height; a++)
        {
            for (int b = 0; b < width; b++)
            {
                buffer[y + a][x + b] = things[i] -> look[a][b];
            }
        }
    }
}

void Controller::init(int h, int w, Producer ps[], int nProducer)
{
    height = h;
    width = w;
    for (int i = 0; i < nProducer; i++)
    {
        producers.push_back(ps[i]);
    }
    buffer = createArray<char>(height, width);
}

void Controller::loop()
{
    while (!exit)
    {
        bang();
        bound();
        clean();
        produce();
        handle();
        draw();
    }
}
