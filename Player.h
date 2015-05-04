#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <SFML/Graphics.hpp>

#include "Terrain.h"

class Player: public sf::Drawable{
private:
  bool walking;
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
  void setTerrain(Terrain *);
  void setIndex(int);
  void setDistance(int);
  void move(int);
};

#endif
