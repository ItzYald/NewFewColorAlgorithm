#include "ModifyImageKMeans.h"


ModifyImageKMeans::ModifyImageKMeans(std::string folder,
	std::string fileName, int _quantityColors, bool floydSteinberg)
{
	quantityColors = _quantityColors;

	originalImage = sf::Image();
	originalImage.loadFromFile(folder + "/" + fileName);
	modifyImage = originalImage;

	optimizedColors = std::vector<sf::Color>();
	for (size_t i = 0; i < quantityColors; i++)
	{
		optimizedColors.push_back(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		clusters.push_back(std::vector<std::shared_ptr<Point>>());
	}

	FillPoints();
	ScoreDistanceFirst();
	for (size_t i = 0; i < 3; i++)
	{
		ScoreDistanceContinue();
	}
	for (size_t k = 0; k < quantityColors; k++)
	{
		std::cout << (int)optimizedColors[k].r << " " << (int)optimizedColors[k].g << " " << (int)optimizedColors[k].b << std::endl;
	}

	FillImage(floydSteinberg);
}

void ModifyImageKMeans::FillPoints()
{
	for (size_t i = 0; i < originalImage.getSize().x; i++)
	{
		for (size_t j = 0; j < originalImage.getSize().y; j++)
		{
			sf::Color thisColor = originalImage.getPixel(i, j);
			points.push_back(std::make_shared<Point>(thisColor.r, thisColor.g, thisColor.b, -1));
		}
	}
}

void ModifyImageKMeans::ScoreDistanceFirst()
{
	std::vector<float> distancesToCentres;
	float minDistance;
	int index;
	for (std::shared_ptr<Point>& thisPoint : points)
	{
		distancesToCentres.clear();
		for (size_t i = 0; i < optimizedColors.size(); i++)
		{
			distancesToCentres.push_back(pifagorMetric(*thisPoint, optimizedColors[i]));
		}

		minDistance = *std::min_element(distancesToCentres.begin(), distancesToCentres.end());
		index = std::distance(distancesToCentres.begin(), std::find(distancesToCentres.begin(), distancesToCentres.end(), minDistance));

		clusters[index].push_back(thisPoint);
		thisPoint->setNumberCluster(index);
	}
	std::cout << "distanceFirst" << std::endl;

}

void ModifyImageKMeans::ScoreDistanceContinue()
{
	oldOptimizedColors = optimizedColors;
	sf::Vector3f sumCoords;
	for (size_t i = 0; i < clusters.size(); i++)
	{
		sumCoords = sf::Vector3f(0, 0, 0);
		for (std::shared_ptr<Point>& thisPoint : clusters[i])
		{
			sumCoords += sf::Vector3f(thisPoint->r, thisPoint->g, thisPoint->b);
		}
		optimizedColors[i] = sf::Color(sumCoords.x / (float)clusters[i].size(), sumCoords.y / (float)clusters[i].size(), sumCoords.z / (float)clusters[i].size());;
	}

	std::vector<float> distancesToCentres;
	float minDistance;
	int index;
	for (size_t i = 0; i < clusters.size(); i++)
	{
		clusters[i].clear();
	}
	for (std::shared_ptr<Point>& thisPoint : points)
	{
		distancesToCentres.clear();
		for (size_t i = 0; i < optimizedColors.size(); i++)
		{
			distancesToCentres.push_back(pifagorMetric(*thisPoint, optimizedColors[i]));
		}

		minDistance = *std::min_element(distancesToCentres.begin(), distancesToCentres.end());
		auto find = std::find(distancesToCentres.begin(), distancesToCentres.end(), minDistance);

		if (find != distancesToCentres.end())
		{
			index = std::distance(distancesToCentres.begin(), find);
			clusters[index].push_back(thisPoint);
			thisPoint->setNumberCluster(index);
		}
	}

	std::cout << "distanceContinue" << std::endl;

}
