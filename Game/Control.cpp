#include "Control.h"

Control::Control(int w, int h, Airplane &a, Screen &s):
    width(w), height(w), screen(s), airplane(a), enemyCreateRate(20), shootRate(5) {}
Control::~Control() {}

void Control::autoMove()
{
    for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
    {
        it -> move();
        it -> outBound(width, height);
    }
    for (std::list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++)
    {
        it -> move();
        it -> outBound(width, height);
    }
    airplane.move();
    airplane.outBound(width, height);
}

void Control::autoShoot()
{
    static int count = 0;
    
    if (count > shootRate)
    {
        count -= shootRate;
        addBullet();
    }
    else
    {
        count++;
    }
}

void Control::addBullet()
{
    bullets.push_back(airplane.shoot());
}

void Control::addEnemy()
{
    static int count = 0;
    
    if (count > enemyCreateRate)
    {
        count -= enemyCreateRate;
        std::srand(std::time(0));
        int x = std::rand();
        x = x % width;
        enemys.push_back(Enemy(x, 0, EnemyR, 3, 5, EnemyPower, GTexture::enemyTexture));
    }
    else
    {
        count++;
    }
}

bool isDead(Lifeable &l)
{
    return !l.isAilve();
}

void Control::clean()
{
    for (std::list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++)
    {
        for (std::list<Bullet>::iterator iter = bullets.begin(); iter != bullets.end(); iter++)
        {
            int distance =
                (it -> getX() - iter -> getX()) ^ 2 +
                (it -> getY() - iter -> getY()) ^ 2;
            int r =
                (it -> getR() + iter -> getR()) ^ 2;
            if (distance < r)
            {
                it -> attacked(20);
                iter -> attacked(20);
            }
        }
    }
    enemys.remove_if(isDead);
    bullets.remove_if(isDead);
}

void Control::playerHandle()
{
    char key;
    while ((key = screen.message()) != ' ')
    {
        airplane.changeSpeed(key);
    }
}

void Control::driver()
{
    while (1)
    {
        std::vector<DRawable *> v;
        v.push_back(&airplane);
        for (std::list<Enemy>::iterator it = enemys.begin(); it != enemys.end(); it++)
        {
            v.push_back(&(*it));
        }
        for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
        {
            v.push_back(&(*it));
        }
        screen.refresh(v);
        addEnemy();
        autoMove();
        autoShoot();
        playerHandle();
        clean();
    }
}
