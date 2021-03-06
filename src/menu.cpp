#include "menu.hpp"
#include "color.hpp"
#include "game.hpp"
#include "scores.hpp"
#include <iostream>
#include <sstream>

void Menu::startMenu(int err) {
  constexpr auto greetings_text = "Welcome to ";
  constexpr auto gamename_text = "2048!";
  constexpr auto sp = "  ";

  std::ostringstream str_os;
  std::ostringstream title_richtext;
  title_richtext << bold_on << sp << greetings_text << blue << gamename_text
                 << def << bold_off << "\n";

  constexpr auto menu_entry_text = R"(
          1. Play a New Game
          2. Continue Previous Game
          3. View Highscores and Statistics
          4. Exit

)";

  clearScreen();
  drawAscii();
  str_os << title_richtext.str();
  str_os << menu_entry_text;
  std::cout << str_os.str();
  input(err);
}

void Menu::input(int err) {
  constexpr auto err_input_text = "Invalid input. Please try again.";
  constexpr auto prompt_choice_text = "Enter Choice: ";
  constexpr auto sp = "  ";

  std::ostringstream str_os;
  std::ostringstream err_input_richtext;
  err_input_richtext << red << sp << err_input_text << def << "\n\n";
  std::ostringstream prompt_choice_richtext;
  prompt_choice_richtext << sp << prompt_choice_text;

  if (err) {
    str_os << err_input_richtext.str();
  }

  str_os << prompt_choice_richtext.str();
  std::cout << str_os.str();
  char c;
  std::cin >> c;

  if (std::cin.eof()) {
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
  }

  switch (c) {
  case '1':
    startGame();
    break;
  case '2':
    continueGame();
    break;
  case '3':
    showScores();
    break;
  case '4':
    exit(EXIT_SUCCESS);
  default:
    startMenu(1);
    break;
  }
}

void Menu::startGame() {

  Game g;
  g.startGame();
}

void Menu::continueGame() {
  Game g;
  g.continueGame();
}

void Menu::showScores() {
  int boardsize = 0;

  std::ostringstream error_prompt_richtext;
  std::ostringstream str_os;
  std::ostringstream board_size_prompt_richtext;

    constexpr auto choose_playsize = "Enter the size of board (3 to 10). If you want to go back, enter '0': ";
    const auto invalid_prompt_text ={
      "Invalid input. Gameboard size should range from ", " to ", "."};
    error_prompt_richtext << red << std::begin(invalid_prompt_text)[0]
                            << 3
                            << std::begin(invalid_prompt_text)[1]
                            << 10
                            << std::begin(invalid_prompt_text)[2] << def << "\n\n";
    board_size_prompt_richtext << bold_on << " " << choose_playsize<< bold_off;


 bool err = false;
  while(boardsize < 3 || boardsize > 10){
    clearScreen();
    drawAscii();
    if(err)
      str_os << error_prompt_richtext.str();
    str_os << board_size_prompt_richtext.str();
    std::cout << str_os.str();
    std::cin >> boardsize;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::int32_t>::max(), '\n');
    err = true;
    if(boardsize==0){
      Menu menu;
      menu.startMenu();
    }
  }
  Scoreboard s;
  s.printScore(boardsize);
  s.printStats(boardsize);
}

void drawAscii() {
  constexpr auto title_card_2048 = R"(
   /\\\\\\\\\          /\\\\\\\                /\\\         /\\\\\\\\\
  /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\
  \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\
             /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/
           /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\
         /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\
        /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      /\\\
        /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\/
        \///////////////      \///////                \///         \/////////
  )";
  std::ostringstream title_card_richtext;
  title_card_richtext << green << bold_on << title_card_2048 << bold_off << def;
  title_card_richtext << "\n\n\n";
  std::cout << title_card_richtext.str();
}
