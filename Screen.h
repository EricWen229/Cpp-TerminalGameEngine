#ifndef Screen_H
#define Screen_H

class Screen
{
    private:
        char **buffer;
        char **lastBuffer;
        int width, height;
        
    public:
        Screen(int w, int h);
        ~Screen();
        void print();
};

#endif
