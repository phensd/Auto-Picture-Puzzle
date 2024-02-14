#pragma once
#include <raylib.h>
#include <utility>

namespace puzzle_game {
    struct puzzle_piece{

        public:
            Vector2 pos;
            Texture2D img;
            Rectangle bounding_box;



            void move(Vector2& pos);
            void swap(puzzle_piece* with);
            bool operator ==(const puzzle_piece& p);
            bool operator !=(const puzzle_piece& p);

            puzzle_piece(Vector2 pos, Texture2D img,Rectangle bounding_box);
            ~puzzle_piece();





    };    
}
