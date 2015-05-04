#include "Player.h"

#include <string>
#include <fstream>
#include <iostream>

#include "Terrain.h"
#include "Utility.h"

Player::Player(std::string pFile):
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
  //sf::CircleShape circ(10,20);
  //circ.setPosition(circPos);
  //circ.setOutlineColor(sf::Color::White);
  //circ.setOutlineThickness(3);
  //circ.setFillColor(sf::Color::White);
  //circ.setOrigin(10,10);
  //target.draw(circ);
  //int n = terrain->getNormal(terrainIndex);
  //sf::Vertex normal[] = {
  //sf::Vertex(circPos),
  //sf::Vertex(circPos +
  //	       sf::Vector2f(30*cos(n*PI/180),
  //			    30*sin(n*PI/180)))
  //};
  target.draw(sprite);
  //target.draw(normal,2,sf::Lines);
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

void Player::setTerrain(Terrain *t){
  terrain  = t;
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
