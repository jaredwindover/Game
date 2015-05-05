#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include <string>

#include "Terrain.h"
#include "Background.h"
#include "Player.h"

class Game{
private:
  sf::RenderWindow window;
  sf::View camera_view;
  Background background1;
  Background background2;
  Terrain asteroid;
  Player player;
  float framerate;
  sf::Color background_color;
  sf::Font debug_font;
#ifdef DEBUG
  sf::View debug_view;
#endif
  bool in_left;
  bool in_right;
  bool in_left_rotate;
  bool in_right_rotate;
  bool in_up;
  bool in_down;
  bool in_move_left;
  bool in_move_right;
  bool in_jump;
  bool in_quit;
  bool in_pause;
  bool s_paused;
  bool s_running;

  void moveCamera(int,int);
  void rotateCamera(int);
  void updateCamera();
protected:
public:
  Game();
  ~Game();
  void run();
  void update(sf::Time);
  void pauseUpdate();
  void updateCircle();
  void render();
  void processEvents();
  void handleKeyboard(sf::Keyboard::Key, bool);
};

#endif
