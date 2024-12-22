#pragma once
#include "ModifyImage.h"


class ModifyImageKMeans : public ModifyImage
{
private:



public:
	ModifyImageKMeans(){}
	ModifyImageKMeans(std::string folder, std::string fileName, int _quantityColor, bool floydSteinberg);

	std::vector<std::shared_ptr<Point>> points;

	std::vector<std::vector<std::shared_ptr<Point>>> clusters;

	void FillPoints();
	void ScoreDistanceFirst();
	void ScoreDistanceContinue();

};

