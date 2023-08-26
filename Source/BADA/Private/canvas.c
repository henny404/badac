#include "canvas.h"

static uint32_t* s_canvas;
static size_t s_rows;
static size_t s_cols;

typedef struct history {
    int x;
    int y;
    int prev_color;
}his_t;

his_t undo_stack[256];
int undo_index = -1;

his_t redo_stack[256];
int redo_index = -1;

void set_canvas(uint32_t* canvas, size_t rows, size_t cols)
{
    s_canvas = canvas;
    s_rows = rows;
    s_cols = cols;

}

void release_canvas(void)
{
    
}

void draw_pixel(size_t x, size_t y, uint32_t rgb_color)
{
    if (undo_index == 255)
    {
        for (size_t i = 0; i < 255; ++i)
        {
            undo_stack[i].x = undo_stack[i + 1].x;
            undo_stack[i].y = undo_stack[i + 1].y;
            undo_stack[i].prev_color = undo_stack[i + 1].prev_color;
        }
        --undo_index;
    }

    ++undo_index;
    undo_stack[undo_index].x = x;
    undo_stack[undo_index].y = y;
    undo_stack[undo_index].prev_color = s_canvas[y * s_cols + x];

    s_canvas[y * s_cols + x] = rgb_color;
    redo_index = -1;
}

void remove_pixel(size_t x, size_t y)
{
    if (undo_index == 255)
    {
        for (size_t i = 0; i < 255; ++i)
        {
            undo_stack[i].x = undo_stack[i + 1].x;
            undo_stack[i].y = undo_stack[i + 1].y;
            undo_stack[i].prev_color = undo_stack[i + 1].prev_color;
        }
        --undo_index;
    }
    ++undo_index;
    undo_stack[undo_index].x = x;
    undo_stack[undo_index].y = y;
    undo_stack[undo_index].prev_color = s_canvas[y * s_cols + x];

    s_canvas[y * s_cols + x] = 0xffffff;
    redo_index = -1;
}

void fill_canvas(uint32_t rgb_color)
{
    for(int i=0; i<s_rows; i++)
        for (int j = 0; j < s_cols; j++)
        {
            if (undo_index == 255)
            {
                for (size_t i = 0; i < 255; ++i)
                {
                    undo_stack[i].x = undo_stack[i + 1].x;
                    undo_stack[i].y = undo_stack[i + 1].y;
                    undo_stack[i].prev_color = undo_stack[i + 1].prev_color;
                }
                --undo_index;
            }
            ++undo_index;
            undo_stack[undo_index].x = j;
            undo_stack[undo_index].y = i;
            undo_stack[undo_index].prev_color = s_canvas[i * s_cols + j];
            s_canvas[i * s_cols + j] = rgb_color;
        }
    redo_index = -1;
}

void draw_horizontal_line(size_t y, uint32_t rgb_color)
{
    for (int i = 0; i < s_cols; i++) 
    {
        if (undo_index == 255)
        {
            for (size_t i = 0; i < 255; ++i)
            {
                undo_stack[i].x = undo_stack[i + 1].x;
                undo_stack[i].y = undo_stack[i + 1].y;
                undo_stack[i].prev_color = undo_stack[i + 1].prev_color;
            }
            --undo_index;
        }
        ++undo_index;
        undo_stack[undo_index].x = i;
        undo_stack[undo_index].y = y;
        undo_stack[undo_index].prev_color = s_canvas[y * s_cols + i];
        s_canvas[y * s_cols + i] = rgb_color;
    }

    redo_index = -1;
}

void draw_vertical_line(size_t x, uint32_t rgb_color)
{
    for (int i = 0; i < s_rows; i++)
    {
        if (undo_index == 255)
        {
            for (size_t i = 0; i < 255; ++i)
            {
                undo_stack[i].x = undo_stack[i + 1].x;
                undo_stack[i].y = undo_stack[i + 1].y;
                undo_stack[i].prev_color = undo_stack[i + 1].prev_color;
            }
            --undo_index;
        }
        ++undo_index;
        undo_stack[undo_index].x = x;
        undo_stack[undo_index].y = i;
        undo_stack[undo_index].prev_color = s_canvas[i * s_cols + x];
        s_canvas[i * s_cols + x] = rgb_color;
    }
    redo_index = -1;
}

void draw_rectangle(size_t start_x, size_t start_y, size_t end_x, size_t end_y, uint32_t rgb_color)
{
    for (int i = start_y; i <= end_y; i++)
        for (int j = start_x; j <= end_x; j++) {
            if (undo_index == 255)
            {
                for (size_t k = 0; k < 255; ++k)
                {
                    undo_stack[k].x = undo_stack[k + 1].x;
                    undo_stack[k].y = undo_stack[k + 1].y;
                    undo_stack[k].prev_color = undo_stack[k + 1].prev_color;
                }
                --undo_index;
            }
            ++undo_index;
            undo_stack[undo_index].x = j;
            undo_stack[undo_index].y = i;
            undo_stack[undo_index].prev_color = s_canvas[i * s_cols + j];
            s_canvas[i * s_cols + j] = rgb_color;
        }
    redo_index = -1;
}

int undo(void)
{
    if (undo_index >= 0) {
        redo_index++;

        int x = undo_stack[undo_index].x;
        int y = undo_stack[undo_index].y;

        redo_stack[redo_index].prev_color = s_canvas[y * s_cols + x];
        redo_stack[redo_index].x = x;
        redo_stack[redo_index].y = y;

        s_canvas[y * s_cols + x] = undo_stack[undo_index].prev_color;
        --undo_index;
        return TRUE;
    }
    return FALSE;
}

int redo(void)
{
    if (redo_index >= 0) {
        undo_index++;

        int x = redo_stack[redo_index].x;
        int y = redo_stack[redo_index].y;

        undo_stack[undo_index].prev_color = s_canvas[y * s_cols + x];
        undo_stack[undo_index].x = x;
        undo_stack[undo_index].y = y;

        s_canvas[y * s_cols + x] = redo_stack[redo_index].prev_color;
        --redo_index;
    }
    return FALSE;
}