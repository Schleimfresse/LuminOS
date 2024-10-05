#include "panic.h"
#include "../include/basic_renderer.h"
#include "../../include/string.h"

void panic(const char* panic_msg) {
    global_renderer->set_clear_color(Colour::RED);
    global_renderer->clear();

    global_renderer->set_colour(Colour::WHITE);

    int char_width = 8;
    int char_height = 16;

    int width = global_renderer->TargetFramebuffer->width;
    int height = global_renderer->TargetFramebuffer->height;

    int total_message_height = (char_height * 2) + char_height;

    int y_start = (height / 2) - (total_message_height / 2);

    int x_line1 = (width / 2) - (strlen("kernel panic") * char_width / 2);
    int x_line2 = (width / 2) - (strlen(panic_msg) * char_width / 2);

    global_renderer->set_cursorX(x_line1);
    global_renderer->set_cursorY(y_start);
    global_renderer->print("kernel panic");

    int y_line2 = y_start + char_height * 2;
    global_renderer->set_cursorX(x_line2);
    global_renderer->set_cursorY(y_line2);
    global_renderer->print(panic_msg);
}