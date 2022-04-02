#ifndef MAZE_H_
#define MAZE_H_

#include <ncurses.h>
#include <stdlib.h>

#define EMPTY ' '
#define WALL 'I'
#define PLAYER 'O'
#define GOAL 'X'

#define EMPTY_COLOR 1
#define WALL_COLOR 2
#define PLAYER_COLOR 3
#define GOAL_COLOR 4

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define RANDOM_WALL_CHANCE 10

typedef struct node {
    int row;
    int col;
    bool visited;
} Node;

void init_maze(const int maze_level, const int rows, const int cols,
               char maze[rows][cols]);
void print_maze(const int rows, const int cols, const int total_rows,
                const int total_cols, char maze[rows][cols]);
void clear_maze(const int rows, const int cols, char maze[rows][cols]);
int init_walls(const int rows, const int cols, char maze[rows][cols]);
void init_nodes(const int rows, const int cols, const int node_count,
                Node nodes[node_count]);
void generate_random_walls(const int rows, const int cols,
                           char maze[rows][cols]);
void generate_aldous_broder(const int rows, const int cols,
                            char maze[rows][cols]);

#endif  // MAZE_H_
