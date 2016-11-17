#include "Plane.h"

int AttackTable[3][3];

Player::Player(): UserControlThing(UserType), life(10)
{
    look = createArray<char>(1, 5);
    look[0][0] = '/';
    look[0][1] = '-';
    look[0][2] = '^';
    look[0][3] = '-';
    look[0][4] = '\\';
    height = 1;
    width = 5;
}

void Player::ifBang(Thing *thing)
{
    /* table-driven */
    life -= AttackTable[objectType][thing -> objectType];
}

void Player::ifBound(OutBoundType o)
{
}

bool Player::live()
{
    return life > 0;
}

AutoControlThing *Player::shoot()
{
    int bulletI;
    if (i == 0)
    {
        bulletI = i;
    }
    else
    {
        bulletI = i - 1;
    }
    return new Bullet(5, j + 2, -1, 0);
    /* return null; */
}

Enemy::Enemy(int locI, int locJ): AutoControlThing(EnemyType), life(2)
{
    i = locI;
    j = locJ;
    look = createArray<char>(1, 3);
    look[0][0] = '-';
    look[0][1] = 'o';
    look[0][2] = '-';
    height = 1;
    width = 3;
}

void Enemy::ifBang(Thing *thing)
{
    life -= AttackTable[objectType][thing -> objectType];
}

void Enemy::ifBound(OutBoundType o)
{
    life = 0;
}

bool Enemy::live()
{
    return life > 0;
}

void Enemy::handle()
{
    moveAdd(1, 0);
}

AutoControlThing *Enemy::shoot()
{
    return null;
}

Bullet::Bullet(int posI, int posJ, int speedI, int speedJ):
    AutoControlThing(BulletType), life(2)
{
    i = posI;
    j = posJ;
    di = speedI;
    dj = speedJ;
    look = createArray<char>(1, 1);
    look[0][0] = '|';
    height = 1;
    width = 1;
}

void Bullet::ifBang(Thing *thing)
{
    life -= AttackTable[objectType][thing -> objectType];
}

void Bullet::ifBound(OutBoundType o)
{
    life = 0;
}

bool Bullet::live()
{
    return life > 0;
}

void Bullet::handle()
{
    moveAdd(di, dj);
}

AutoControlThing *Bullet::shoot()
{
    return null;
}
