#include <fstream>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Background.h"
#include "Utility.h"


Background::Background(std::string bgFile,sf::View &camera):
  camera_view(camera)
{
  std::ifstream f(bgFile);
  int count;
  f >> tileHeight >> tileWidth;
  sf::IntRect rect(0,0,tileWidth,tileHeight);
  f >> count;
  list.resize(count);
  textures.resize(count);
  sprites.resize(count);
  for (int i = 0; i < count; i++){
    f >> list[i]; 
    textures[i] = sf::Texture();
    textures[i].loadFromFile(list[i],rect);
    sprites[i] = new sf::Sprite(textures[i]);
  }
  f >> height >> width;
  tiles.resize(height);
  for (auto& tileVec: tiles){
    tileVec.resize(width);
  }
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      f >> tiles[i][j];
    }
  }
  f >> parallax;
  update();
}

Background::~Background(){
  sprites.erase(sprites.begin(),sprites.end());
  
}

void Background::draw(sf::RenderTarget& target,
		      sf::RenderStates states) const{
  for (int i = xi; i < xi + xn; i++){
    for (int j = yi; j < yi + yn; j++){
      sf::Sprite s = *sprites[tiles[(i + width) % width][(j + height) % height]];
      s.setPosition(sf::Vector2f(i*tileWidth + offsetX,
				 j*tileHeight + offsetY));
#ifdef DEBUG
      sf::RectangleShape r(sf::Vector2f(tileWidth,tileHeight));
      r.setPosition(s.getPosition());
      r.setOutlineThickness(3);
      r.setOutlineColor(sf::Color::Blue);
      r.setFillColor(sf::Color::Transparent);
#endif
      target.draw(s);
#ifdef DEBUG
      target.draw(r);
#endif
    }
  }
}

void Background::update(){
  sf::Vector2f camera_center = camera_view.getCenter();
  sf::Vector2f camera_size = camera_view.getSize();
  offsetX = (int)((1 - parallax)*camera_center.x);
  offsetY = (int)((1 - parallax)*camera_center.y);
  sf::Vector2f A (camera_size.x/2 + 1,camera_size.y/2 + 1);
  sf::Vector2f B (camera_size.x/2 + 1,-camera_size.y/2 - 1);
  int rotation = camera_view.getRotation();
  rotate(A,rotation);
  rotate(B,rotation);
  float xd = std::max(abs(A.x),abs(B.x));
  float yd = std::max(abs(A.y),abs(B.y));
  xi = floor((camera_center.x - xd - offsetX)/tileWidth);
  yi = floor((camera_center.y - yd - offsetY)/tileHeight);
  xn = ceil(2*xd/tileWidth) + 1;
  yn = ceil(2*yd/tileHeight) + 1;
}
