#include <iostream>
#include <fstream>
#include <bitset>
#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <filesystem>

uint8_t MyLog(int x)
{
	//std::cout << (uint8_t)(std::log(x) / std::log(2)) + 1 << " " << x << std::endl;
	//std::cin >> x;
	return (uint8_t)(std::log(x) / std::log(2));
}

void ImageBinToJpg(std::string folder, std::string fileName)
{
	std::ifstream readFile(folder + fileName, std::ios::binary);

	if (!readFile)
	{
		std::cout << "Не удалось открыть файл" << std::endl;
	}
	
	// Размер изображения
	int imageSizeX;
	readFile.read((char*)&imageSizeX, sizeof(imageSizeX));
	int imageSizeY;
	readFile.read((char*)&imageSizeY, sizeof(imageSizeY));

	sf::Image image = sf::Image();
	image.create(imageSizeX, imageSizeY);

	// Количество цветов
	int quantityColorsBin;
	readFile.read((char*)&quantityColorsBin, sizeof(quantityColorsBin));

	std::vector<sf::Color> colors = std::vector<sf::Color>();

	// Цвета
	for (size_t i = 0; i < quantityColorsBin; i++)
	{
		colors.push_back(sf::Color(0, 0, 0));
		uint8_t thisColorR;
		readFile.read((char*)&thisColorR, sizeof(thisColorR));
		colors[i].r = thisColorR;
		uint8_t thisColorG;
		readFile.read((char*)&thisColorG, sizeof(thisColorG));
		colors[i].g = thisColorG;
		uint8_t thisColorB;
		readFile.read((char*)&thisColorB, sizeof(thisColorB));
		colors[i].b = thisColorB;
	}

	std::cout << quantityColorsBin << std::endl;

	std::string binaryString = "";

	uint8_t buffer;

	while (readFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
	{
		for (size_t i = 0; i < sizeof(buffer); ++i)
		{
			binaryString += std::bitset<8>(buffer >> i).to_string();
		}
	}

	int offset = 0;

	int quantityColorsLog = MyLog(quantityColorsBin);
	std::cout << quantityColorsLog << std::endl;
	int lol;
	std::cin >> lol;

	for (size_t i = 0; i < imageSizeX; i++)
	{
		for (size_t j = 0; j < imageSizeY; j++)
		{
			if (offset > binaryString.size() - 2)
			{
				//std::cout << binaryString.size() - 2 << " " << offset << std::endl;
				break;
			}

			std::string thisString = binaryString.substr(offset, quantityColorsLog);
			offset += quantityColorsLog;

			if (std::stoi(thisString, nullptr, 2) == quantityColorsBin - 1)
			{
				thisString = binaryString.substr(offset, quantityColorsLog);
				sf::Color thisColor = colors[std::stoi(thisString, nullptr, 2)];
				offset += quantityColorsLog;
				thisString = binaryString.substr(offset, quantityColorsLog);
				offset += quantityColorsLog;
				std::cout << thisString << " ";
				if (j + std::stoi(thisString, nullptr, 2) - 1 >= imageSizeY)
				{
					offset -= quantityColorsLog * 3;
					break;
				}
				for (size_t k = 0; k < std::stoi(thisString, nullptr, 2); k++)
				{
					if (j < imageSizeY)
					{
						image.setPixel(i, j, thisColor);
					}
					j += 1;
				}
				j -= 1;
				
			}
			else
			{
				sf::Color thisColor = colors[std::stoi(thisString, nullptr, 2)];
				image.setPixel(i, j, thisColor);
			}
		}
	}

	readFile.close();

	image.saveToFile(folder + fileName.substr(0, fileName.size() - 4) + "Bin" + ".jpg");
	std::cout << "SavedBinJpg" << std::endl;

}

int main(int argc, char* argv[])
{
	std::string folder;
	std::string fileName;
	if (argc == 1)
	{
		folder = "Images/LowLow/";
		fileName = "Few32Image.bin";
		ImageBinToJpg(folder, fileName);
	}
	if (argc == 2)
	{
		std::filesystem::path path(argv[1]);
		folder = path.parent_path().string() + "/";
		fileName = path.filename().string();
		ImageBinToJpg(folder, fileName);
	}
}
