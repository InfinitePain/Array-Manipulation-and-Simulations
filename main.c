/*
=============================================================================
 Name        : main.c
 Author      : InfinitePain
 License     : Apache License 2.0
 Description : Source file for Ascii-Numeric Utility
=============================================================================
*/

#include "utilities.h"
#include "time.h"
#include "stdlib.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    curs_set(0);
    srand(time(NULL));

    bool should_quit = false;
    if (!create_app_menu())
    {
        mvprintw(error_line, 0, "Error creating menu. Press any key to exit.");
        getch();
        endwin();
        return 1;
    }
    if (COLS < 60 || LINES < 19 )
    {
        delete_menu();
        endwin();
        printf("Terminal size is too small. Please ensure that the terminal is at least 60x19.\n");
        printf("Press enter to exit.");
        getchar();
        return 1;
    }
    int key;
    while (should_loop)
    {
        print_menu();
        key = getch();
        custom_menu_driver(key);
    }
    delete_menu();
    endwin();
    return 0;
}
