#include <ncurses.h>

int main()
{
    initscr(); /* Start curses mode */
    cbreak(); /* Line buffering disabled, Pass on
* everty thing to me */
    keypad(stdscr, TRUE); /* I need that nifty F1 */
    WINDOW *local_win;
    local_win = newwin(10, 9, 0, 0);
    char buffer[][10]=
    {
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "abcdefgd3",
        "012345678"
    };
    for (int i = 0; i < 10; i++)
    {
        wprintw(local_win, buffer[i]);
    }
    wrefresh(local_win); /* Show that box */
}
