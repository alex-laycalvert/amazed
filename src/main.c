#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER 'O'
#define EMPTY ' '
#define WALL 'I'
#define GOAL 'X'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define QUIT 'q'

#define MAZE_LEVEL 1

struct point {
    int y;
    int x;
};

int row, col;

void setup();
void run();
void exit_program();

void init_maze(char maze[row][col]);
void clear_maze(char maze[row][col]);
void generate_random_walls(char maze[row][col]);
void generate_aldous_broder(char maze[row][col]);

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
    getmaxyx(stdscr, row, col);
    if (row % 2 == 0) row--;
    if (col % 2 == 0) col--;
}

void run() {
    bool win = false;
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
        if (maze[player_row][player_col] == GOAL) win = true;
        refresh();
    } while (!win);
}

void exit_program() { endwin(); }

void init_maze(char maze[row][col]) {
    clear_maze(maze);
    for (int i = 0; i < row; i++) {
        maze[i][0] = WALL;
        maze[i][col - 1] = WALL;
    }
    for (int i = 0; i < col; i++) {
        maze[0][i] = WALL;
        maze[row - 1][i] = WALL;
    }

    switch (MAZE_LEVEL) {
        case 0:
            generate_random_walls(maze);
            break;
        case 1:
            generate_aldous_broder(maze);
            break;
        default:
            break;
    }
}

void clear_maze(char maze[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            maze[i][j] = EMPTY;
        }
    }
}

void generate_random_walls(char maze[row][col]) {
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < col - 1; j++) {
            if (rand() % 10 == 9)
                maze[i][j] = WALL;
            else
                maze[i][j] = EMPTY;
        }
    }
    int goal_row, goal_col;
    do {
        goal_row = rand() % row;
    } while (goal_row <= 0 || goal_row >= row - 1 || goal_row == row / 2);
    do {
        goal_col = rand() % col;
    } while (goal_col <= 0 || goal_col >= col - 1 || goal_col == col / 2);
    maze[goal_row][goal_col] = GOAL;
}

void generate_aldous_broder(char maze[row][col]) {
    int points_to_visit = ((row - 2) / 2) * ((col - 2) / 2);
    struct point visited[points_to_visit];
    for (int i = 0; i < points_to_visit; i++) {
        struct point tmp_point;
        tmp_point.x = -1;
        tmp_point.y = -1;
        visited[i] = tmp_point;
    }
    int curr_row, curr_col;
    int rand_row, rand_col;
    do {
        rand_row = rand() % (row - 2) + 1;
    } while (rand_row % 2 == 0);
    do {
        rand_col = rand() % (col - 2) + 1;
    } while (rand_row % 2 == 0);
    curr_row = rand_row;
    curr_col = rand_col;

    /* TODO */
    return;

    do {
    } while (visited[points_to_visit - 1].x < 0);
}
