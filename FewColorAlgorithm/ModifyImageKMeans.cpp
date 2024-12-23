#include "ModifyImageKMeans.h"


ModifyImageKMeans::ModifyImageKMeans(std::string& folder,
	std::string& fileName, int _quantityColors, bool floydSteinberg)
{
	quantityColors = _quantityColors;

	originalImage = sf::Image();
	originalImage.loadFromFile(folder + fileName);
	modifyImage = originalImage;

	optimizedColors = std::vector<sf::Color>();
	clustersSumCoords = std::vector<sf::Vector3f>();
	quantityInClusters = std::vector<int>();
	for (size_t i = 0; i < quantityColors; i++)
	{
		optimizedColors.push_back(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		clustersSumCoords.push_back(sf::Vector3f(0, 0, 0));
		quantityInClusters.push_back(0);
	}

	FillPoints();
	ScoreDistanceFirst();
	for (size_t i = 0; i < 10; i++)
	{
		ScoreDistanceContinue();
	}
	for (size_t k = 0; k < quantityColors; k++)
	{
		std::cout << (int)optimizedColors[k].r << " " << (int)optimizedColors[k].g << " " << (int)optimizedColors[k].b << "  " << quantityInClusters[k] << std::endl;
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
	double minDistance = 1000000000000;
	int index = 0;
	for (std::shared_ptr<Point>& thisPoint : points)
	{
		minDistance = 1000000000000;
		double distance;
		index = 0;
		for (size_t i = 0; i < optimizedColors.size(); i++)
		{
			distance = maxCoordsDistance(*thisPoint, optimizedColors[i]);
			if (distance < minDistance)
			{
				minDistance = distance;
				index = i;
			}
		}

		clustersSumCoords[index] += sf::Vector3f(thisPoint->r, thisPoint->g, thisPoint->b);
		quantityInClusters[index] += 1;
		thisPoint->setNumberCluster(index);
	}

	std::cout << "distanceFirst" << std::endl;

}

void ModifyImageKMeans::ScoreDistanceContinue()
{
	sf::Vector3f sumCoords;
	for (size_t i = 0; i < clustersSumCoords.size(); i++)
	{
		float clusterSize = quantityInClusters[i];
		optimizedColors[i] = sf::Color(clustersSumCoords[i].x / clusterSize,
			clustersSumCoords[i].y / clusterSize, clustersSumCoords[i].z / clusterSize);;
	}

	for (size_t i = 0; i < clustersSumCoords.size(); i++)
	{
		clustersSumCoords[i] = sf::Vector3f(0, 0, 0);
		quantityInClusters[i] = 0;
	}

	double minDistance = 1000000000000;
	int index = 0;
	for (std::shared_ptr<Point>& thisPoint : points)
	{
		minDistance = 1000000000000;
		double distance;
		index = 0;
		for (size_t i = 0; i < optimizedColors.size(); i++)
		{
			distance = maxCoordsDistance(*thisPoint, optimizedColors[i]);
			if (distance < minDistance)
			{
				minDistance = distance;
				index = i;
			}
		}

		clustersSumCoords[index] += sf::Vector3f(thisPoint->r, thisPoint->g, thisPoint->b);
		quantityInClusters[index] += 1;
		thisPoint->setNumberCluster(index);
	}

	std::cout << "distanceContinue" << std::endl;

}

