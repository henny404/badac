#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h>
#include <stdint.h>

#ifndef NULL
#define NULL ((void*)(0))
#endif // NULL

#ifndef TRUE
#define TRUE (1)
#endif // TRUE

#ifndef FALSE
#define FALSE (0)
#endif // FALSE

typedef enum command {
    COMMAND_DRAW_PIXEL,
    COMMAND_REMOVE_PIXEL,
    COMMAND_FILL_CANVAS,
    COMMAND_DRAW_HORIZONTAL_LINE,
    COMMAND_DRAW_VERTICAL_LINE,
    COMMAND_DRAW_RECTANGLE,
    COMMAND_UNDO,
    COMMAND_REDO,
} command_t;

#ifdef __cplusplus
extern "C"
{
    void set_canvas(uint32_t* canvas, size_t rows, size_t cols);

    void release_canvas(void);

    void draw_pixel(size_t x, size_t y, uint32_t rgb_color);

    void remove_pixel(size_t x, size_t y);

    void fill_canvas(uint32_t rgb_color);

    void draw_horizontal_line(size_t y, uint32_t rgb_color);

    void draw_vertical_line(size_t x, uint32_t rgb_color);

    void draw_rectangle(size_t start_x, size_t start_y, size_t end_x, size_t end_y, uint32_t rgb_color);

    int undo(void);

    int redo(void);
}
#endif // __cplusplus

#endif // CANVAS_H