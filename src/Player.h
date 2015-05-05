#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <SFML/Graphics.hpp>

#include "Terrain.h"

enum Direction {LEFT, RIGHT};

class Player: public sf::Drawable{
private:
  bool walking;
  Direction facing;
  Terrain * terrain;
  int terrainIndex;
  int terrainDist;
  sf::Texture texture;
  sf::Sprite sprite;
  int width;
  int height;
  int distanceToGo;
protected:
public:
  Player(std::string);
  ~Player();
  virtual void draw(sf::RenderTarget&,sf::RenderStates) const;
  void update();
  void setTerrain(Terrain *, int = 0, int = 0);
  void setIndex(int);
  void setDistance(int);
  void move(int);
  void face(Direction);
  sf::Vector2f getPosition();
  float getRotation();
};

#endif
