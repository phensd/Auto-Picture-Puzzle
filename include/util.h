#pragma once
#include <raylib.h>

namespace puzzle_game::util{

    void setup_window(const Image* puzzle_image,int divisor);

    Image conform_image(Image* image);

    void set_window_icon(Image image);

}
