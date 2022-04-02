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

    char *title1 = "                                    _";
    char *title2 = "   __ _ _ __ ___   __ _ _______  __| |";
    char *title3 = "  / _` | '_ ` _ \\ / _` |_  / _ \\/ _` |";
    char *title4 = " | (_| | | | | | | (_| |/ /  __/ (_| |";
    char *title5 = "  \\__,_|_| |_| |_|\\__,_/___\\___|\\__,_|";

    int title_len = strlen(title1);
    mvprintw((rows / 2) - (menu_rows / 2) + 2, (cols / 2) - (title_len / 2) - 2,
             "%s", title1);
    mvprintw((rows / 2) - (menu_rows / 2) + 3, (cols / 2) - (title_len / 2) - 2,
             "%s", title2);
    mvprintw((rows / 2) - (menu_rows / 2) + 4, (cols / 2) - (title_len / 2) - 2,
             "%s", title3);
    mvprintw((rows / 2) - (menu_rows / 2) + 5, (cols / 2) - (title_len / 2) - 2,
             "%s", title4);
    mvprintw((rows / 2) - (menu_rows / 2) + 6, (cols / 2) - (title_len / 2) - 2,
             "%s", title5);

    getch();
    return menu_choice;
}
