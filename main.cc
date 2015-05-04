 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

void usage(std::string);

int main(int argc, char**argv) {
  Game game;
  game.run();
  return 0;
}

void usage(std::string message){
  std::cout << message << std::endl << std::flush;
}
