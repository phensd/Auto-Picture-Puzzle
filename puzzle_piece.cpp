#include <raylib.h>
#include "include/puzzle_piece.h"
#include <raymath.h>
#include <iostream>


void puzzle_game::puzzle_piece::move(Vector2& pos){
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    
    this->bounding_box.x = pos.x;
    this->bounding_box.y = pos.y;
}

//swap positions of two pieces
void puzzle_game::puzzle_piece::swap(puzzle_piece* with){
    auto temp_pos = with->pos;

    with->move(pos);
    this->move(temp_pos);


}

puzzle_game::puzzle_piece::~puzzle_piece(){
    static int deleted{0};
    std::cerr << "Deleted puzzle piece #" << deleted++ <<'\n';
}

puzzle_game::puzzle_piece::puzzle_piece(Vector2 pos, Texture2D img,Rectangle bounding_box) :
    pos{pos},
    img{img},
    bounding_box{bounding_box}
    {}


//Pieces are equal if there positions are equal
bool puzzle_game::puzzle_piece::operator==(const puzzle_piece& p){
    return Vector2Equals(this->pos,p.pos);
}

bool puzzle_game::puzzle_piece::operator!=(const puzzle_piece& p){
    return !(puzzle_piece::operator==(p));
}
