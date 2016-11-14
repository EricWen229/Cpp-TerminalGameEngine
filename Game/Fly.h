#ifndef Fly_H
#define Fly_H

#include "Able.h"
#include "GlobalVar.h"
#include "GTexture.h"
#include <SFML/Graphics.hpp>

class FlyThing: public Lifeable, public DRawable, public Attackable
{
    protected:
        FlyThing(
            int x, int y,
            int r,
            int dx, int dy,
            int blood,
            int power,
            sf::Texture &texture
        );
        ~FlyThing();
        
    public:
        virtual void outBound();
        void move();
};

class Airplane: public FlyThing, public Shootable
{
    public:
        Airplane(
            int x, int y,
            int r,
            int dx, int dy,
            int blood,
            int power,
            sf::Texture &texture
        );
        ~Airplane();
        
    public:
        void outBound(int width, int height);
        void changeSpeed(char key);
        Bullet shoot();
};

class Bullet: public FlyThing
{
    public:
        Bullet(
            int x, int y,
            int r,
            int dx, int dy,
            int power,
            sf::Texture &texture
        );
        ~Bullet();
        
    public:
        void outBound(int width, int height);
};

class Enemy: public FlyThing, public Shootable
{
    public:
        Enemy(
            int x, int y,
            int r,
            int dx, int dy,
            int power,
            sf::Texture &texture
        );
        ~Enemy();
        
    public:
        void outBound(int width, int height);
        Bullet shoot();
};

#endif
