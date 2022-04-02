#include "maze.h"

void init_maze(const int maze_level, const int rows, const int cols,
               char maze[rows][cols]) {
    clear_maze(rows, cols, maze);
    switch (maze_level) {
        case 0:
            generate_random_walls(rows, cols, maze);
            break;
        case 1:
            generate_aldous_broder(rows, cols, maze);
            break;
        // TODO
        // more maze generation algorithms
        default:
            generate_random_walls(rows, cols, maze);
            break;
    }
}

void print_maze(const int rows, const int cols, const int total_rows,
                const int total_cols, char maze[rows][cols]) {
    start_color();
    init_pair(EMPTY_COLOR, COLOR_BLACK, COLOR_BLACK);  // walls
    init_pair(WALL_COLOR, COLOR_WHITE, COLOR_WHITE);   // walls
    init_pair(PLAYER_COLOR, COLOR_BLUE, COLOR_BLACK);  // player
    init_pair(GOAL_COLOR, COLOR_GREEN, COLOR_BLACK);   // player
    attron(COLOR_PAIR(WALL_COLOR));
    for (int i = 0; i < total_rows; i++) {
        mvprintw(i, 0, "%c", WALL);
        mvprintw(i, total_cols - 1, "%c", WALL);
    }
    for (int i = 0; i < total_cols; i++) {
        mvprintw(0, i, "%c", WALL);
        mvprintw(total_rows - 1, i, "%c", WALL);
    }
    attroff(COLOR_PAIR(WALL_COLOR));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (maze[i][j]) {
                case WALL:
                    attron(COLOR_PAIR(WALL_COLOR));
                    mvprintw(i + 1, j + 1, "%c", maze[i][j]);
                    attroff(COLOR_PAIR(WALL_COLOR));
                    break;
                case PLAYER:
                    attron(COLOR_PAIR(PLAYER_COLOR));
                    attron(A_BOLD);
                    mvprintw(i + 1, j + 1, "%c", maze[i][j]);
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(PLAYER_COLOR));
                    break;
                case GOAL:
                    attron(COLOR_PAIR(GOAL_COLOR));
                    attron(A_BOLD);
                    mvprintw(i + 1, j + 1, "%c", maze[i][j]);
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(GOAL_COLOR));
                    break;
                case EMPTY:
                    attron(COLOR_PAIR(EMPTY_COLOR));
                    mvprintw(i + 1, j + 1, "%c", maze[i][j]);
                    attroff(COLOR_PAIR(EMPTY_COLOR));
                    break;
                default:
                    mvprintw(i + 1, j + 1, "%c", maze[i][j]);
                    break;
            }
        }
    }
}

void clear_maze(const int rows, const int cols, char maze[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maze[i][j] = EMPTY;
        }
    }
}

int init_walls(const int rows, const int cols, char maze[rows][cols]) {
    int node_count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 != 0 || j % 2 != 0)
                maze[i][j] = WALL;
            else {
                node_count++;
            }
        }
    }
    return node_count;
}

void init_nodes(const int rows, const int cols, const int node_count,
                Node nodes[node_count]) {
    int node_i = 0;
    for (int i = 0; i < rows; i += 2) {
        for (int j = 0; j < cols; j += 2) {
            Node new_node;
            new_node.row = i;
            new_node.col = j;
            new_node.visited = false;
            nodes[node_i] = new_node;
            node_i++;
        }
    }
}

void generate_random_walls(const int rows, const int cols,
                           char maze[rows][cols]) {
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
    maze[rows / 2][cols / 2] = PLAYER;
}

void generate_aldous_broder(const int rows, const int cols,
                            char maze[rows][cols]) {
    int node_count = init_walls(rows, cols, maze);
    Node nodes[node_count];
    init_nodes(rows, cols, node_count, nodes);

    // get random starting node
    Node start_node = nodes[0];
    start_node.visited = true;
    maze[start_node.row][start_node.col] = PLAYER;
    Node curr_node = start_node;

    // populate maze
    bool all_visited = false;
    int temp = 0;
    do {
        Node* next_node;
        bool dir_chose = false;
        int row_offset = 0;
        int col_offset = 0;
        do {
            int rand_dir = rand() % 4;
            switch (rand_dir) {
                case UP:
                    if (curr_node.row - 2 >= 0) {  // can move
                        dir_chose = true;
                        row_offset = -2;
                    }
                    break;
                case DOWN:
                    if (curr_node.row + 2 >= 0) {  // can move
                        dir_chose = true;
                        row_offset = 2;
                    }
                    break;
                case LEFT:
                    if (curr_node.col - 2 >= 0) {  // can move
                        dir_chose = true;
                        col_offset = -2;
                    }
                    break;
                case RIGHT:
                    if (curr_node.col + 2 >= 0) {  // can move
                        dir_chose = true;
                        col_offset = 2;
                    }
                    break;
            }
            for (int i = 0; i < node_count; i++) {  // find next node
                if (nodes[i].row == curr_node.row + row_offset &&
                    nodes[i].col == curr_node.col + col_offset) {
                    next_node = &nodes[i];
                    break;
                }
            }
            if (!next_node->visited) {
                maze[next_node->row - (row_offset / 2)]
                    [next_node->col - (col_offset / 2)] = EMPTY;
                next_node->visited = true;
            }

            curr_node = *next_node;
        } while (!dir_chose);
        for (int i = 0; i < node_count; i++) {
            if (!nodes[i].visited) break;
            if (i == node_count - 1) {
                all_visited = true;
                maze[curr_node.row][curr_node.col] = GOAL;
            }
        }
    } while (!all_visited);
}
