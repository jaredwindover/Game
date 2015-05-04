#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <SFML/Graphics.hpp>

#define PI 3.14159265

#ifdef DEBUG
#define dbgPrint(note) std::cout << note << std::endl << std::flush
#define dbgError(note) std::cerr << note << std::endl << std::flush
#else
#define dbgPrint(note)
#define dbgError(note)
#endif

void rotate(sf::Vector2f &,int);

int distance(sf::Vector2f vecA, sf::Vector2f vecB);

float length(sf::Vector2f vec);

#endif
