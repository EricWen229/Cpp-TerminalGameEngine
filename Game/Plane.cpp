#include "Plane.h"

Player::Player(): UserControlThing(User), life(10)
{
    look = createArray<char>(3, 3);
    look[0][0] = 'A';
    look[0][1] = 'B';
    look[0][2] = 'C';
    look[1][0] = 'D';
    look[1][1] = 'E';
    look[1][2] = 'F';
    look[2][0] = 'G';
    look[2][1] = 'H';
    look[2][2] = 'I';
    height = width = 3;
}

void Player::ifBang(Thing *thing)
{
    /* table-driven */
    if (thing -> objectType == Enemy)
    {
        life -= 2;
    }
    if (thing -> objectType == Bullet)
    {
        life -= 1;
    }
}

void Player::ifBound(bool top, bool bottom, bool left, bool right)
{
}

bool Player::live()
{
    return life > 0;
}

AutoControlThing *Player::shoot()
{
    return nullptr;
}
