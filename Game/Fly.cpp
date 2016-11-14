#include "Fly.h"

FlyThing::FlyThing(
    int x, int y,
    int r,
    int dx, int dy,
    int blood,
    int power,
    sf::Texture &texture
): Moveable(x, y, r, dx, dy), Lifeable(blood), DRawable(texture), Attackable(power)
{
    double scaleX = 1.0 * r / texture.getSize().x;
    double scaleY = 1.0 * r / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);
    sprite.setOrigin(r / 2.0, r / 2.0);
    setPosition(x, y);
}
FlyThing::~FlyThing() {};

void FlyThing::outBound()
{
    setPosition(x, y);
}

void FlyThing::move()
{
    Moveable::move();
}

Airplane::Airplane(
    int x, int y,
    int r,
    int dx, int dy,
    int blood,
    int power,
    sf::Texture &texture
): FlyThing(x, y, r, dx, dy, blood, power, texture) {}
Airplane::~Airplane() {}

void Airplane::outBound(int width, int height)
{
    if (x < 0)
    {
        x  = 0;
    }
    else if (x > width)
    {
        x = width;
    }
    
    if (y < 0)
    {
        y = 0;
    }
    else if (y > height)
    {
        y = height;
    }
    
    FlyThing::outBound();
}

void Airplane::changeSpeed(char key)
{
    switch (key)
    {
        case 'w':
            dy -= 1;
            dx = 0;
            break;
        case 's':
            dy += 1;
            dx = 0;
            break;
        case 'a':
            dy = 0;
            dx -= 1;
            break;
        case 'd':
            dy = 0;
            dx += 1;
            break;
        default:
            break;
    }
    
    if (dx < -1 * AirplaneMaxDx)
    {
        dx = -1 * AirplaneMaxDx;
    }
    else if (dx > AirplaneMaxDx)
    {
        dx = AirplaneMaxDx;
    }
    
    if (dy < -1 * AirplaneMaxDy)
    {
        dy = -1 * AirplaneMaxDy;
    }
    else if (dy > AirplaneMaxDy)
    {
        dy = AirplaneMaxDy;
    }
}

Bullet Airplane::shoot()
{
    return Bullet(x, y, BulletR, 0, -1 * BulletSpeed, BulletPower, GTexture::bulletTexture);
}

Bullet::Bullet(
    int x, int y,
    int r,
    int dx, int dy,
    int power,
    sf::Texture &texture
): FlyThing(x, y, r, dx, dy, 1, power, texture) {}
Bullet::~Bullet() {}

void Bullet::outBound(int width, int height)
{
    if (x < 0 || x > width || y < 0 || y > height)
    {
        attacked(1);
    }
}

Enemy::Enemy(
    int x, int y,
    int r,
    int dx, int dy,
    int power,
    sf::Texture &texture
): FlyThing(x, y, r, dx, dy, 100, power, texture) {}
Enemy::~Enemy() {}

void Enemy::outBound(int width, int height)
{
    if (x < 0)
    {
        x = 0;
        dx *= -1;
    }
    else if (x > width)
    {
        x = width;
        dx *= -1;
    }
    
    if (y < 0)
    {
        y = 0;
        dy *= -1;
    }
    else if (y > height)
    {
        y = height;
        dy *= -1;
    }
    
    FlyThing::outBound();
}

Bullet Enemy::shoot()
{
    return Bullet(x, y, 0, -1 * BulletSpeed, BulletR, BulletPower, GTexture::bulletTexture);
}
