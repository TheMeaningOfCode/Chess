#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <fstream>

#include "Game.h"
#include "Chessboard.h"
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"

void Game::kill_SDL2() {
  for (int i = 0; i < 12; i++) {
    SDL_DestroyTexture(images[i]);
  }
  IMG_Quit();
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

bool Game::modify_coordinates(Piece** target, int& t_x, int& t_y) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (&(board->m_square[i][j]) == target) {
        t_x = i;
        t_y = j;
        return true;
      }
    }
  }
  return false;
}

SDL_Texture* Game::load_picture_to_texture(const char* filename) {
  SDL_Texture* temp;

  tmp_load_surface = IMG_Load(filename);
  if (!tmp_load_surface) cout << filename << " not loaded" << endl;
  temp = SDL_CreateTextureFromSurface(render, tmp_load_surface);
  SDL_RenderClear(render);
  SDL_FreeSurface(tmp_load_surface);

  return temp;
}

void Game::load_pngs() {

  if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
    cout << IMG_GetError() << endl;
  }

  images[0] = load_picture_to_texture("Assets/White_Rook.png");
  images[1] = load_picture_to_texture("Assets/White_Knight.png");
  images[2] = load_picture_to_texture("Assets/White_Bishop.png");
  images[3] = load_picture_to_texture("Assets/White_Queen.png");
  images[4] = load_picture_to_texture("Assets/White_King.png");
  images[5] = load_picture_to_texture("Assets/White_Pawn.png");

  images[6] = load_picture_to_texture("Assets/Black_Rook.png");
  images[7] = load_picture_to_texture("Assets/Black_Knight.png");
  images[8] = load_picture_to_texture("Assets/Black_Bishop.png");
  images[9] = load_picture_to_texture("Assets/Black_King.png");
  images[10] = load_picture_to_texture("Assets/Black_Queen.png");
  images[11] = load_picture_to_texture("Assets/Black_Pawn.png");

}

