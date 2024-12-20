#include "ModifyImageStaticCubes.h"

ModifyImageStaticCubes::ModifyImageStaticCubes(std::string folder, std::string fileName, int _quantityColors, int _quantityCubes)
{
	quantityColors = _quantityColors;
	quantityCubes = _quantityCubes;

	originalImage = sf::Image();
	originalImage.loadFromFile(folder + fileName + ".jpg");
	modifyImage = originalImage;

	colorCubes = std::vector<std::vector<std::vector<int>>>();
	for (size_t i = 0; i < quantityCubes; i++)
	{
		colorCubes.push_back(std::vector<std::vector<int>>());
		for (size_t j = 0; j < quantityCubes; j++)
		{
			colorCubes[i].push_back(std::vector<int>());
			for (size_t k = 0; k < quantityCubes; k++)
			{
				colorCubes[i][j].push_back(0);
			}
		}
	}
	optimizedColors = std::vector<sf::Color>();
	for (size_t i = 0; i < quantityColors; i++)
	{
		optimizedColors.push_back(sf::Color(0, 0, 0));
	}  

	FillColorCubes();
	FillOptimizedColors();
	FillImage(false);

	SaveToJpg(folder + fileName + std::to_string(quantityColors) + "_" + std::to_string(quantityCubes) + ".jpg");
	SaveToBin(folder + fileName + std::to_string(quantityColors) + "_" + std::to_string(quantityCubes) + ".bin", false);
	SaveToBin(folder + fileName + "Line" + std::to_string(quantityColors) + "_" + std::to_string(quantityCubes) + ".bin", true);
	SaveToBinHaffman(folder + fileName + "Haffman" + std::to_string(quantityColors) + "_" + std::to_string(quantityCubes) + ".bin", false);
	SaveToBinHaffman(folder + fileName + "Haffman" + "Line" + std::to_string(quantityColors) + "_" + std::to_string(quantityCubes) + ".bin", true);
}

void ModifyImageStaticCubes::FillColorCubes()
{
	for (size_t i = 0; i < originalImage.getSize().x; i++)
	{
		for (size_t j = 0; j < originalImage.getSize().y; j++)
		{
			sf::Color thisColor = originalImage.getPixel(i, j);
			colorCubes[(int)(thisColor.r / (256 / quantityCubes))][(int)(thisColor.g / (256 / quantityCubes))][(int)(thisColor.b / (256 / quantityCubes))] += 1;
		}
	}
}

void ModifyImageStaticCubes::FillOptimizedColors()
{
	sf::Color maxColor;
	std::vector<int> maxColorMeaningList = std::vector<int>();
	int maxColorMeaning = 0;
	
	for (size_t i = 0; i < quantityColors; i++)
	{
		for (size_t j = 0; j < colorCubes.size(); j++)
		{
			for (size_t k = 0; k < colorCubes[0].size(); k++)
			{
				for (size_t t = 0; t < colorCubes[0][0].size(); t++)
				{
					if (colorCubes[j][k][t] > maxColorMeaning)
					{
						bool repeat = false;
						for (size_t l = 0; l < maxColorMeaningList.size(); l++)
						{
							if (colorCubes[j][k][t] == maxColorMeaningList[l])
							{
								repeat = true;
							}
						}
						if (!repeat)
						{
							maxColorMeaning = colorCubes[j][k][t];
							maxColor = sf::Color(j * quantityCubes, k * quantityCubes, t * quantityCubes);
						}
					}
				}
			}
		}
		maxColorMeaningList.push_back(maxColorMeaning);
		maxColorMeaning = 0;
		optimizedColors[i] = maxColor;
	}

	int sumAll = 0;
	int sumAfter0 = 0;
	int sumAfter17 = 0;

	double avarageBefore18;

	for (size_t i = 0; i < quantityColors; i++)
	{
		sumAll += maxColorMeaningList[i];
		if (i > 0)
		{
			sumAfter0 += maxColorMeaningList[i];
		}
		if (i > 17)
		{
			sumAfter17 += maxColorMeaningList[i];
		}
		std::cout << (int)optimizedColors[i].r << " " << (int)optimizedColors[i].g <<
			" " << (int)optimizedColors[i].b << " - " << maxColorMeaningList[i] << " " << i << std::endl;
	}

}
