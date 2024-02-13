#include <iostream>
#include <raylib.h>
#include "include/constants.h"
#include <cassert>
#include <vector>
#include "include/puzzle.h"
#include <sstream>
#include "include/util.h"






void handle_global_keypresses(puzzle_game::puzzle& puzzle){
    //restart, increase division
    if(IsKeyReleased(KEY_F4)){
        puzzle.increase_divisor(2);
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
        puzzle.set_image(&image,files.paths[0]);
        UnloadImage(image);
    }catch(std::exception& e){
        e.what();
    }

    UnloadDroppedFiles(files);

}

int main(int argc, [[maybe_unused]]char* argv[]){

    InitWindow(800,800,"[Auto Picture Puzzle]");
    SetTargetFPS(144);

    puzzle_game::puzzle puzzle{};


    if(argc > 1){
        Image image {LoadImage(argv[1])};
        puzzle.set_image(&image,argv[1]);
        UnloadImage(image);
    }
    


    
    


    while (!WindowShouldClose()){
        if(IsFileDropped()) handle_image_drop(puzzle);

        BeginDrawing();
        if(puzzle.has_an_image()){

            handle_global_keypresses(puzzle);
            puzzle.draw();
            puzzle.update();
            //Gray is less common for what I assume people would use this for
            //so we clear with gray here, but
            ClearBackground(GRAY);
        }else {
            DrawText("Drag and drop and image here to start!",30,330,38,BLACK);
            //white here because its better for the text.
            ClearBackground(WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
	return 0;
}
