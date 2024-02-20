#include "include/util.h"
#include "include/constants.h"
#include <iostream>
#include <format>

namespace puzzle_game{

    //Set up the window, taking into account that dividing an image into smaller pieces
    //will cause some floating point imprecision, (atleast in the formats that raylib supports?)
    void util::setup_window(const Image* puzzle_image,int divisor){
        //images cant store floating point values
        //so have to make sure window compensates for inevitable loss
        int wwidth {(puzzle_image->width - (puzzle_image->width/divisor*divisor))};
        int hheight {(puzzle_image->height - (puzzle_image->height/divisor*divisor))};
        SetWindowSize(puzzle_image->width - wwidth, puzzle_image->height - hheight);

    }

    //Resize image to be atleast a bit smaller than the user's monitor
    Image util::conform_image(Image* image){
        Image return_image {ImageCopy(*image)};
        const int USER_MONITOR_HEIGHT = GetMonitorHeight(GetCurrentMonitor());
        const int USER_MONITOR_WIDTH = GetMonitorWidth(GetCurrentMonitor());
        while(return_image.height >= USER_MONITOR_HEIGHT-puzzle_game::constants::FORCED_FREE_SPACE_ON_MONITOR or
        return_image.width >= USER_MONITOR_WIDTH-puzzle_game::constants::FORCED_FREE_SPACE_ON_MONITOR) {
            ImageResize(&return_image,return_image.width*0.90,return_image.height*0.90);
        }
        return return_image;

    }

    void util::set_window_icon(Image image){
        ImageResize(&image,256,256);
        SetWindowIcon(image);

        UnloadImage(image);
    }

    std::string util::get_difficulty_string(int difficulty){
        return std::format("Difficulty ({0}x{0})",difficulty);
    }

    //Set the window title, "include_info" adds some information about keybindings
    void util::set_window_title(std::string title, bool include_info,int difficulty){

        //add brackets to the first entry
        title.insert(0,"[");
        title += "]";


        //add some space for anything that gets appended
        title += " ";

        if(include_info){
            std::string info_string {std::format("[F4] Increase {1} | [Spacebar] Scramble Puzzle | [CTRL] Preview Image | FPS:{0}",GetFPS(),get_difficulty_string(difficulty))};
            title += info_string;
        }

        SetWindowTitle(title.c_str());
    }

}
