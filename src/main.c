#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "menu.h"

#define UP_KEY 'k'
#define DOWN_KEY 'j'
#define LEFT_KEY 'h'
#define RIGHT_KEY 'l'
#define QUIT_KEY 'q'

void setup();
void run();
void exit_program();

int rows, cols;

int main(void) {
    srand(time(0));
    setup();
    run();
    exit_program();
    return 0;
}

void setup() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, rows, cols);
    if ((rows - 2) % 2 == 0) {
        rows--;
    }
    if ((cols - 2) % 2 == 0) {
        cols--;
    }
}

void run() {
    int maze_level = maze_menu(rows + 2, cols + 2);

    bool win = false;
    char maze[rows - 2][cols - 2];
    init_maze(maze_level, rows - 2, cols - 2, maze);
    int player_row, player_col;
    for (int i = 0; i < rows - 2; i++) {
        bool found = false;
        for (int j = 0; j < cols - 2; j++) {
            if (maze[i][j] == PLAYER) {
                player_row = i;
                player_col = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    // the game loop
    do {
        maze[player_row][player_col] = PLAYER;
        print_maze(rows - 2, cols - 2, rows, cols, maze);
        move(0, 0);
        refresh();

        char key = getch();
        maze[player_row][player_col] = EMPTY;
        switch (key) {
            case QUIT_KEY:
                maze_menu(rows + 2, cols + 2);
            case UP_KEY:
                if (player_row - 1 < 0) break;
                if (maze[player_row - 1][player_col] == WALL) break;
                player_row--;
                break;
            case DOWN_KEY:
                if (player_row + 1 >= rows) break;
                if (maze[player_row + 1][player_col] == WALL) break;
                player_row++;
                break;
            case LEFT_KEY:
                if (maze[player_row][player_col - 1] == WALL) break;
                player_col--;
                break;
            case RIGHT_KEY:
                if (player_col + 1 >= cols) break;
                if (maze[player_row][player_col + 1] == WALL) break;
                player_col++;
                break;
            default:
                break;
        }
        if (maze[player_row][player_col] == GOAL) win = true;
        refresh();
    } while (!win);
}

void exit_program() { endwin(); }

