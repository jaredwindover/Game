#include <gtest/gtest.h>

#include "Utility.h"

#include <SFML/Graphics.hpp>

TEST(Test1,A){
  sf::Vector2f TestVec(1,1);
  sf::Vector2f CompVec(1,1);
  rotate(TestVec,0);
  EXPECT_EQ(TestVec,CompVec);
}
