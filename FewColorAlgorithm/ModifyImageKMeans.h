#pragma once
#include "ModifyImage.h"


class ModifyImageKMeans : public ModifyImage
{
private:



public:
	ModifyImageKMeans(){}
	ModifyImageKMeans(std::string folder, std::string fileName, int _quantityColor);

	std::vector<std::shared_ptr<Point>> points;

	std::vector<std::vector<std::shared_ptr<Point>>> clusters;

	std::vector<sf::Color> oldOptimizedColors;

	void FillPoints();
	void ScoreDistanceFirst();
	void ScoreDistanceContinue();

};

