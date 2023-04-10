#include <iostream>
#include <raylib.h>
#include "include/constants.h"
#include <cassert>
#include <vector>
#include "include/puzzle.h"
#include <sstream>




void setup_window(Image& puzzle_image,int divisor=4){

    //images cant store floating point values
    //so have to make sure window compensates for inevitable loss 
    int wwidth {(puzzle_image.width - (puzzle_image.width/divisor*divisor))};
    int hheight {(puzzle_image.height - (puzzle_image.height/divisor*divisor))};
    SetWindowSize(puzzle_image.width - wwidth, puzzle_image.height - hheight);

}


void reset_puzzle(puzzle_game::puzzle& puzzle,int divisor_add=0){
    puzzle.increase_divisor(divisor_add);
    setup_window(*puzzle.img,puzzle.current_divisor);
    puzzle.reset();
}



void conform_image(Image& image){
    //awk to read
    const int USER_MONITOR_HEIGHT = GetMonitorHeight(GetCurrentMonitor());
    const int USER_MONITOR_WIDTH = GetMonitorWidth(GetCurrentMonitor());
    while(image.height >= USER_MONITOR_HEIGHT-puzzle_game::constants::FORCED_FREE_SPACE_ON_MONITOR or
     image.width >= USER_MONITOR_WIDTH-puzzle_game::constants::FORCED_FREE_SPACE_ON_MONITOR) {
        ImageResize(&image,image.width*0.90,image.height*0.90);
    }

}


void handle_global_keypresses(puzzle_game::puzzle& puzzle){
    //restart, increase division
    if(IsKeyReleased(KEY_F4)){
        reset_puzzle(puzzle,2);
    }
    //restart, keep division
    if(IsKeyReleased(KEY_SPACE)){
        puzzle.shuffle();
    }
    
}


//pbv intentional for copy
void set_window_icon(Image image){

    ImageResize(&image,256,256);
    SetWindowIcon(image);

}


Image get_image(const char* image_path){
    return LoadImage(image_path);
}


int main(int argc, [[maybe_unused]]char* argv[]){
    assert(argc > 1 && "You have to drag and drop an image into the executable directly!");

    InitWindow(800,800,argv[1]);
    SetTargetFPS(144);


    Image puzzle_image{get_image(argv[1])};
    
    conform_image(puzzle_image);
    setup_window(puzzle_image);
    //dont know why i have to make a copy when i pbv..?
    set_window_icon(ImageCopy(puzzle_image));

    puzzle_game::puzzle puzzle{&puzzle_image};
    puzzle.init();





    
    


    while (!WindowShouldClose()){
        handle_global_keypresses(puzzle);
        BeginDrawing();
        puzzle.draw();
        puzzle.update();
        ClearBackground(GRAY);
        EndDrawing();
    }
    CloseWindow();
	return 0;
}