#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>
#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>

class Terrain: public sf::Drawable{
private:
  int width;
  int height;
  int count;
  std::vector<sf::Vector2f> points;
  std::vector<int> normals;
  std::vector<float> deltas;
  sf::Texture texture;
  sf::Sprite sprite;
  virtual void draw(sf::RenderTarget&,sf::RenderStates) const;
protected:
public:
  Terrain(std::string);
  ~Terrain();
  std::tuple<int,int> moveAlong(int,int,int);
  int getNormal(int);
  sf::Vector2f getPosition(int, int);
};

#endif