void Game::update_window() {
  SDL_GetWindowSize(win, &win_x_size, &win_y_size);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      square[i][j].h = min(win_x_size, win_y_size)/8;
      square[i][j].w = square[i][j].h;    //square

      if (win_x_size >= win_y_size) {
        square[i][j].x = (max(win_x_size, win_y_size)-min(win_x_size, win_y_size))/2 + j*(min(win_x_size, win_y_size)/8);
        square[i][j].y = i*(min(win_x_size, win_y_size)/8);
      }
      else if (win_x_size < win_y_size) {
        square[j][i].y = (max(win_x_size, win_y_size)-min(win_x_size, win_y_size))/2 + j*(min(win_x_size, win_y_size)/8);
        square[j][i].x = i*(min(win_x_size, win_y_size)/8);
      }

      if (from_moves.find(pair<int, int>(j, 7-i)) != from_moves.end()) {
        SDL_SetRenderDrawColor(render, 0x33, 0x99, 0xFF, 0xFF);
      }
      else if ((i+j)%2 == 1) {
        SDL_SetRenderDrawColor(render, 0x30, 0x30, 0x30, 0xFF);
      }
      else if ((i+j)%2 == 0){
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
      }

      SDL_RenderFillRect(render, &square[i][j]);
      if (board->occupied(pair<int, int>(j, 7-i))) {
        if (board->picture_name(j, 7-i) == "White_Rook") {
          if (SDL_RenderCopy(render, images[0], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "White_Knight") {
          if (SDL_RenderCopy(render, images[1], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "White_Bishop") {
          if (SDL_RenderCopy(render, images[2], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "White_Queen") {
          if (SDL_RenderCopy(render, images[3], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "White_King") {
          if (SDL_RenderCopy(render, images[4], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "White_Pawn") {
          if (SDL_RenderCopy(render, images[5], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "Black_Rook") {
          if (SDL_RenderCopy(render, images[6], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "Black_Knight") {
          if (SDL_RenderCopy(render, images[7], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "Black_Bishop") {
          if (SDL_RenderCopy(render, images[8], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "Black_King") {
          if (SDL_RenderCopy(render, images[9], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "Black_Queen") {
          if (SDL_RenderCopy(render, images[10], NULL, &square[i][j]) < 0) cout << "Error";
        }
        if (board->picture_name(j, 7-i) == "Black_Pawn") {
          if (SDL_RenderCopy(render, images[11], NULL, &square[i][j]) < 0) cout << "Error";
        }
      }
    }
  }

  SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 255);
  SDL_RenderPresent(render);
  SDL_UpdateWindowSurface(win);
  SDL_RenderClear(render);
}

//returns pointer to Piece*
Piece** Game::assign_click_to_square_coordinates() {
  int x, y, a, b;
  SDL_GetWindowSize(win, &a , &b);
  SDL_GetMouseState(&x, &y);

  //find the left upper point of the chessboard

  if (a >= b) {
    a = (a-b)/2;
  }
  else if (a < b) {
    b = (b-a)/2;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (win_x_size  >= win_y_size) {
        if (((a+j*(b/8))<=x) && ((a+j*(b/8)+(b/8))>x) && ((i*(b/8))<=y) && ((i*(b/8)+(b/8))>y)) {
          return &(board->m_square[j][7-i]);
        }
      }
      else if (win_x_size < win_y_size) {
        if (((j*(a/8))<=x) && ((j*(a/8)+(a/8))>x) && ((b+i*(a/8))<=y) && (b+i*(a/8)+(a/8)>y)) {
          return &(board->m_square[j][7-i]);
        }
            
      }
    }
  }
  
  cout << "NO CHESSBOARD ON THIS POSITION" << endl;
  return nullptr;
}


Game::Game() {
  win = nullptr;
  render = nullptr;
  tmp_load_surface = nullptr;
  for (int i = 0; i < 12; i++) {
    images[i] = nullptr;
  }
  hold = false;
  win_x_size = 0;
  win_y_size = 0;

  running = true;
  hold = false;

  from = nullptr;
  to = nullptr;

  board = nullptr;
  ai = nullptr;
  who_starts = "White";
  is_a_tutorial = false;
}

Game::~Game() {
  if (ai) delete ai;
  if (board) delete board;
}


void Game::play_as(bool& menu1, bool& menu2, bool& menu3) {
  int input;
  system("clear");
  cout << "Play As\n1 -- White\n2 -- Black\n3 -- return"<< endl;
    cin >> input;
    while(cin.fail()) {
      cin.clear();
      cin.ignore(1000000, '\n');
      cin >> input;
    }

  switch (input) {
    case 1:
      menu1 = false;
      menu2 = false;
      menu3 = false;
      break;
    case 2:
      ai->make_move();
      menu1 = false;
      menu2 = false;
      menu3 = false;
      who_starts = "Black";
      break;
    case 3:
      return;
  }
}

void Game::difficulty(bool& menu1, bool& menu2) {
  int input;
  bool menu3 = true;
  while(menu3) {
    system("clear");
    cout << "Select difficulty\n1 -- Easy\n2 -- Medium\n3 -- Hard\n4 -- Return" << endl;
    cin >> input;
    while(cin.fail()) {
      cin.clear();
      cin.ignore(1000000, '\n');
      cin >> input;
    }
    switch (input) {
      case 1:
        ai = new EasyAI(board);
        play_as(menu1, menu2, menu3);
        break;
      case 2:
        ai = new MediumAI(board);
        play_as(menu1, menu2, menu3);
        break;
      case 3:
        ai = new HardAI(board);
        play_as(menu1, menu2, menu3);
        break;
      case 4:
        menu3 = false;
        delete ai;
        ai = nullptr;
        return;
    }
  }
}

void Game::game_type(bool& menu1) {
  int input;
  bool menu2 = true;
  while (menu2) {
    system("clear");
    cout << "Game type\n1 -- 2 Players On 1 Computer \n2 -- Play Against Computer\n3 -- Return"<< endl;
    cin >> input;
    while(cin.fail()) {
      cin.clear();
      cin.ignore(1000000, '\n');
      cin >> input;
    }

    switch (input) {
      case 1:
        menu1 = false;
        menu2 = false;
        break;
      case 2:
        difficulty(menu1, menu2);
        break;
      case 3:
        menu2 = false;
        delete board;
        board = nullptr;
        return;
    }
  }
}


bool Game::menu() {
  int input;
  string text_input;
  bool menu1;
  menu1 = true;

  while (menu1) {
    system("clear");
    cout << "Main Menu\n1 -- New game\n2 -- Load game\n3 -- Tutorial\n4 -- Quit"<< endl;
    
    cin >> input;
    while(cin.fail()) {
      cin.clear();
      cin.ignore(1000000, '\n');
      cin >> input;
    }

    switch (input) {
      case 1:
        board = new ChessBoard();
        game_type(menu1);
        break;
      case 2:
        board = new ChessBoard();
        menu1 = false;
        loading();
        break;
      case 3:
        cout << "Here" << endl;
        tutorial(menu1);
        break;
      case 4:
        system("clear");
        return true;
    }
  }
  return false;
}


void Game::tutorial(bool& menu1) {
  int input;
  bool menu2 = true;
  is_a_tutorial = true;

  while (menu2) {
    system("clear");
    cout << "Select tutorial\n1 -- Queen\n2 -- Bishop, Knight, Rook\n3 -- Castling\n4 -- En_passant and Promotion \n5 -- Return"<< endl;

    cin >> input;
    while(cin.fail()) {
      cin.clear();
      cin.ignore(1000000, '\n');
      cin >> input;
    }

    switch (input) {
      case 1:
        cout << "In this tutorial you can play with the queens. They move vertically horizontally and diagonally" << endl;
        board = new ChessBoard(1);
        menu1 = false;
        menu2 = false;
        break;
      case 2:
        cout << "In this tutorial you can learn how to move Bishops, Knights and Rooks" << endl;
        board = new ChessBoard(2);
        menu1 = false;
        menu2 = false;
        break;
      case 3:
        cout << "Try castling White King by moving 2 spaces to the right. Keep in mind, that none of the places between kings position can be in check" << endl;
        board = new ChessBoard(3);
        menu1 = false;
        menu2 = false;
        break;
      case 4:
        cout << "Can you figure out which Black Pawn moved during the last turn? Dont worry, try taking the square above him. Confifm by pressing \"Z\"" << endl;
        board = new ChessBoard(4);
        board->make_move(pair<int, int>(1,3), pair<int, int>(1,4));
        board->make_move(pair<int, int>(3,3), pair<int, int>(3,4));
        board->make_move(pair<int, int>(5,3), pair<int, int>(5,4));
        board->make_move(pair<int, int>(7,3), pair<int, int>(7,4));
        board->make_move(pair<int, int>(2,6), pair<int, int>(2,4));
        board->make_move(pair<int, int>(4,6), pair<int, int>(4,4));

        menu1 = false;
        menu2 = false;
        break;
      case 5:
        delete board;
        board = nullptr;
        menu2 = false;
        is_a_tutorial = false;
        break;    
    }
  }
}

void Game::loading() {
  string text_input;
  string file;
    
  system("clear");
  cout << "Select Game File:" << endl;

  //print all files
  filesystem::path path = "examples/Saves/";
  for (const auto& f : filesystem::directory_iterator(path)) {
    cout << f.path().filename() << endl;
  }


  ifstream outFile;  

  while (!outFile.is_open()) {
    cin.clear();
    cin.ignore(1000000, '\n');
    cin >> text_input;

    file = "examples/Saves/" + text_input;
    outFile.open(file);
    cout << "File does not exist" << endl;
  }

    string line;

    getline(outFile, line);
    if (line == "None") cout << "None";
    else if (line == "EasyAI") {
      ai = new EasyAI(board);
    } 
    else if (line == "MediumAI") {
      ai = new MediumAI(board);
    } 
    else if (line == "HardAI") {
      ai = new HardAI(board);
    } 


    line.clear();
    getline(outFile, line);

    if (line == "Black") {
      who_starts = "Black";
    }

    int a, b, c, d;

    while (getline(outFile, line)) {
      a = stoi(line.substr(0, 1));
      b = stoi(line.substr(2, 1));
      c = stoi(line.substr(4, 1));
      d = stoi(line.substr(6, 1));

      board->make_move(pair<int, int>(a, b), pair<int, int>(c, d));
    }



  outFile.close();

  return;


}

void Game::saving() {
  system("clear");
  cout << "Save file as:" << endl;

  string input_text;

  cin.clear();
  cin.ignore(1000000, '\n');
  getline(cin, input_text);

  string file = "examples/Saves/" + input_text;

  //delete contents
  ofstream inFile(file, ios::trunc);

  if (!inFile.is_open()) return;

  stringstream s;
  if (ai) {
    s << ai->get_type() << '\n';
  }
  else {
    s << "None" << '\n';
  }
  s << who_starts << '\n';
  
  //input all moves
  while (board->st.size()) {
    s << board->st.front().m_from.first << " " << board->st.front().m_from.second << " " << board->st.front().m_to.first << " " << board->st.front().m_to.second << '\n';
    board->st.pop_front();
  }
  inFile << s.str();
  inFile.close();
}

int Game::run() {

  //main menu
  if (menu()) return 0;
  if (!is_a_tutorial) system("clear");

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL not initialised -> " << SDL_GetError() << endl;
    return -1;
  }

  win = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (!win) {
    cout << "Window not created" << SDL_GetError() << endl;
    SDL_Quit();
    return -1;
  }

  render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); 
  if (!render) cout << "ERROR" << SDL_GetError();

  load_pngs();


  int a, b, c, d;
  bool save = false;

  while (running) {
    while (SDL_PollEvent(&e) ) {
            
      switch (e.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (e.button.button == SDL_BUTTON_LEFT) {
            from = assign_click_to_square_coordinates();
            if (!from) continue;                                              //click outside chessboard
            if (*from == nullptr || (*from)->color != board->turn) continue;  //no piece, or opponent pieces
            modify_coordinates(from, a, b);

            //no legal move for this piece
            if (!board->legal_moves().count(pair<int, int>(a, b))) continue;

            from_moves = board->legal_moves().at(pair<int, int>(a, b));

            hold = true;  //accessed
          }
          break;
        case SDL_MOUSEBUTTONUP:
          if (e.button.button == SDL_BUTTON_LEFT && hold) {
            if (hold) {
              to = assign_click_to_square_coordinates();
              if (!to) {
                hold = false;
                from_moves.clear();
              }
              //now check for legality
              modify_coordinates(to, c, d);
              if (from_moves.find(pair<int, int>(c, d)) != from_moves.end()) {
                board->make_move(pair<int, int>((*from)->x, (*from)->y), pair<int, int>(c, d));
                //promotion took place
                if (board->st.back().promotion) {
                  cout << "Choose a piece\n q -- Queen\n r -- Rook\n b -- Bishop\n k -- Knight\n" << endl;
                  while (true) {
                    SDL_PollEvent(&ch);
                    if (ch.key.keysym.sym == SDLK_q) {
                      board->change_promotion("q");
                      break;
                    }
                    if (ch.key.keysym.sym == SDLK_r) {
                      board->change_promotion("r");
                      break;
                    }
                    if (ch.key.keysym.sym == SDLK_b) {
                      board->change_promotion("b");
                      break;
                    }
                    if (ch.key.keysym.sym == SDLK_k) {
                      board->change_promotion("k");
                      break;
                    }
                  }
                }

                //game status
                check();
                if (board->game_over()) {
                  running = false;
                }

                //AIs turn
                if (ai != nullptr) {
                  if (!ai->make_move()) {
                    if (board->game_over()) {
                      running = false;
                    }
                  }
                }
              }

            }
            hold = false;
            from_moves.clear();
          }
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_z) {
            cout << "UNDO" << endl;
            board->undo_move();
            if (ai != nullptr) {
              // If ai is playing, we want to undo two steps at a time.
              board->undo_move();
            }
          } 
          else if (e.key.keysym.sym == SDLK_q) {
            cout << "Quit" << endl;
            running = false;
          }
          else if (e.key.keysym.sym == SDLK_s) {
            kill_SDL2();
            save = true;
            saving();
            running = false;
          }
      }
            
    }

  if (!save)  update_window();
  if (!save)  SDL_Delay(10);            //reduce CPU usage
  }

  if (!save) kill_SDL2();

  return 0;
}

bool Game::check() {
  bool result;
  board->turn == "White" ? board->turn = "Black" : board->turn = "White";
  result = board->king_in_check();
  if (result) {
    cout << board->turn << " has opponent in check" << endl;
  }
  board->turn == "White" ? board->turn = "Black" : board->turn = "White";
  return result;
}
