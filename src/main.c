#include <ncurses.h>

#define PLAYER 'O'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define EMPTY ' '
#define WALL 'I'
#define QUIT 'q'

int row, col;

void setup();
void run();
void exit_program();

void init_maze(char maze[row][col]);

int main(void) {
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
    getmaxyx(stdscr, row, col);
}

void run() {
    char maze[row][col];
    init_maze(maze);

    // init variables
    int player_row = row / 2;
    int player_col = col / 2;

    // the game loop
    do {
        maze[player_row][player_col] = PLAYER;
        for (int i = 0; i < row; i++) {
            mvprintw(i, 0, "%s", maze[i]);
        }
        move(0, 0);
        refresh();

        char key = getch();
        maze[player_row][player_col] = EMPTY;
        switch (key) {
            case QUIT:
                return;
            case UP:
                if (player_row - 1 < 0) break;
                if (maze[player_row - 1][player_col] == WALL) break;
                player_row--;
                break;
            case DOWN:
                if (player_row + 1 >= row) break;
                if (maze[player_row + 1][player_col] == WALL) break;
                player_row++;
                break;
            case LEFT:
                if (player_col - 1 < 0) break;
                if (maze[player_row][player_col - 1] == WALL) break;
                player_col--;
                break;
            case RIGHT:
                if (player_col + 1 >= col) break;
                if (maze[player_row][player_col + 1] == WALL) break;
                player_col++;
                break;
            default:
                break;
        }
        refresh();
    } while (true);
}

void exit_program() { endwin(); }

void init_maze(char maze[row][col]) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) maze[i][j] = EMPTY;
    for (int i = 0; i < row; i++) {
        maze[i][0] = WALL;
        maze[i][col - 1] = WALL;
    }
    for (int i = 0; i < col; i++) {
        maze[0][i] = WALL;
        maze[row - 1][i] = WALL;
    }
}
