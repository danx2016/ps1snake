
#include <sys/types.h>
#include <libetc.h>
#include <libgpu.h>
#include <libgte.h>
#include <stdlib.h>
#include <stdint.h>

#include "snake.h"
 
DISPENV disp[2];
DRAWENV draw[2]; 
int32_t db = 0;

// grid cell colors
CVECTOR gcc[18] = {
    {   0,   0,   0 }, {   0,   0, 255 },
    {   0,   0, 255 }, {   0,   0, 255 },
    {   0,   0, 255 }, {   0,   0, 255 },
    {   0,   0, 255 }, {   0,   0, 255 },
    {   0,   0, 255 }, {   0,   0, 255 },
    {   0,   0, 255 }, {   0,   0, 255 },
    {   0,   0, 255 }, {   0,   0, 255 },
    {   0,   0, 255 }, { 255,   0,   0 },
    {   0, 255,   0 }, {   0,   0, 255 }
};

int32_t first_play = 1;

void update_snake_direction()
{
    uint32_t padInfo = PadRead(0);

    if (padInfo & _PAD(0, PADLup))
    {
        set_snake_direction(UP);
    }
    if (padInfo & _PAD(0, PADLdown))
    {
        set_snake_direction(DOWN);
    }
    if (padInfo & _PAD(0, PADLleft))
    {
        set_snake_direction(LEFT);
    }
    if (padInfo & _PAD(0, PADLright))
    {
        set_snake_direction(RIGHT);
    }

    if (padInfo && game_status == SNAKE_STATUS_GAME_OVER)
    {
        srand(VSync(-1));
        reset_game();
        first_play = 0;
    }
}

void render()
{
    if (game_status == SNAKE_STATUS_PLAYING)
    {
        for (uint8_t row = 0; row < SNAKE_GRID_ROWS; row++)
        {
            for (uint8_t col = 0; col < SNAKE_GRID_COLS; col++)
            {
                uint8_t cid = game_grid[row][col];
                if (cid > 0)
                {
                    TILE_16 tile;
                    setTile16(&tile);
                    setRGB0(&tile, gcc[cid].r, gcc[cid].g, gcc[cid].b);
                    setXY0(&tile, 16 * col, 16 * row);
                    DrawPrim(&tile);
                    DrawSync(0);
                }
            }
        }
    }
    else if (first_play)
    {
        FntPrint(1, "PRESS BUTTON TO START");
    }
    else
    {
        FntPrint(1, "     GAME OVER !     ");    
    }
    FntPrint(0, "SCORE %d", game_score);    
}

int main()
{
    ResetGraph(0);
    PadInit(0);

    SetDefDispEnv(&disp[0], 0, 0, 320, 240);
    SetDefDispEnv(&disp[1], 0, 240, 320, 240);
    SetDefDrawEnv(&draw[0], 0, 240, 320, 240);
    SetDefDrawEnv(&draw[1], 0, 0, 320, 240);

    draw[0].isbg = 1;
    draw[1].isbg = 1;
    setRGB0(&draw[0], 32, 32, 32);
    setRGB0(&draw[1], 32, 32, 32);
    SetDispMask(1);
    
    FntLoad(320, 0);
    FntOpen(12, 16, 256, 64, 0, 512);
    FntOpen(72, 108, 200, 64, 0, 512);
    
    uint32_t frame_count = 0;

    while (1)
    {
        update_snake_direction();
        if (frame_count++ % 10 == 0)
        {
            game_tick();
        }
        render();

        FntFlush(0);
        FntFlush(1);
        DrawSync(0);
        VSync(0);
        db = !db;
        PutDispEnv(&disp[db]);
        PutDrawEnv(&draw[db]);
    }

    return 0;
}