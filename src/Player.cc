#include "Player.h"

#include <string>
#include <fstream>
#include <iostream>

#include "Terrain.h"
#include "Utility.h"

Player::Player(std::string pFile):
  facing(RIGHT),
  terrainIndex(0),
  distanceToGo(0)
{
  walking = true;
  std::ifstream f(pFile);
  f >> width >> height;
  std::string imagefile;
  f >> imagefile;
  texture.loadFromFile(imagefile);
  sprite = sf::Sprite(texture);
}

Player::~Player(){}

void Player::draw(sf::RenderTarget& target,
		  sf::RenderStates states) const{
  target.draw(sprite);
}

void Player::update(){
  std::tuple<int,int> result =
    terrain->moveAlong(terrainIndex,terrainDist,distanceToGo);
  distanceToGo = 0;
  terrainIndex = std::get<0>(result);
  terrainDist =std::get<1>(result);
  sf::Vector2f circPos = terrain->getPosition(terrainIndex,terrainDist);
  sprite.setOrigin(width/2,height);
  sprite.setPosition(circPos);
  sprite.setRotation(terrain->getNormal(terrainIndex) + 90);
}

void Player::setTerrain(Terrain *t, int index, int dist){
  terrain  = t;
  terrainIndex = index;
  terrainDist = dist;
}

void Player::setIndex(int i){
  terrainIndex = i;
}

void Player::setDistance(int d){
  terrainDist = d;
}

void Player::move(int d){
  distanceToGo += d;
}

void Player::face(Direction d){
  facing = d;
  if (d == LEFT){
    sprite.setTextureRect(sf::IntRect(width,0,-width,height));
  } else {
    sprite.setTextureRect(sf::IntRect(0,0,width,height));    
  }
}
