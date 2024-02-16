#include "include/puzzle.h"
#include "include/puzzle_piece.h"
#include <algorithm>
#include <raylib.h>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <raymath.h>
#include "include/constants.h"
#include <cmath>
#include "include/util.h"
#include <format>
#include <cassert>


//functions for grabbing piece pointers based on location
puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_piece_above(const puzzle_piece* piece){
    return ptr_piece_at(current_order_of_pieces,Vector2{piece->pos.x,piece->pos.y-piece->bounding_box.height});
}

puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_piece_below(const puzzle_piece* piece){
    return ptr_piece_at(current_order_of_pieces,Vector2{piece->pos.x,piece->pos.y+piece->bounding_box.height});
}

puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_piece_left(const puzzle_piece* piece){
    return ptr_piece_at(current_order_of_pieces,Vector2{piece->pos.x-piece->bounding_box.width,piece->pos.y});
}

puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_piece_right(const puzzle_piece* piece){
    return ptr_piece_at(current_order_of_pieces,Vector2{piece->pos.x+piece->bounding_box.width,piece->pos.y});
}


//function for grabbing a piece pointer
puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_piece_at(std::vector<puzzle_piece>& list,const Vector2& pos){
    for(auto& p : list){
        if(p.pos.x == pos.x and p.pos.y == pos.y){
            return &p;
        }
    }
    return nullptr;
}

//function for gettting all the neighbours of the last piece
//this *can* return nullptrs
std::vector<puzzle_game::puzzle_piece*> puzzle_game::puzzle::neighbours_of_last_piece(){
    std::vector<puzzle_piece*> neighbours {
        ptr_piece_above(ptr_last_piece),
        ptr_piece_below(ptr_last_piece),
        ptr_piece_right(ptr_last_piece),
        ptr_piece_left(ptr_last_piece),
    };
    return neighbours;
}

//checks if the current puzzle state contains the last piece
bool puzzle_game::puzzle::is_filled_in_after_completion(){
    return (std::find(current_order_of_pieces.begin(),current_order_of_pieces.end(),*ptr_last_piece) != current_order_of_pieces.end());
}

void puzzle_game::puzzle::handle_mouse_clicks(const Vector2& mouse_pos){

    //not clicked, return
    if(!IsMouseButtonPressed(0)) return;

    //loop through pieces
    for(auto& p : current_order_of_pieces){
        //if a piece was clicked...
        if(CheckCollisionPointRec(mouse_pos,p.bounding_box)){
            //search neighbours of the empty piece (the last piece)
            for(auto &ptr : neighbours_of_last_piece()){
                //if the piece clicked is a neighbour of the empty slot
                //it can be moved there
                if(ptr == &p){
                    //swap the empty slot and the piece
                    p.swap(ptr_last_piece);

                    //check if the puzzle is solved, if it is, fill in the last piece
                    if(this->is_solved() && (!(this->is_filled_in_after_completion()))) {

                        //add in the last piece into its original index, so the order doesnt get messed up for
                        //later solve checks.
                        current_order_of_pieces.insert(current_order_of_pieces.begin()+indx_last_piece,*ptr_last_piece);

                        
                    }
                }
            }
        }
    }
}


//Draw a white border over pieces the player is hovering over
void puzzle_game::puzzle::handle_mouse_hover(const Vector2& mouse_pos){
    for(auto& p : current_order_of_pieces){
        if(CheckCollisionPointRec(mouse_pos,p.bounding_box)){
            Rectangle outline = {p.pos.x,p.pos.y,static_cast<float>(p.img.width),static_cast<float>(p.img.height)};
            DrawRectangleLinesEx(outline,puzzle_game::constants::PUZZLE_PIECE_BORDER_THICKNESS,WHITE);
        }
    }

}

