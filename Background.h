#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Background: public sf::Drawable{
private:
  sf::View& camera_view;
  std::vector<std::string> list;
  std::vector<sf::Texture> textures;
  std::vector<std::vector<int> > tiles;
  //std::vector<std::vector<sf::Sprite*> > sprites;
  //std::vector<std::vector<bool> > active_sprites;
  std::vector<sf::Sprite*> sprites;
  int height;
  int width;
  int tileHeight;
  int tileWidth;
  int xi;
  int yi;
  int xn;
  int yn;
  int offsetX;
  int offsetY;
  float parallax;
  
  virtual void draw(sf::RenderTarget&,sf::RenderStates) const;
protected:
public:
  Background(std::string,
	     sf::View&);
  ~Background();
  void update();
};

#endif
