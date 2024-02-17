#pragma once
#include "puzzle_piece.h"
#include <raylib.h>
#include <vector>
#include <string>

namespace puzzle_game {
    class puzzle{


        public:
            Image img;
            Image modif_img;
            Texture modif_img_as_texture;
            // std::vector<puzzle_piece>& get_pieces();
            
            void init();
            void set_image(Image* image, std::string file_path_for_title);
            void reset();
            void update();
            void draw();
            void increase_divisor(int add);
            int current_divisor{4};
            void shuffle();

            bool has_an_image() {return has_image;}
            std::string& image_file_path_get() {return file_path_for_title;}
            bool is_filled_in_after_completion();


            
            puzzle(const puzzle&) = delete;
            puzzle& operator=(const puzzle&) = delete;
            puzzle();

        private:
            const int MIN_DIVISOR{4};
            const int MAX_DIVISOR{10};
            puzzle_piece* ptr_last_piece{nullptr};
            int indx_last_piece;

            puzzle_piece* ptr_piece_at(std::vector<puzzle_piece>& list,const Vector2& pos);

            puzzle_piece* ptr_piece_below(const puzzle_piece* piece);
            puzzle_piece* ptr_piece_above(const puzzle_piece* piece);
            puzzle_piece* ptr_piece_left(const puzzle_piece* piece);
            puzzle_piece* ptr_piece_right(const puzzle_piece* piece);

            std::vector<puzzle_piece*> neighbours_of_last_piece();
            puzzle_piece* ptr_rand_neighbour_of_last_piece();

            bool is_solved();
            bool has_image {false};
            void handle_mouse_hover(const Vector2& mouse_pos);
            void handle_mouse_clicks(const Vector2& mouse_pos);

            std::string file_path_for_title;

            std::vector<puzzle_piece> correct_order_of_pieces{};
            std::vector<puzzle_piece> current_order_of_pieces{};
            void fill_list_with_pieces(std::vector<puzzle_piece>& list);
    };

}
