/*
ChessBoard board                - board being used for this game, will be expanded in the future for more games
SDL_Window* win                 - SDL window
SDL_Renderer* render            - SDL render
SDL_Event e                     - SDL event
int win_x_size, win_y_size      - sizes of SDL window
bool running                    - flag for ending the game and closing the window
SDL_Surface* tmp_load_surface   - temporary surface for loading pictures
SDL_Texture* images[12]         - textures for storing the pictures
bool hold                       - for remembering if there is a Piece held to be moved on the Chessboard
SDL_Rect square[8][8]           - squares to be rendered to SDL render 
Piece** from                    - pointer to the piece which is going to be moved
Piece** to                      - pointer to the Piece/square to be moved to

SDL_Texture* load_picture_to_texture            - loads picture to SDL texture
void load_pngs()                                - load all the pictures
void update_window()                            - update window render and window
Piece** assign_click_to_square_coordinates()    - find a Piece based on where the cursor clicked
void make_move(Piece** from, Piece** to)        - change the position of pieces on the board if possible

int run()                       - the main game loop

*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Chessboard.h"
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"
#include "Ai.h"


class Game {
  private:
    SDL_Window* win;
    SDL_Renderer* render;
    SDL_Rect square[8][8];
    SDL_Event e, ch;
    SDL_Surface* tmp_load_surface;
    SDL_Texture* images[12];
    int win_x_size, win_y_size;

    bool running;
    bool hold;
    Piece** from;
    Piece** to;

    ChessBoard* board;
    AI* ai;
    string who_starts;
    set<pair<int, int>> from_moves;
    bool is_a_tutorial;



    void saving();
    void loading();
    void kill_SDL2();
    void play_as(bool& menu1, bool& menu2, bool& menu3);
    void difficulty(bool& menu1, bool& menu2);
    void game_type(bool& menu1);
    bool menu();
    void tutorial(bool& menu1);

    bool modify_coordinates(Piece** target, int& t_x, int& t_y);
    SDL_Texture* load_picture_to_texture(const char* filename);
    void load_pngs();
    void update_window();
    Piece** assign_click_to_square_coordinates();

    bool check();

  public:
    Game();
    ~Game();
    int run();

};
