#ifndef Control_H
#define Control_H

#include "Able.h"
#include "Fly.h"
#include "Screen.h"
#include "GTexture.h"
#include <list>

class Control
{
    private:
        Airplane &airplane;
        std::list<Bullet> bullets;
        std::list<Enemy> enemys;
        int width, height;
        Screen &screen;
        int enemyCreateRate;
        int shootRate;
        
    public:
        Control(int w, int h, Airplane &a, Screen &s);
        ~Control();
        
    private:
        void autoMove();
        void autoShoot();
        void addBullet();
        void addEnemy();
        void clean();
        
    public:
        void playerHandle();
        void driver();
};

#endif
