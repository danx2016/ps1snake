#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdint.h>

#define SNAKE_GRID_COLS 20
#define SNAKE_GRID_ROWS 15

#define SNAKE_EMPTY      0
#define SNAKE_HEAD      15
#define SNAKE_FOOD      16

#define SNAKE_STATUS_PLAYING   1
#define SNAKE_STATUS_GAME_OVER 2

// up=0110 down=1110 left=1001 right=1011
typedef enum { UP=6, DOWN=14, LEFT=9, RIGHT=11 } SNAKE_DIR;

extern uint32_t game_score;
extern uint8_t game_status;
extern uint8_t game_grid[SNAKE_GRID_ROWS][SNAKE_GRID_COLS];

extern void reset_game(void);
extern void set_snake_direction(SNAKE_DIR direction);
extern void game_tick();

#endif /* _SNAKE_H_ */