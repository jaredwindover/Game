#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "Terrain.h"
#include "Utility.h"

Terrain::Terrain(std::string tFile){
  std::string image;
  std::ifstream f(tFile);
  f >> width >> height >> image >> count;
  points.resize(count);
  normals.resize(count);
  deltas.resize(count);
  int x;
  int y;
  sf::Vector2f diff;
  for (int i = 0; i < count; i++){
    f >> x >> y;
    points[i] = sf::Vector2f(x,y);
  }
  for (int i = 0; i < (count - 1); i++){
    diff = points[i + 1] - points[i];
    normals[i] = std::atan2(diff.y,diff.x)*180/PI + 270;
    normals[i] += 360;
    normals[i] %= 360;
    deltas[i] = length(diff);
  }
  diff = points[0] - points[count - 1];
  normals[count - 1] = std::atan2(diff.y,diff.x)*180/PI + 270;
  normals[count - 1] += 360;
  normals[count - 1] %= 360;
  deltas[count - 1] = length(diff);
  texture = sf::Texture();
  texture.loadFromFile(image);
  sprite = sf::Sprite(texture);
}

void Terrain::draw(sf::RenderTarget& target,
		   sf::RenderStates states)const{
  target.draw(sprite);
}

Terrain::~Terrain(){}

std::tuple<int,int> Terrain::moveAlong(int index,
				       int curDist,
				       int dist){
  int d2Next;
  if (dist >= 0){
    while (dist > 0){
      d2Next = deltas[index];
      if (curDist + dist < d2Next){
	curDist += dist;
	dist = 0;
      } else {
	dist -= d2Next;
	index += 1;
	index %= count;
	curDist = 0;
      }
    }
  } else {
    while (dist < 0){
      if (curDist > dist){
	curDist += dist;
	dist = 0;
      } else {
	dist += curDist;
	index +=  count - 1;
	index %= count;
	curDist = deltas[index];
      }
    }
  }
  return std::tuple<int,int>(index,curDist);
}

int Terrain::getNormal(int index){
  return normals[index];
}

sf::Vector2f Terrain::getPosition(int index, int distance){
  sf::Vector2f pos = points[index];
  sf::Vector2f dir = points[(index + 1) % count] - points[index];
  int delta = deltas[index];
  pos += ((float)distance / delta)*dir;
  return pos;
}
