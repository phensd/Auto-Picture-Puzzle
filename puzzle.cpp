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




puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_piece_at(std::vector<puzzle_piece>& list,const Vector2& pos){
    for(auto& p : list){
        if(p.pos.x == pos.x and p.pos.y == pos.y){
            return &p;
        }
    }
    return nullptr;
}


bool puzzle_game::puzzle::is_filled_in_after_completion(){
    return std::find(current_order_of_pieces.begin(),current_order_of_pieces.end(),*ptr_last_piece) != current_order_of_pieces.end();
}


//too nested ughhhh
void puzzle_game::puzzle::handle_mouse_clicks(const Vector2& mouse_pos){
    if(!IsMouseButtonPressed(0)) return;
    for(auto& p : current_order_of_pieces){
        if(CheckCollisionPointRec(mouse_pos,p.bounding_box)){
            for(auto &ptr : neighbours_of_last_piece()){
                //if the piece clicked is a neighbour of the empty slot
                //it can be moved there
                if(ptr == &p){
                    p.swap(ptr_last_piece);
                    if(this->is_solved()) current_order_of_pieces.push_back(*ptr_last_piece);
                }
            }
        }
    }
}


void puzzle_game::puzzle::handle_mouse_hover(const Vector2& mouse_pos){
    for(auto& p : current_order_of_pieces){
        if(CheckCollisionPointRec(mouse_pos,p.bounding_box)){
            Rectangle outline = {p.pos.x,p.pos.y,static_cast<float>(p.img.width),static_cast<float>(p.img.height)};
            DrawRectangleLinesEx(outline,puzzle_game::constants::PUZZLE_PIECE_BORDER_THICKNESS,WHITE);
        }
    }

}

bool puzzle_game::puzzle::is_solved(){
    //ocompare is used to jump comparison ahead so last piece in correct list
    //isnt compared with anything in current list
    int ocompare {0};

    for(int i = 0; i < current_order_of_pieces.size(); ++i){
        if(correct_order_of_pieces[ocompare] == *ptr_last_piece) ++ocompare;
        if(!(current_order_of_pieces[i] == correct_order_of_pieces[ocompare])) return false;

        ++ocompare;
    }
    return true;

}



void puzzle_game::puzzle::update(){
    if(is_filled_in_after_completion())return;

    handle_mouse_hover(GetMousePosition());
    handle_mouse_clicks(GetMousePosition());
}


void puzzle_game::puzzle::draw(){

    for(auto& p : current_order_of_pieces){
        DrawTexture(p.img,p.pos.x,p.pos.y,WHITE);

        if(!is_filled_in_after_completion()){
            DrawRectangleLinesEx(Rectangle{p.pos.x,p.pos.y,static_cast<float>(p.img.width),static_cast<float>(p.img.height)},puzzle_game::constants::PUZZLE_PIECE_BORDER_THICKNESS,BLACK);
        }
    }
}

std::vector<puzzle_game::puzzle_piece>& puzzle_game::puzzle::get_pieces(){
    return current_order_of_pieces;
}


std::vector<puzzle_game::puzzle_piece*> puzzle_game::puzzle::neighbours_of_last_piece(){
    std::vector<puzzle_piece*> neighbours {
        ptr_piece_above(ptr_last_piece),
        ptr_piece_below(ptr_last_piece),
        ptr_piece_right(ptr_last_piece),
        ptr_piece_left(ptr_last_piece),
    };


    return neighbours;


}


//usd to scramble puzzle
puzzle_game::puzzle_piece* puzzle_game::puzzle::ptr_rand_neighbour_of_last_piece(){
    puzzle_piece* choice = nullptr;
    while(choice == nullptr){
        choice = neighbours_of_last_piece()[rand()%4];
    }
    return choice;
}


void puzzle_game::puzzle::shuffle(){
    auto& pieces = current_order_of_pieces;


    //define the last piece and then remove it from the current puzzle state
    if(!ptr_last_piece){
        int chosen_hidden_piece_index = rand() % pieces.size();
        ptr_last_piece = &correct_order_of_pieces[chosen_hidden_piece_index];
        pieces.erase(pieces.begin()+chosen_hidden_piece_index);
    }


    auto size = pieces.size();
    for(int i = 0; i < static_cast<int>(size*size); ++i){
      ptr_last_piece->swap(ptr_rand_neighbour_of_last_piece());

    }

}

void puzzle_game::puzzle::set_image(Image image){
    img = &image;
    puzzle_game::util::conform_image(*img);
    puzzle_game::util::setup_window(*img);
    puzzle_game::util::set_window_icon(ImageCopy(*img));

    init();

}

void puzzle_game::puzzle::init(){

    
    fill_list_with_pieces(correct_order_of_pieces);
    current_order_of_pieces = correct_order_of_pieces;
    
    this->shuffle();

}

void puzzle_game::puzzle::reset(){

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

    current_order_of_pieces.clear();
    correct_order_of_pieces.clear();
    this->init();
}


void puzzle_game::puzzle::fill_list_with_pieces(std::vector<puzzle_game::puzzle_piece>& list){
    int& divisor {current_divisor};
    auto& image {*img};
    list.reserve(static_cast<size_t>(current_divisor*current_divisor));


    for(int y = 0; y < divisor; ++y){
        for(int x = 0; x < divisor; ++x){

            Vector2 dist {static_cast<float>(image.width/divisor),static_cast<float>(image.height/divisor)};
            Vector2 pos  {x*dist.x,y*dist.y};
            Vector2 dimensions  {static_cast<float>(image.width/divisor),static_cast<float>(image.height/divisor)};

            Image cropped_img {ImageFromImage(image,Rectangle{pos.x,pos.y,dimensions.x,dimensions.y})};
            Texture2D puzzle_piece_img {LoadTextureFromImage(cropped_img)};
            UnloadImage(cropped_img);
            

            list.emplace_back(pos,puzzle_piece_img,Rectangle{pos.x,pos.y,dimensions.x,dimensions.y});
            


        }
    }

}

void puzzle_game::puzzle::increase_divisor(int add){
    current_divisor += add;
    if(current_divisor > MAX_DIVISOR) current_divisor = MIN_DIVISOR;
}

puzzle_game::puzzle::~puzzle(){
    UnloadImage(*img);
    std::cerr << "puzzle deleted \n";
}
