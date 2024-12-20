#include <iostream>
#include <filesystem>

#include "SFML/Graphics.hpp"

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

	image.saveToFile(fileName.substr(0, fileName.size() - 4) + "Bin" + ".jpg");
	std::cout << "SavedBinJpg" << std::endl;
}

void ImageBinToJpgHaffman(std::string fileName)
{
	sf::Image image;

	std::ifstream readFile(fileName);
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

			/*if (offset > binaryString.size() - 10)
			{
				std::cout << binaryString.size() - 10 << " " << offset << std::endl;
				break;
			}*/

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

	image.saveToFile(fileName.substr(0, fileName.size() - 4) + "BinHaffman" + ".jpg");
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
	ModifyImageKMeans imageK;
	int quantityColors = 0;
	
	/*std::cout << std::endl;
	std::cout << argv[0] << std::endl;
	std::cout << argv[1] << std::endl;
	std::cout << std::endl;*/

	// Просто запуск программы
	if (argc == 1)
	{
		folder = "Images/LowLow";
		fileName = "ImageLowLow.jpg";
		quantityColors = 127;
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, false);
		imageK.SaveToJpg(folder + "/" + "Few" + std::to_string(quantityColors) + fileName);
		imageK.SaveToJpg(folder + "/" + "Few" + std::to_string(quantityColors) + fileName);
		imageK.SaveToBin(
			folder + "/" + "Few" + std::to_string(quantityColors) + fileName.substr(0, fileName.size() - 4) + ".bin", 1);
		//ImageBinToJpgHaffman(
		//	folder + "/" + "Few" + std::to_string(quantityColors) + fileName.substr(0, fileName.size() - 4) + ".bin");
	}
	if (argc == 2)
	{
		std::filesystem::path path(argv[1]);
		folder = path.parent_path().string(); 
		fileName = path.filename().string();
		quantityColors = 15;
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, false);
		imageK.SaveToJpg(folder + "/" + "Few" + std::to_string(quantityColors) + fileName);
		imageK.SaveToBin(
			folder + "/" + "Few" + std::to_string(quantityColors) + fileName.substr(0, fileName.size() - 4) + ".bin", 1);
		//ImageBinToJpg(
		//	folder + "/" + "Few" + std::to_string(quantityColors) + fileName.substr(0, fileName.size() - 4) + ".bin");
		
	}
	else if (argc == 3)
	{
		std::filesystem::path path(argv[1]);
		folder = path.parent_path().string();
		fileName = path.filename().string();
		quantityColors = std::stoi(argv[2]);
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, false);
		imageK.SaveToJpg(folder + fileName + "_few" + ".jpg");
	}
	else if (argc == 4)
	{
		folder = argv[1];
		fileName = argv[2];
		quantityColors = std::stoi(argv[3]);
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, true);
		imageK.SaveToJpg(folder + fileName + "_few" + ".jpg");
	}
	else if (argc == 5)
	{
		folder = argv[1];
		fileName = argv[2];
		quantityColors = std::stoi(argv[3]);
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, true);
		std::string arg = argv[4];
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
