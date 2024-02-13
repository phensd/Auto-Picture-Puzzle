#include <iostream>
#include <raylib.h>
#include "include/constants.h"
#include <cassert>
#include <vector>
#include "include/puzzle.h"
#include <sstream>
#include "include/util.h"





void reset_puzzle(puzzle_game::puzzle& puzzle,int divisor_add=0){
    puzzle.increase_divisor(divisor_add);
    puzzle_game::util::setup_window(*puzzle.img,puzzle.current_divisor);
    puzzle.reset();
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


Image get_image(const char* image_path){
    return LoadImage(image_path);
}

void handle_image_drop(puzzle_game::puzzle& puzzle){
    auto files {LoadDroppedFiles()};
    try{
        Image image {LoadImage(files.paths[0])};
        puzzle.set_image(image);
    }catch(std::exception& e){

        e.what();
    }

    UnloadDroppedFiles(files);

}

int main(int argc, [[maybe_unused]]char* argv[]){
    assert(argc > 1 && "You have to drag and drop an image into the executable directly!");

    InitWindow(800,800,argv[1]);
    SetTargetFPS(144);


    Image puzzle_image{get_image(argv[1])};
    


    puzzle_game::puzzle puzzle{};

    puzzle.set_image(puzzle_image);





    
    


    while (!WindowShouldClose()){
        if(IsFileDropped()) handle_image_drop(puzzle);

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