bool puzzle_game::puzzle::is_solved(){

    //if the current puzzle state is all the way filled in, it is solved. return early
    if(is_filled_in_after_completion()) return true;

    //compare_offset is used to jump comparison ahead so last piece in correct list
    //isnt compared with anything in current list
    int compare_offset {0};


    std::cout << "COMPARE PIECES \n";
    for(int i = 0; i < current_order_of_pieces.size(); ++i){

        //console logging
        std::cerr << "i = (" << i << ") compare_offset = (" << compare_offset << ")\n";
        {
            std::string message_current {std::format("POS X:({0}) Y:({1})",current_order_of_pieces[i].pos.x,current_order_of_pieces[i].pos.y)};
            std::string message_correct {std::format("POS X:({0}) Y:({1})",correct_order_of_pieces[compare_offset].pos.x,correct_order_of_pieces[compare_offset].pos.y)};

            std::cerr << "current order (" << i << ") " << message_current << " correct order (" << compare_offset << ") "<< message_correct<< "\n";
        }

        //if the current index is the last piece pointer, 
        //increment the compare offset so we dont compare it to anything in the current order.
        if(correct_order_of_pieces[i] == *ptr_last_piece) {

            compare_offset++;

            //without offset (wooffset) with offset (woffset)
            std::string message_correct_wooffset {std::format("POS X:({0}) Y:({1})",correct_order_of_pieces[i].pos.x,correct_order_of_pieces[i].pos.y)};
            std::string message_correct_woffset {std::format("POS X:({0}) Y:({1})",correct_order_of_pieces[compare_offset].pos.x,correct_order_of_pieces[compare_offset].pos.y)};

            std::cerr << "found correct piece - offset corrected (" << compare_offset << ")." << '\n';
            std::cerr << "Correct piece is " << message_correct_wooffset << '\n';
            std::cerr << "Next comparison rhs should be " << message_correct_woffset << '\n';
        }

        //if the index at the current order doesnt compare to the index (compare offset) of the correct order, the puzzle isnt solved.
        if(current_order_of_pieces[i] != correct_order_of_pieces[compare_offset]) {
            std::cerr << "inequal - ";
            std::string message_current {std::format("POS X:({0}) Y:({1})",current_order_of_pieces[i].pos.x,current_order_of_pieces[i].pos.y)};
            std::string message_correct {std::format("POS X:({0}) Y:({1})",correct_order_of_pieces[compare_offset].pos.x,correct_order_of_pieces[compare_offset].pos.y)};
            std::cerr << "current order (" << i << ") " << message_current << " correct order (" << compare_offset << ") "<< message_correct<< "\n";
            std::cerr << "Not solved. \n";
            return false;
        }

        //increment the correct-order-of-pieces comparison offset to keep up with 'i'
        compare_offset++;

    } 
    //if we got here, then the puzzle is solved. 
    std::cerr << "Solved! \n";
    return true;
}



void puzzle_game::puzzle::update(){

    //dont run any of this code if the puzzle is completed
    if(is_filled_in_after_completion()) return;

    handle_mouse_hover(GetMousePosition());
    handle_mouse_clicks(GetMousePosition());
}


void puzzle_game::puzzle::draw(){


    for(auto& p : current_order_of_pieces){
        DrawTexture(p.img,p.pos.x,p.pos.y,WHITE);

        //if the puzzle isnt solved, draw a soft border around each piece
        if(!is_filled_in_after_completion()){
            DrawRectangleLinesEx(Rectangle{p.pos.x,p.pos.y,static_cast<float>(p.img.width),static_cast<float>(p.img.height)},puzzle_game::constants::PUZZLE_PIECE_BORDER_THICKNESS,BLACK);
        }
    }

    //if the user if holding control show them the image they are tryin to piece together
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        DrawTexture(modif_img_as_texture,0,0,WHITE);
    }

}

//I havent used this function yet, dont think I will, but no harm in leaving it commented out for now
// std::vector<puzzle_game::puzzle_piece>& puzzle_game::puzzle::get_pieces(){
//     return current_order_of_pieces;
// }


//used to scramble puzzle
puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_rand_neighbour_of_last_piece(){
    puzzle_piece* choice = nullptr;
    while(choice == nullptr){
        choice = neighbours_of_last_piece()[rand()%4];
    }
    return choice;
}


void puzzle_game::puzzle::shuffle(){
    auto& pieces = current_order_of_pieces;


    //if there is no pointer to the last piece, or the puzzle is solved, we need to
    //define the last piece and then remove it from the current puzzle state
    if( (!ptr_last_piece) || (this->is_solved())){
        //get a random index from the pieces for the removed/last piece to be
        int chosen_hidden_piece_index = rand() % pieces.size();
        //set the pointer to the piece's address then save the index for when
        //it will be re-inserted into the current puzzle state after it is solved
        ptr_last_piece = &correct_order_of_pieces[chosen_hidden_piece_index];
        indx_last_piece = chosen_hidden_piece_index;
        //erase that chosen piece from the current state
        pieces.erase(pieces.begin()+chosen_hidden_piece_index);

        //there should only be *ONE* piece erased from the current order vector.
        //there is NO REASON THIS SHOULD EVER FAIL.
        assert( (correct_order_of_pieces.size() - current_order_of_pieces.size()) == 1);

    }


    //pick a random neighbour of the last piece, then swap them.
    //if the puzzle somehow solves itself in this process, do it again
    auto size = pieces.size();
    auto do_shuffle = [this,&size](puzzle_piece* last_piece){

        auto shuffle = [this,&size](puzzle_piece* last_piece) -> bool{
            for(int i = 0; i < static_cast<int>(size*size); ++i){
                last_piece->swap(this->ptr_rand_neighbour_of_last_piece());
            }

            return this->is_solved();
        };

        //shuffle returns false if the puzzle is solved after shuffling
        //so we do it over and over until it returns true
        while(shuffle(last_piece)){
            shuffle(last_piece);
        }
    };

    //call the shuffle func
    do_shuffle(ptr_last_piece);


}


