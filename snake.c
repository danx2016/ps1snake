#include <rand.h>
#include <memory.h>

#include "snake.h"

uint32_t game_score = 0;
uint8_t game_status = SNAKE_STATUS_GAME_OVER;
uint8_t game_grid[SNAKE_GRID_ROWS][SNAKE_GRID_COLS];

static uint8_t snake_head_col;
static uint8_t snake_head_row;
static uint8_t snake_tail_col;
static uint8_t snake_tail_row;
static uint8_t snake_direction;

static void create_food()
{
    uint8_t food_col;
    uint8_t food_row;
    do
    {
        food_col = rand() % SNAKE_GRID_COLS;
        food_row = rand() % SNAKE_GRID_ROWS;
    } 
    while (game_grid[food_row][food_col] > 0);

    game_grid[food_row][food_col] = SNAKE_FOOD;
}

void reset_game(void)
{
    memset(game_grid, SNAKE_EMPTY, SNAKE_GRID_COLS * SNAKE_GRID_ROWS * sizeof(uint8_t));
    snake_head_col = SNAKE_GRID_COLS / 2;
    snake_head_row = SNAKE_GRID_ROWS / 2;
    snake_tail_col = snake_head_col;
    snake_tail_row = snake_head_row;
    game_score = 0;
    game_status = SNAKE_STATUS_PLAYING;
    snake_direction = 1 + (rand() % 4);
    game_grid[snake_head_row][snake_head_col] = SNAKE_HEAD;
    create_food();
}

void set_snake_direction(uint8_t direction)
{
    snake_direction = direction;
}

void game_tick()
{
    if (game_status == SNAKE_STATUS_GAME_OVER)
    {
        return;
    }
    
    uint8_t snake_head_prev_col = snake_head_col;
    uint8_t snake_head_prev_row = snake_head_row;

    snake_head_col += (snake_direction & 3) - 2;
    snake_head_row += (snake_direction >> 2) - 2;

    if (snake_head_col < 0 || snake_head_row < 0 || 
        snake_head_col > SNAKE_GRID_COLS - 1 || 
        snake_head_row > SNAKE_GRID_ROWS - 1)
    {
        game_status = SNAKE_STATUS_GAME_OVER;
        return;
    }
    game_grid[snake_head_prev_row][snake_head_prev_col] = snake_direction;
    // eat food
    if (game_grid[snake_head_row][snake_head_col] == SNAKE_FOOD)
    {
        game_score++;
        game_grid[snake_head_row][snake_head_col] = SNAKE_HEAD;
        create_food();
    }
    // touch own body
    else if (game_grid[snake_head_row][snake_head_col] > 0)
    {
        game_status = SNAKE_STATUS_GAME_OVER;
        game_grid[snake_head_row][snake_head_col] = SNAKE_HEAD;
        return;
    }
    // empty
    else 
    {
        int tail_direction = game_grid[snake_tail_row][snake_tail_col];
        game_grid[snake_tail_row][snake_tail_col] = SNAKE_EMPTY;
        game_grid[snake_head_row][snake_head_col] = SNAKE_HEAD;

        snake_tail_col += (tail_direction & 3) - 2;
        snake_tail_row += (tail_direction >> 2) - 2;
    }
}
