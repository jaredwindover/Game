#include "Utility.h"

void rotate(sf::Vector2f& vec,int amt){
  float newx = cos(amt*PI/180)*vec.x + sin(amt*PI/180)*vec.y;
  float newy = cos(amt*PI/180)*vec.y - sin(amt*PI/180)*vec.x;
  vec = sf::Vector2f(newx,newy);
}

int distance(sf::Vector2f vecA, sf::Vector2f vecB){
  return (int)sqrt(pow(vecA.x - vecB.x,2) + pow(vecA.y - vecB.y,2));
}

float length(sf::Vector2f vec){
  return (float)sqrt(pow(vec.x,2) + pow(vec.y,2));
}
