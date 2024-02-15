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


void handle_image_change(puzzle_game::puzzle& puzzle, FilePathList* files=nullptr, const char* from_path=nullptr){

    Image image;
    std::string file_path_for_title;

    //if called with a direct path to the file,
    //try to load the image from there.
    if(from_path){
        image = LoadImage(from_path);
        //pass the file title over to be used for the window title
        file_path_for_title = from_path;

    //if a file path list was passed
    //(i.e called from a dragg-and-drop)
    //try to load it from a drag-and-dropped file.
    }else if(files){
        image = LoadImage(files->paths[0]);
        //pass the file title over to be used for the window title
        file_path_for_title = files->paths[0];
    }

    //if the image has data (i.e, it was loaded successfully)
    //set it as the puzzle's image then unload it after
    if(image.data) {
        puzzle.set_image(&image,file_path_for_title);
        UnloadImage(image);
    }
}


void update_window_title(puzzle_game::puzzle* puzzle){
     //Set the window title to be the file name of the image loaded,
    //and some info on key bindings if the puzzle is not completed
    if(!puzzle->is_filled_in_after_completion()){
        puzzle_game::util::set_window_title(puzzle->image_file_path_get(),true);
    }else{
        puzzle_game::util::set_window_title("Puzzle Solved!");

    }
}

int main(int argc, [[maybe_unused]]char* argv[]){

    std::string middle_message{"Drag and drop and image here to start!"};

    InitWindow(800,800,"[Auto Picture Puzzle]");
    SetTargetFPS(144);

    puzzle_game::puzzle puzzle{};


    //if there was an arg passed, try to load it as an image.
    //if it loads successfully, set it as the puzzle's image.
    if(argc > 1){
        handle_image_change(puzzle,nullptr,argv[1]);
    }
    


    
    


    while (!WindowShouldClose()){

        //if a file is dropped, load the files,
        //pass it into handle_image_change,
        //then unload the files
        if(IsFileDropped()) {
            auto files {LoadDroppedFiles()};
            handle_image_change(puzzle,&files);
            UnloadDroppedFiles(files);
        }


        BeginDrawing();

        //update and draw the puzzle if it has an image
        if(puzzle.has_an_image()){
            handle_global_keypresses(puzzle);
            puzzle.draw();
            puzzle.update();
            update_window_title(&puzzle);
            //Gray is less common for what I assume people would use this for
            //so we clear with gray here, but
            ClearBackground(GRAY);

        //otherwise draw a message in the middle of the screen
        //telling the user to drop an image into the window
        }else {
            DrawText(middle_message.c_str(),30,335,38,BLACK);
            //white here because its better for the text.
            ClearBackground(WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
	return 0;
}
