#include "Interface.h"
#include "../Semaphore/Semaphore.h"
#include "../Array/Array.h"
#include <iostream>

/* EventBuffer eb; */

/* void *get(void *unused) */
/* { */
/*     Event e = eb.get(); */
/*     std::cout << e << std::endl; */
/*     return null; */
/* } */

/* void *put(void *unused) */
/* { */
/*     eb.put(Up); */
/*     eb.put(Right); */
/*     eb.put(Left); */
/*     return null; */
/* } */

/* int main() */
/* { */
/*     pthread_t p1 = createPthread(get); */
/*     /1* pthread_t p2 = createPthread(put); *1/ */
/*     pthread_t p3 = createPthread(get); */

/*     char c; */
/*     for (int i = 0; i < 2; i++) */
/*     { */
/*         std::cin >> c; */
/*         eb.put(Up); */
/*     } */

/*     waitPthread(p1); */
/*     /1* waitPthread(p2); *1/ */
/*     waitPthread(p3); */
/* } */

SmartArray<char> s = createArray<char>(10, 10);

bool handler(Event e)
{
    switch (e)
    {
        case Up:
            s[0][0] += 1;
            break;
        case Down:
            s[0][0] -= 1;
            break;
        case Left:
            break;
        case Right:
            break;
        case Quit:
            return true;
    }
    return false;
}

int main()
{
    Ncurses ns;
    for (int i = 0; i < s -> height; i++)
    {
        for (int j = 0; j < s -> width; j++)
        {
            s[i][j]='f';
        }
        s[i][s -> width - 1] = '\0';
    }
    ns.init(s, handler);
    ns.loop();
    ns.end();
}
