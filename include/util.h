#pragma once
#include <raylib.h>

namespace puzzle_game::util{

    void setup_window(Image* puzzle_image,int divisor=4);

    void conform_image(Image* image);

    void set_window_icon(Image image);

}
