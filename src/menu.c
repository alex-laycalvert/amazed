#include "menu.h"

int maze_menu(const int rows, const int cols) {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    int menu_rows = 20;
    int menu_cols = 50;
    int menu_choice = 0;

    attron(COLOR_PAIR(1));
    for (int i = 0; i < menu_rows; i++) {
        mvprintw(i + (rows / 2) - (menu_rows / 2), (cols / 2) - (menu_cols / 2),
                 "I");
        mvprintw(i + (rows / 2) - (menu_rows / 2), (cols / 2) + (menu_cols / 2),
                 "I");
    }
    for (int i = 0; i <= menu_cols; i++) {
        mvprintw((rows / 2) - (menu_rows / 2), i + (cols / 2) - (menu_cols / 2),
                 "I");
        mvprintw((rows / 2) + (menu_rows / 2), i + (cols / 2) - (menu_cols / 2),
                 "I");
    }
    attroff(COLOR_PAIR(1));

    char *title[6];
    title[0] = "                                   _";
    title[1] = "   __ _ _ __ ___   __ _ _______  __| |";
    title[2] = "  / _` | '_ ` _ \\ / _` |_  / _ \\/ _` |";
    title[3] = " | (_| | | | | | | (_| |/ /  __/ (_| |";
    title[4] = "  \\__,_|_| |_| |_|\\__,_/___\\___|\\__,_|";
    title[5] = "by: alex-laycalvert";

    for (int i = 0; i < 6; i++) {
        mvprintw((rows / 2) - (menu_rows / 2) + 1 + i,
                 (cols / 2) - (strlen(title[i]) / 2), "%s", title[i]);
    }

    attron(COLOR_PAIR(1));
    for (int i = 0; i < menu_cols; i++) {
        mvprintw((rows / 2) - (menu_rows / 2) + 8,
                 (cols / 2) - (menu_cols / 2) + i, "I");
    }
    attroff(COLOR_PAIR(1));

    char *options[4];
    options[0] = "Randomly Generated Walls";
    options[1] = "Aldous-Broder";
    options[2] = "High Scores (coming soon...)";
    options[3] = "Exit";

    for (int i = 0; i < 4; i++) {
        mvprintw((rows / 2) + i, (cols / 2) - (strlen(options[i]) / 2), "%s",
                 options[i]);
    }

    getch();
    return menu_choice;
}
