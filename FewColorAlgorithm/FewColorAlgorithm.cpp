#include <iostream>
#include <filesystem>

#include "SFML/Graphics.hpp"

#include "ModifyImageStaticCubes.h"
#include "ModifyImageKMeans.h"


void ImageBinToJpg(std::string fileName)
{
	sf::Image image;

	//std::ifstream readFile(folder + fileName + "Line" + std::to_string(quantityColors) + "_" + "k" + ".bin", std::ios::binary);
	std::ifstream readFile(fileName, std::ios::binary);
	if (!readFile)
	{
		std::cerr << "Error opening file for reading." << std::endl;
	}

	// Размер изображения
	int imageSizeX;
	readFile.read((char*)&imageSizeX, sizeof(imageSizeX));
	int imageSizeY;
	readFile.read((char*)&imageSizeY, sizeof(imageSizeY));


	image = sf::Image();
	image.create((int)imageSizeX, (int)imageSizeY);

	// Количество цветов
	int quantityColorsBin;
	readFile.read((char*)&quantityColorsBin, sizeof(quantityColorsBin));
	std::cout << quantityColorsBin << std::endl;

	std::vector<sf::Color> optimizedColors;
	for (size_t i = 0; i < (int)quantityColorsBin; i++)
	{
		optimizedColors.push_back(sf::Color(0, 0, 0));
	}

	// Цвета
	for (size_t i = 0; i < (int)quantityColorsBin; i++)
	{
		uint8_t thisColorR;
		readFile.read((char*)&thisColorR, sizeof(thisColorR));
		optimizedColors[i].r = (int)thisColorR;
		uint8_t thisColorG;
		readFile.read((char*)&thisColorG, sizeof(thisColorG));
		optimizedColors[i].g = (int)thisColorG;
		uint8_t thisColorB;
		readFile.read((char*)&thisColorB, sizeof(thisColorB));
		optimizedColors[i].b = (int)thisColorB;
	}

	std::string binaryString;

	uint8_t buffer;

	while (readFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
	{
		for (size_t i = 0; i < sizeof(buffer); ++i)
		{
			// Здесь обрабатываем каждый бит
			binaryString += std::bitset<8>(buffer >> i).to_string();
		}
	}

	int offset;
	offset = 0;

	// Заполнение пикселей
	for (size_t i = 0; i < imageSizeX; i++)
	{
		for (size_t j = 0; j < imageSizeY; j++)
		{
			uint8_t thisColorNumberByte = 0;

			//offset += 1;

			if (offset > binaryString.size() - 100)
			{
				std::cout << binaryString.size() - 100 << " " << offset << std::endl;
				break;
			}

			std::string thisString = "";

			//thisString += binaryString[offset];

			for (size_t i = 0; i < log2(quantityColorsBin); i++)
			{
				thisString += binaryString[offset];
				offset += 1;
			}

			bool isRow = false;

			if (thisString == "1111111" && quantityColorsBin == 127 || thisString == "11111111" && quantityColorsBin == 255 || thisString == "111111111" && quantityColorsBin == 511)
			{
				isRow = true;
				thisString = "";
				for (size_t i = 0; i < log2(quantityColorsBin); i++)
				{
					thisString += binaryString[offset];
					offset += 1;
				}
			}
			
			int aboba = log2(quantityColorsBin);

			thisColorNumberByte = std::stoi(thisString, nullptr, 2);

			sf::Color thisColor = optimizedColors[(int)(thisColorNumberByte)];
			if (isRow)
			{
				std::string quantityEqualsColorsString = "";
				for (size_t i = 0; i < log2(quantityColorsBin); i++)
				{
					quantityEqualsColorsString += binaryString[offset];
					offset += 1;
				}

				uint8_t quantityEqualsColors = std::stoi(quantityEqualsColorsString, nullptr, 2);

				if (j + quantityEqualsColors - 1 >= imageSizeY)
				{
					continue;
				}
				for (size_t k = 0; k < (int)quantityEqualsColors; k++)
				{
					image.setPixel(i, j + (int)k, thisColor);
				}
				j += quantityEqualsColors - 1;
			}
			else
			{
				image.setPixel(i, j, thisColor);
			}

		}
	}

	readFile.close();
	std::cout << "Read Bin" << std::endl;

	image.saveToFile(fileName.substr(0, fileName.size() - 4) + ".jpg");
	std::cout << "SavedBinJpg" << std::endl;
}

void ImageBinToJpgHaffman(std::string folder, std::string fileName, std::string type, int quantityColors, int quantityCubes)
{
	sf::Image image;

	std::ifstream readFile(folder + fileName + "Haffman" + std::to_string(quantityColors) + "_" + "k" + ".bin", std::ios::binary, std::ios::binary);
	if (!readFile)
	{
		std::cerr << "Error opening file for reading." << std::endl;
	}

	// Размер изображения
	int imageSizeX;
	readFile.read((char*)&imageSizeX, sizeof(imageSizeX));
	int imageSizeY;
	readFile.read((char*)&imageSizeY, sizeof(imageSizeY));


	image = sf::Image();
	image.create((int)imageSizeX, (int)imageSizeY);

	// Количество цветов
	int quantityColorsBin;
	readFile.read((char*)&quantityColorsBin, sizeof(quantityColorsBin));

	std::vector<sf::Color> optimizedColors;
	for (size_t i = 0; i < (int)quantityColorsBin; i++)
	{
		optimizedColors.push_back(sf::Color(0, 0, 0));
	}

	// Цвета
	for (size_t i = 0; i < (int)quantityColorsBin; i++)
	{
		uint8_t thisColorR;
		readFile.read((char*)&thisColorR, sizeof(thisColorR));
		optimizedColors[i].r = (int)thisColorR;
		uint8_t thisColorG;
		readFile.read((char*)&thisColorG, sizeof(thisColorG));
		optimizedColors[i].g = (int)thisColorG;
		uint8_t thisColorB;
		readFile.read((char*)&thisColorB, sizeof(thisColorB));
		optimizedColors[i].b = (int)thisColorB;
	}

	std::string binaryString;

	uint8_t buffer;

	while(readFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
	{
		for (size_t i = 0; i < sizeof(buffer); ++i)
		{
			// Здесь обрабатываем каждый бит
			binaryString += std::bitset<8>(buffer >> i).to_string();
		}
	}

	int offset;
	offset = -1;

	// Заполнение пикселей
	for (size_t i = 0; i < imageSizeX; i++)
	{
		for (size_t j = 0; j < imageSizeY; j++)
		{
			uint8_t thisColorNumberByte = 0;

			offset += 1;

			if (offset > binaryString.size() - 10)
			{
				std::cout << binaryString.size() - 10 << " " << offset << std::endl;
				break;
			}

			std::string thisString = "";

			thisString += binaryString[offset];
			bool isRow = false;
			while (true)
			{
 				offset += 1;
				thisString += binaryString[offset];

				if (thisString == "01")
				{
					isRow = true;
					thisString = "";
					continue;
				}

				
				if (thisString == "10")
				{
					thisColorNumberByte = 0;
					break;
				}
				else if (thisString == "0001")
				{
					thisColorNumberByte = 1;
					break;
				}
				else if (thisString == "0011")
				{
					thisColorNumberByte = 2;
					break;
				}
				else if (thisString == "00101")
				{
					thisColorNumberByte = 3;
					break;
				}
				else if (thisString == "00100")
				{
					thisColorNumberByte = 4;
					break;
				}
				else if (thisString == "00001")
				{
					thisColorNumberByte = 5;
					break;
				}
				else if (thisString == "000001")
				{
					thisColorNumberByte = 6;
					break;
				}
				else if (thisString == "0000001")
				{
					thisColorNumberByte = 7;
					break;
				}
				else if (thisString == "00000001")
				{
					thisColorNumberByte = 8;
					break;
				}
				else if (thisString == "000000001")
				{
					thisColorNumberByte = 9;
					break;
				}
				else if (thisString == "11")
				{
					thisString = "";
					for (size_t i = 0; i < log2(quantityColorsBin); i++)
					{
						offset += 1;
						thisString += binaryString[offset];
					}

					thisColorNumberByte = std::stoi(thisString, nullptr, 2);
					break;
				}
			}

			sf::Color thisColor = optimizedColors[(int)(thisColorNumberByte)];
			if (isRow)
			{
				std::string quantityEqualsColorsString = "";
				for (size_t i = 0; i < log2(quantityColorsBin); i++)
				{
					offset += 1;
					quantityEqualsColorsString += binaryString[offset];
				}

				uint8_t quantityEqualsColors = std::stoi(quantityEqualsColorsString, nullptr, 2);

				if (j + quantityEqualsColors - 1 >= imageSizeY)
				{
					continue;
				}
				for (size_t k = 0; k < (int)quantityEqualsColors; k++)
				{
					image.setPixel(i, j + (int)k, thisColor);
				}
				j += quantityEqualsColors - 1;
			}
			else
			{
				image.setPixel(i, j, thisColor);
			}


		}

	}

	readFile.close();
	std::cout << "Read Bin" << std::endl;

	image.saveToFile(folder + fileName + "Haffman" + std::to_string(quantityColors) + "_" + "k" + ".jpg");
	std::cout << "SavedBinJpgHaffman" << std::endl;
}

void FileSize(std::ofstream& file, std::string folder, std::string fileName, std::string type, int quantityColors, int quantityCubes)
{

	std::filesystem::path filePath;
	filePath = folder + fileName + std::to_string(quantityColors) + "_" + "k" + ".bin";
	file << std::to_string(quantityColors) + "_" + "k" << " " << std::filesystem::file_size(filePath) / 1024 << std::endl;

	filePath = folder + fileName + "Line" + std::to_string(quantityColors) + "_" + "k" + ".bin";
	file << std::to_string(quantityColors) + "_" + "k" + "Line" << " " << std::filesystem::file_size(filePath) / 1024 << std::endl;

	filePath = folder + fileName + "Haffman" + std::to_string(quantityColors) + "_" + "k" + ".bin";
	file << std::to_string(quantityColors) + "_" + "k" + "Haffman" << " " << std::filesystem::file_size(filePath) / 1024 << std::endl;

	filePath = folder + fileName + "HaffmanLine" + std::to_string(quantityColors) + "_" + "k" + ".bin";
	file << std::to_string(quantityColors) + "_" + "k" + "HaffmanLine" << " " << std::filesystem::file_size(filePath) / 1024 << std::endl;
	file << std::endl;
	std::cout << "Saved staticstic\n";
}

int main(int argc, char* argv[])
{
	std::string folder;
	std::string fileName;
	std::string type;
	int quantityColors = 0;
	int quantityCubes = 0;

	if (argc == 1)
	{
		folder = "Images/LowLow/";
		fileName = "ImageLowLow";
		quantityColors = 31;
		quantityCubes = 16;
		ModifyImageKMeans imageK = ModifyImageKMeans(folder, fileName, quantityColors);
	}
	else if (argc == 2)
	{
		std::string str = fileName.substr(0, fileName.size() - 3);
		std::cout << "lol";
		std::cout << std::endl;
	}
	else if (argc == 3)
	{
		folder = argv[1];
		fileName = argv[2];
		quantityColors = 31;
		quantityCubes = 16;
		ModifyImageKMeans imageK = ModifyImageKMeans(folder, fileName, quantityColors);
		imageK.SaveToJpg(folder + fileName + "_few" + ".jpg");
	}
	else if (argc == 4)
	{
		folder = argv[1];
		fileName = argv[2];
		quantityColors = 31;
		quantityCubes = 16;
		ModifyImageKMeans imageK = ModifyImageKMeans(folder, fileName, quantityColors);
		std::string arg = argv[3];
		if (arg == "jpg")
			imageK.SaveToJpg(folder + fileName + "_few" + ".jpg");
		else
			imageK.SaveToBin(folder + fileName + ".bin", 1);
	}
	else
	{
		std::cout << "Слишком много аргументов";
		std::cout << argc << std::endl;
		for (size_t i = 0; i < argc; i++)
		{
			std::cout << argv[i] << " ";
		}
		std::cout << std::endl;
	}
}
