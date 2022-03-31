#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER 'O'
#define EMPTY ' '
#define WALL '.'
#define GOAL 'X'
#define UP 'k'
#define DOWN 'j'
#define LEFT 'h'
#define RIGHT 'l'
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
    // init variables
    bool win = false;
    char maze[row][col];
    init_maze(maze);

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
        // TODO
        // more maze generation algorithms
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
    int srow = 1;
    int scol = 1;
    int erow = row - 1;
    int ecol = col - 1;
    struct node {
        int row;
        int col;
        int id;
        char ch;
        bool visited;
    };
    struct node nodes[(erow - srow) * (ecol - scol)];

    // add walls nodes
    int node_i = 0;
    for (int i = srow; i < erow; i++) {
        for (int j = scol; j < ecol; j++) {
            if (i % 2 == 0 || j % 2 == 0) maze[i][j] = WALL;
            struct node new_node;
            new_node.row = i;
            new_node.col = j;
            new_node.id = node_i;
            new_node.ch = maze[i][j];
            new_node.visited = false;
            nodes[node_i] = new_node;
            node_i++;
        }
    }

    int rand_id, rand_row, rand_col;
}
