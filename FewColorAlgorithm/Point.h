#pragma once
#include "SFML/Graphics.hpp"

class Point : public sf::Color
{
public:
	int numberCluster;

	Point() {}
	Point(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, int _numberCluster);

	void setNumberCluster(int _numberCluster);
};

