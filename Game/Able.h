#ifndef Moveable_H
#define Moveable_H

class Moveable
{
    protected:
        int x, y;
        
    protected:
        Moveable(int x, int y);
        virtual ~Moveable();
        
    protected:
        virtual void move() = 0;
        
    public:
        int getX();
        int getY();
};

class Attackable: public virtual Moveable
{
    private:
        int power;
        int R;
        
    protected:
        Attackable(int power, int R);
        virtual ~Attackable();
        
    public:
        int attack();
};

class Lifeable: public virtual Moveable
{
    private:
        int blood;
        
    protected:
        Lifeable(int blood);
        virtual ~Lifeable();
        
    public:
        void attacked(int attack);
        bool isAilve();
};

class Bullet;
class Shootable
{
    private:
        int shootRate;
        
    protected:
        Shootable(int shootRate);
        virtual ~Shootable();
        
    public:
        virtual Bullet shoot() = 0;
};

#endif
