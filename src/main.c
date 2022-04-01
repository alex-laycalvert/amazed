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
#define RANDOM_WALL_CHANCE 10

struct point {
    int y;
    int x;
};

int total_rows, total_cols;
int rows, cols;

void setup();
void run();
void exit_program();

void init_maze(char maze[rows][cols]);
void clear_maze(char maze[rows][cols]);
void print_maze(char maze[rows][cols]);
void generate_random_walls(char maze[rows][cols]);
void generate_aldous_broder(char maze[rows][cols]);

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
    getmaxyx(stdscr, total_rows, total_cols);
    rows = total_rows - 2;
    cols = total_cols - 2;
    if (rows % 2 == 0) {
        total_rows--;
        rows--;
    }
    if (cols % 2 == 0) {
        total_cols--;
        cols--;
    }
}

void run() {
    // init variables
    bool win = false;
    char maze[rows][cols];
    init_maze(maze);

    int player_row = rows / 2;
    int player_col = cols / 2;

    // the game loop
    do {
        maze[player_row][player_col] = PLAYER;
        print_maze(maze);
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
                if (player_row + 1 >= rows) break;
                if (maze[player_row + 1][player_col] == WALL) break;
                player_row++;
                break;
            case LEFT:
                if (player_col - 1 < 0) break;
                if (maze[player_row][player_col - 1] == WALL) break;
                player_col--;
                break;
            case RIGHT:
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

void init_maze(char maze[rows][cols]) {
    clear_maze(maze);
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
            generate_random_walls(maze);
            break;
    }
}

void print_maze(char maze[rows][cols]) {
    for (int i = 0; i < total_rows; i++) {
        mvprintw(i, 0, "%c", WALL);
        mvprintw(i, total_cols - 1, "%c", WALL);
    }
    for (int i = 0; i < total_cols; i++) {
        mvprintw(0, i, "%c", WALL);
        mvprintw(total_rows - 1, i, "%c", WALL);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mvprintw(i + 1, j + 1, "%c", maze[i][j]);
        }
    }
}

void clear_maze(char maze[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maze[i][j] = EMPTY;
        }
    }
}

void generate_random_walls(char maze[rows][cols]) {
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (rand() % RANDOM_WALL_CHANCE == 0)
                maze[i][j] = WALL;
            else
                maze[i][j] = EMPTY;
        }
    }
    int goal_row, goal_col;
    do {
        goal_row = rand() % rows;
    } while (goal_row <= 0 || goal_row >= rows || goal_row == rows / 2);
    do {
        goal_col = rand() % cols;
    } while (goal_col <= 0 || goal_col >= cols || goal_col == cols / 2);
    maze[goal_row][goal_col] = GOAL;
}

void generate_aldous_broder(char maze[rows][cols]) {
    struct node {
        int id;
        int row;
        int col;
        bool visited;
    };

    // set walls between nodes
    int node_count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 != 0 || j % 2 != 0)
                maze[i][j] = WALL;
            else
                node_count++;
        }
    }

    // initialize nodes
    struct node nodes[node_count];
    int node_i = 0;
    for (int i = 0; i < rows; i += 2) {
        for (int j = 0; j < cols; j += 2) {
            struct node new_node;
            new_node.id = node_i;
            new_node.row = i;
            new_node.col = j;
            new_node.visited = false;
            nodes[node_i] = new_node;
            node_i++;
        }
    }

    // get random starting node
    struct node start_node = nodes[rand() % node_count];
    start_node.visited = true;
    nodes[start_node.id] = start_node;
    maze[start_node.row][start_node.col] = '@';
    struct node curr_node = start_node;

    bool all_nodes_visited = false;
    int row_offset, col_offset, rand_dir;
    bool dir_chose = false;
    int temp = 9;
    do {
        do {
            dir_chose = true;
            rand_dir = rand() % 4;
            printf("RAND %d", rand_dir);
            row_offset = 0;
            col_offset = 0;
            switch (rand_dir) {
                case 0:
                    if (curr_node.row - 2 >= 0)
                        row_offset = -2;
                    else
                        dir_chose = false;
                    break;
                case 1:
                    if (curr_node.row + 2 < rows)
                        row_offset = 2;
                    else
                        dir_chose = false;
                    break;
                case 2:
                    if (curr_node.col - 2 >= 0)
                        col_offset = -2;
                    else
                        dir_chose = false;
                    break;
                case 3:
                    if (curr_node.col + 2 < cols)
                        col_offset = 2;
                    else
                        dir_chose = false;
                    break;
                default:
                    break;
            }
        } while (!dir_chose);
        for (int i = 0; i < node_count; i++) {
            if (nodes[i].row == curr_node.row + row_offset &&
                nodes[i].col == curr_node.col + col_offset)
                curr_node = nodes[i];
        }
        maze[curr_node.row][curr_node.col] = '@';
        curr_node.visited = true;
        nodes[curr_node.id] = curr_node;
        for (int i = 0; i < node_count; i++) {
            if (!nodes[i].visited) break;
            if (i == node_count - 1) all_nodes_visited = true;
        }
        temp++;
    } while (temp < 10);
}
