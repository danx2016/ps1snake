#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdint.h>

#define SNAKE_GRID_COLS 20
#define SNAKE_GRID_ROWS 15

// up=0110 down=1110 left=1001 right=1011
#define SNAKE_DIR_UP     6
#define SNAKE_DIR_DOWN  14
#define SNAKE_DIR_LEFT   9
#define SNAKE_DIR_RIGHT 11 

#define SNAKE_EMPTY      0
#define SNAKE_HEAD      15
#define SNAKE_FOOD      16

#define SNAKE_STATUS_PLAYING   1
#define SNAKE_STATUS_GAME_OVER 2

extern uint32_t game_score;
extern uint8_t game_status;
extern uint8_t game_grid[SNAKE_GRID_ROWS][SNAKE_GRID_COLS];

extern void reset_game(void);
extern void set_snake_direction(uint8_t direction);
extern void game_tick();

#endif /* _SNAKE_H_ */