/* #include <ncurses.h> */
/* #include <panel.h> */

/* int main() */
/* { */
/*     initscr(); */
/*     start_color(); */

/*     char buffer[][10]= */
/*     { */
/*         "abcdefg", */
/*         "nvnfdjv" */
/*     }; */

/*     /1* printw(buffer[0]); *1/ */
/*     /1* printw(buffer[1]); *1/ */

/*     WINDOW *win = newwin(2, 8, 2, 2); */
/*     box(win, 0, 0); */
/*     wrefresh(win); */

/*     /1* move(20, 30); *1/ */
/*     /1* addch('c'); *1/ */
/*     /1* mvaddch(30, 20, 'a'); *1/ */
/*     /1* printw("Hello World !"); *1/ */

/*     /1* int col, row; *1/ */
/*     /1* getmaxyx(stdscr, row, col); *1/ */
/*     /1* getyx(stdscr, row, col); *1/ */
/*     /1* printw("%d %d", row, col); *1/ */

/*     /1* refresh(); *1/ */

/*     getch(); */
/*     return 0; */
/* } */

#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{
    WINDOW *my_win;
    int startx, starty, width, height;
    int ch;
    initscr(); /* Start curses mode */
    cbreak(); /* Line buffering disabled, Pass on
* everty thing to me */
    keypad(stdscr, TRUE); /* I need that nifty F1 */
    height = 3;
    width = 10;
    starty = (LINES - height) / 2; /* Calculating for a center placement */
    startx = (COLS - width) / 2; /* of the window */
    printw("Press F1 to exit");
    refresh();
    my_win = create_newwin(height, width, starty, startx);
    while ((ch = getch()) != KEY_F(1))
    {
        switch (ch)
        {
            case KEY_LEFT:
                destroy_win(my_win);
                my_win = create_newwin(height, width, starty, --startx);
                break;
            case KEY_RIGHT:
                destroy_win(my_win);
                my_win = create_newwin(height, width, starty,++startx);
                break;
            case KEY_UP:
                destroy_win(my_win);
                my_win = create_newwin(height, width, --starty,startx);
                break;
            case KEY_DOWN:
                destroy_win(my_win);
                my_win = create_newwin(height, width, ++starty,startx);
                break;
        }
    }
    endwin(); /* End curses mode */
    return 0;
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    char buffer[][11]=
    {
        "abcdefgdge",
        "0123456789"
    };
    wprintw(local_win, buffer[0]);
    wprintw(local_win, buffer[1]);
    wrefresh(local_win); /* Show that box */
    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    /* box(local_win, ' ', ' '); : This won't produce the desired
    * result of erasing the window. It will leave it's four corners
    * and so an ugly remnant of window.
    */
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /* The parameters taken are
    * 1. win: the window on which to operate
    * 2. ls: character to be used for the left side of the window
    * 3. rs: character to be used for the right side of the window
    * 4. ts: character to be used for the top side of the window
    * 5. bs: character to be used for the bottom side of the window
    * 6. tl: character to be used for the top left corner of the window
    * 7. tr: character to be used for the top right corner of the window
    * 8. bl: character to be used for the bottom left corner of the window
    * 9. br: character to be used for the bottom right corner of the window
    */
    wrefresh(local_win);
    delwin(local_win);
}
