#include "include/util.h"
#include "include/constants.h"
#include <iostream>

namespace puzzle_game::util{

    void setup_window(const Image* puzzle_image,int divisor){
        //images cant store floating point values
        //so have to make sure window compensates for inevitable loss
        int wwidth {(puzzle_image->width - (puzzle_image->width/divisor*divisor))};
        int hheight {(puzzle_image->height - (puzzle_image->height/divisor*divisor))};
        SetWindowSize(puzzle_image->width - wwidth, puzzle_image->height - hheight);

    }

    Image conform_image(Image* image){
        //awk to read
        Image return_image {ImageCopy(*image)};
        const int USER_MONITOR_HEIGHT = GetMonitorHeight(GetCurrentMonitor());
        const int USER_MONITOR_WIDTH = GetMonitorWidth(GetCurrentMonitor());
        while(return_image.height >= USER_MONITOR_HEIGHT-puzzle_game::constants::FORCED_FREE_SPACE_ON_MONITOR or
        return_image.width >= USER_MONITOR_WIDTH-puzzle_game::constants::FORCED_FREE_SPACE_ON_MONITOR) {
            ImageResize(&return_image,return_image.width*0.90,return_image.height*0.90);
        }
        return return_image;

    }

    void set_window_icon(Image image){
        ImageResize(&image,256,256);
        SetWindowIcon(image);

        UnloadImage(image);
    }

}