void puzzle_game::puzzle::set_image(Image* image,std::string file_path_for_title){


    //Set the title to give the user some feedback while it loads
    //(Is set back from main.cpp->update_window_title)
    puzzle_game::util::set_window_title("Loading image...");

    //If the puzzle already has an image, unload it, and the modified one aswell
    if(has_image) {
        UnloadImage(img);
        UnloadImage(modif_img);
        UnloadTexture(modif_img_as_texture);
    }

    //save the file path in a string for the title bar
    this->file_path_for_title = file_path_for_title;

    //set has_image to true, so next time an image is loaded the previous one will be unloaded
    has_image = true;

    //make a copy of the image, after the end of this scope the image passed to this argument is unloaded.
    img = ImageCopy(*image);

    //modify the image, conforming it to a reasonable size
    modif_img = util::conform_image(&img);

    //set the window size to be roughly what it should be after rounding is considered
    puzzle_game::util::setup_window(&modif_img,current_divisor);

    //Load the original image as a texture so the player can look at the original image for referencing their progress
    //This wont count for the slight precision loss like the pieces(?) but it should be good enough and not noticeable (I hope?)
    modif_img_as_texture = LoadTextureFromImage(modif_img);

    //I plan on getting around to creating a simple icon for the window instead, because I dont like this
    //puzzle_game::util::set_window_icon(ImageCopy(*image));

    //Reset the puzzle
    reset();









}

void puzzle_game::puzzle::init(){

    //fill the puzzle pieces up
    fill_list_with_pieces(correct_order_of_pieces);

    //copy the correct order to the current order
    current_order_of_pieces = correct_order_of_pieces;
    
    //shuffle the puzzle
    this->shuffle();

}

void puzzle_game::puzzle::reset(){

    //set the last piece ptr to null
    ptr_last_piece = nullptr;


    //Unload all images associated with pieces
    //(I tried to do this in a RAII way but
    //failed horribly. I have no clue how image loading
    //and unloading works behind the scenes, but I dont get it.)
    for(auto& p : correct_order_of_pieces){
        UnloadTexture(p.img);
    }
    for(auto& p : current_order_of_pieces){
        UnloadTexture(p.img);
    }

    //clear out both lists of pieces
    current_order_of_pieces.clear();
    correct_order_of_pieces.clear();

    //initialiase the puzzle again
    this->init();
}


//Divides modif_img into individual pieces based on the current_divisor
void puzzle_game::puzzle::fill_list_with_pieces(std::vector<puzzle_game::puzzle_piece>& list){

    int& divisor {current_divisor};

    //Reserve space in the list for emplacing
    list.reserve(static_cast<size_t>(current_divisor*current_divisor));


    //Divide the image into individual puzzle pieces
    for(int y = 0; y < divisor; ++y){
        for(int x = 0; x < divisor; ++x){

            //the distance between each puzzle piece crop (this narrows to integer)
            Vector2 dist {static_cast<float>(modif_img.width/divisor),static_cast<float>(modif_img.height/divisor)};

            //the position of the crop
            Vector2 pos  {x*dist.x,y*dist.y};

            //the width and height of the crop (this narrows to integer)
            Vector2 dimensions  {static_cast<float>(modif_img.width/divisor),static_cast<float>(modif_img.height/divisor)};

            //the cropped image to be loaded into the puzzle piece
            Image cropped_img {ImageFromImage(modif_img,Rectangle{pos.x,pos.y,dimensions.x,dimensions.y})};

            //above, but as a texture.
            Texture2D puzzle_piece_img {LoadTextureFromImage(cropped_img)};

            //Unload the cropped image since it is no longer needed
            UnloadImage(cropped_img);
            
            //add the piece to the list
            list.emplace_back(pos,puzzle_piece_img,Rectangle{pos.x,pos.y,dimensions.x,dimensions.y});
            


        }
    }


}

void puzzle_game::puzzle::increase_divisor(int add){
    current_divisor += add;
    if(current_divisor > MAX_DIVISOR) current_divisor = MIN_DIVISOR;

    //increasing the division will probably cause more floating point imprecision,
    //so set up the window again just in case
    puzzle_game::util::setup_window(&modif_img,current_divisor);

    //reset the puzzle so the division increase can be seen
    reset();
}

puzzle_game::puzzle::puzzle(){

}
