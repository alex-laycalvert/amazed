#ifndef MAZE_H_
#define MAZE_H_

#include <ncurses.h>
#include <stdlib.h>

#define PLAYER 'O'
#define EMPTY ' '
#define WALL 'I'
#define GOAL 'X'

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define RANDOM_WALL_CHANCE 10

void init_maze(const int maze_level, const int rows, const int cols,
               char maze[rows][cols]);
void print_maze(const int rows, const int cols, const int total_rows,
                const int total_cols, char maze[rows][cols]);
void clear_maze(const int rows, const int cols, char maze[rows][cols]);
void generate_random_walls(const int rows, const int cols,
                           char maze[rows][cols]);
void generate_aldous_broder(const int rows, const int cols,
                            char maze[rows][cols]);

#endif  // MAZE_H_
