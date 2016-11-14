#include "Able.h"

Moveable::Moveable(int oex, int oey, int oer, int oedx, int oedy):
    x(oex), y(oey), r(oer), dx(oedx), dy(oedy) {}
Moveable::~Moveable() {}

int Moveable::getX()
{
    return x;
}

int Moveable::getY()
{
    return y;
}

int Moveable::getR()
{
    return r;
}

void Moveable::move()
{
    x += dx;
    y += dy;
}

Lifeable::Lifeable(int b): blood(b) {}
Lifeable::~Lifeable() {}

void Lifeable::attacked(int attack)
{
    blood -= attack;
}

bool Lifeable::isAilve()
{
    return blood > 0;
}

DRawable::DRawable(sf::Texture &texture)
{
    sprite.setTexture(texture);
}
DRawable::~DRawable() {}

void DRawable::setPosition(int x, int y)
{
    sprite.setPosition(x, y);
}

sf::Sprite &DRawable::draw()
{
    return sprite;
}

Shootable::Shootable() {}
Shootable::~Shootable() {}

Attackable::Attackable(int p): power(p) {}
Attackable::~Attackable() {}

int Attackable::attack()
{
    return power;
}
