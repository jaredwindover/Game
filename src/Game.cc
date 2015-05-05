#include "Game.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Utility.h"

Game::Game():
  window(sf::VideoMode(800,600),
	 "My window",
	 sf::Style::Close ^
	 sf::Style::Resize ^
	 sf::Style::Titlebar),
  camera_view(sf::FloatRect(0,0,800,600)),
  background1("res/backgrounds/defaultBackgroundA",camera_view),
  background2("res/backgrounds/defaultBackgroundB",camera_view),
  asteroid   ("res/terrain/AsteroidTerrain"),
  player     ("res/players/defaultPlayer"),
  framerate(0),
  background_color(sf::Color::Black),
#ifdef DEBUG
  debug_view(sf::FloatRect(0,0,2560,2560)),
#endif
  in_left            (false),
  in_right           (false),
  in_left_rotate     (false),
  in_right_rotate    (false),
  in_up              (false),
  in_down            (false),
  in_move_left       (false),
  in_move_right      (false),
  in_jump            (false),
  in_quit            (false),
  in_pause           (false),
  s_paused           (false)
{
  player.setTerrain(&asteroid);
  debug_font.loadFromFile("res/fonts/Oxygen-Sans.ttf");
  camera_view.setViewport(sf::FloatRect(0,0,1,1));
#ifdef DEBUG
  debug_view.setViewport(sf::FloatRect(0,0,1,1));
  debug_view.move(-880,-980);
  window.setView(debug_view);
#else
  window.setView(camera_view);
#endif
}

Game::~Game(){
  window.close();
}

void Game::update(sf::Time dt){
  if (in_pause){
    s_paused = true;
    in_pause = false;
  }
  if (in_quit){
    s_running = false;
  }
  if (in_left){
    moveCamera(-10,0);
  }
  if (in_right){
    moveCamera(10,0);
  }
  if (in_up){
    moveCamera(0,-10);
  }
  if (in_down){
    moveCamera(0,10);
  }
  if (in_left_rotate){
    rotateCamera(5);
  }
  if (in_right_rotate){
    rotateCamera(-5);
  }
  if (in_move_right){
    player.move(3);
    player.face(RIGHT);
  }
  if (in_move_left){
    player.move(-3);
    player.face(LEFT);
  }
  background1.update();
  background2.update();
  player.update();
  updateCamera();
}

void Game::updateCamera(){
  camera_view.setCenter(player.getPosition());
  camera_view.setRotation(player.getRotation());
#ifndef DEBUG
  window.setView(camera_view);
#endif
}

void Game::pauseUpdate(){
  if (in_pause){
    s_paused = false;
    in_pause = false;
  }
}

void Game::render(){
  window.clear(background_color);
  window.draw(background1);
  window.draw(background2);
  window.draw(asteroid);
  window.draw(player);
  sf::Text frames;
  frames.setString("Framerate: " + std::to_string((int)framerate));
  frames.setFont(debug_font);
#ifdef DEBUG
  frames.setPosition(debug_view.getCenter());
#else
  frames.setPosition(camera_view.getCenter());
#endif
  window.draw(frames);
  
#ifdef DEBUG
  sf::Vector2f camsize = camera_view.getSize();
  sf::Vector2f campos = camera_view.getCenter();
  sf::RectangleShape camRect(camsize);
  camRect.setOrigin(camsize.x/2,camsize.y/2);
  camRect.setPosition(campos);
  camRect.setRotation(camera_view.getRotation());
  camRect.setOutlineColor(sf::Color::Green);
  camRect.setOutlineThickness(3);
  camRect.setFillColor(sf::Color::Transparent);
  window.draw(camRect);
#endif
  window.display();
}


void Game::run(){
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time loopTime = sf::Time::Zero;
  sf::Time timePerFrame = sf::milliseconds(17);
  std::cout << "Game started" << std::endl;
  s_running = true;
  while (s_running) {
    dbgPrint("Processing Events");
    processEvents();
    loopTime = clock.restart();
    timeSinceLastUpdate += loopTime;
    framerate = 1.0/loopTime.asSeconds();
    if (s_paused) {
      timeSinceLastUpdate = sf::Time::Zero;
      dbgPrint("Paused Update");
      pauseUpdate();
      dbgPrint("Sleep");
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
      while (timeSinceLastUpdate > timePerFrame){
	timeSinceLastUpdate -= timePerFrame;
	dbgPrint("Processing Events");
	processEvents();
	dbgPrint("Update");
	update(timePerFrame);
      }
    }
    dbgPrint("Render");
    render();
  }
  std::cout << "Game finished" << std::endl;
}

void Game::processEvents(){
  sf::Event event;
  while (window.pollEvent(event)){
    switch (event.type) {
    case sf::Event::Closed:
      in_quit = true;
      break;
    case sf::Event::KeyPressed:
      handleKeyboard(event.key.code, true);
      break;
    case sf::Event::KeyReleased:
      handleKeyboard(event.key.code, false);
      break;
    default:
      break;
    }
  }
}



void Game::handleKeyboard(sf::Keyboard::Key k, bool b){
  switch (k){
  case sf::Keyboard::Left:
    in_move_left = b;
    break;
  case sf::Keyboard::Right:
    in_move_right = b;
    break;
  //case sf::Keyboard::Up:
  //  in_up = b;
  //  break;
  //case sf::Keyboard::Down:
  //  in_down = b;
  //  break;
  //case sf::Keyboard::Space:
  //  in_jump = b;
  //  break;
  //case sf::Keyboard::A:
  //  //in_left_rotate = b;
  //  in_move_left = b;
  //  break;
  //case sf::Keyboard::D:
  //  //in_right_rotate = b;
  //  in_move_right = b;
  //  break;
  case sf::Keyboard::P:
    in_pause = b;
    break;
  default:
    break;
  }
}

void Game::moveCamera(int x,int y){
  camera_view.move(x,y);
#ifdef DEBUG
  debug_view.move(x,y);
  window.setView(debug_view);
#else
  window.setView(camera_view);
#endif
}

void Game::rotateCamera(int deg){
  camera_view.rotate(deg);
#ifndef DEBUG
  window.setView(camera_view);
#endif
}
