#include "Point.h"

Point::Point(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, int _numberCluster) :
	sf::Color(r, g, b)
{
	numberCluster = _numberCluster;
}

void Point::setNumberCluster(int _numberCluster)
{
	numberCluster = _numberCluster;
}

