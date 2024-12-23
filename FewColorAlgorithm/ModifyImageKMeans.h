#pragma once
#include "ModifyImage.h"


class ModifyImageKMeans : public ModifyImage
{
private:
	std::vector<std::shared_ptr<Point>> points;

public:
	ModifyImageKMeans(){}
	ModifyImageKMeans(std::string& folder, std::string& fileName, int _quantityColor, bool floydSteinberg);

	std::vector<sf::Vector3f> clustersSumCoords;
	std::vector<int> quantityInClusters;

	void FillPoints();
	void ScoreDistanceFirst();
	void ScoreDistanceContinue();

};

