#include <ncurses.h>
#include <panel.h>

int main()
{
    initscr();
    start_color();
    
    /* move(20, 30); */
    /* addch('c'); */
    /* mvaddch(30, 20, 'a'); */
    /* printw("Hello World !"); */
    
    /* int col, row; */
    /* getmaxyx(stdscr, row, col); */
    /* getyx(stdscr, row, col); */
    /* printw("%d %d", row, col); */
    
    WINDOW *win = newwin(10, 10, 10, 10);
    box(win, 0, 0);
    wrefresh(win);
    
    refresh();
    
    getch();
    endwin();
    return 0;
}
