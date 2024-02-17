#pragma once
#include <raylib.h>
#include <string>
namespace puzzle_game::util{

    void set_window_icon(Image image);

    void set_window_title(std::string title, bool include_info=false,int difficulty=0);

    void setup_window(const Image* puzzle_image,int divisor);

    std::string get_difficulty_string(int difficulty);

    Image conform_image(Image* image);



}
