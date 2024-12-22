#include <iostream>
#include <filesystem>

#include "SFML/Graphics.hpp"

#include "ModifyImageKMeans.h"

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
	setlocale(LC_ALL, "Russian");
	std::string folder;
	std::string fileName;
	std::string type;
	ModifyImageKMeans imageK;
	int quantityColors = 0;
	
	// Просто запуск программы
	if (argc == 1)
	{
		folder = "Images/LowLow/";
		fileName = "ImageLowLow.jpg";
		std::cout << "Введите количество цветов: " << std::endl;
		std::cin >> quantityColors;
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, false);
		imageK.SaveToJpg(folder + "Few" + std::to_string(quantityColors) + fileName);
		imageK.SaveToBin(
			folder + "Few" + std::to_string(quantityColors) + fileName.substr(0, fileName.size() - 4) + ".bin", 1);
	}
	if (argc == 2)
	{
		std::filesystem::path path(argv[1]);
		folder = path.parent_path().string() + "/";
		fileName = path.filename().string();
		std::cout << "Введите количество цветов: " << std::endl;
		std::cin >> quantityColors;
		imageK = ModifyImageKMeans(folder, fileName, quantityColors, false);
		imageK.SaveToJpg(folder + "Few" + std::to_string(quantityColors) + fileName);
		imageK.SaveToBin(
			folder + "Few" + std::to_string(quantityColors) + fileName.substr(0, fileName.size() - 4) + ".bin", 1);
		
	}
	else if (argc == 3)
	{
		std::filesystem::path path(argv[1]);
		folder = path.parent_path().string() + "/";
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
