#include "ModifyImage.h"

double ModifyImage::pifagorMetric(Point point1, sf::Color point2)
{
	return 
		std::pow(point1.r - point2.r, 2) +
		std::pow(point1.g - point2.g, 2) +
		std::pow(point1.b - point2.b, 2);
}

double ModifyImage::pifagorMetric(sf::Color point1, sf::Color point2)
{
	return 
		std::pow(point1.r - point2.r, 2) +
		std::pow(point1.g - point2.g, 2) +
		std::pow(point1.b - point2.b, 2);
}

float ModifyImage::maxCoordsDistance(Point point1, sf::Color point2)
{
	return std::max(std::max(std::abs(point1.r - point2.r), std::abs(point1.g - point2.g)), std::abs(point1.b - point2.b));
}

float ModifyImage::maxCoordsDistance(sf::Color point1, sf::Color point2)
{
	return std::max(std::max(std::abs(point1.r - point2.r), std::abs(point1.g - point2.g)), std::abs(point1.b - point2.b));
}

void ModifyImage::SaveToJpg(std::string fileName)
{
	modifyImage.saveToFile(fileName);
	std::cout << fileName << std::endl;
	std::cout << "Saved Jpg" << std::endl;
}

void ModifyImage::SaveToBin(std::string fileName, int typeCompress)
{
	std::ofstream writeFile(fileName, std::ios::binary);
	if (!writeFile)
	{
		std::cerr << "Error opening file for writing." << std::endl;
	}

	// Размер изображения
	int imageSizeX = originalImage.getSize().x;
	writeFile.write((char*)&imageSizeX, sizeof(imageSizeX));
	int imageSizeY = originalImage.getSize().y;
	writeFile.write((char*)&imageSizeY, sizeof(imageSizeY));

	// Количество цветов
	int quantityColorsBin = optimizedColors.size();
	writeFile.write((char*)&quantityColorsBin, sizeof(quantityColorsBin));

	// Цвета
	for (size_t i = 0; i < quantityColors; i++)
	{
		uint8_t thisColorR = optimizedColors[i].r;
		writeFile.write((char*)&thisColorR, sizeof(thisColorR));
		uint8_t thisColorG = optimizedColors[i].g;
		writeFile.write((char*)&thisColorG, sizeof(thisColorG));
		uint8_t thisColorB = optimizedColors[i].b;
		writeFile.write((char*)&thisColorB, sizeof(thisColorB));
	}

	std::string binaryString = "";

	// Заполнение пикселей
	for (size_t i = 0; i < originalImage.getSize().x; i++)
	{
		for (size_t j = 0; j < originalImage.getSize().y; j++)
		{
			uint8_t row = 0;

			sf::Color thisColor = modifyImage.getPixel(i, j);

			for (size_t k = 0; k < quantityColors - 1; k++)
			{
				if (j + k >= originalImage.getSize().y)
					break;
				if (modifyImage.getPixel(i, j + k) == thisColor && typeCompress == 1)
					row += 1;
				else
					break;
			}

			uint8_t thisColorNumberByte = 0;

			for (size_t k = 0; k < optimizedColors.size(); k++)
			{
				thisColorNumberByte = k;
				if (thisColor == optimizedColors[k])
					break;
			}

			if (row > 3 || thisColorNumberByte == quantityColors - 1)
			{
				uint8_t rowBit = quantityColors - 1;
				for (size_t i = 0; i < sizeof(rowBit); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(rowBit >> i).to_string();
					}
					if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(rowBit >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(rowBit >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(rowBit >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(rowBit >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(rowBit >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(rowBit >> i).to_string();
					}
				}
				for (size_t i = 0; i < sizeof(thisColorNumberByte); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(thisColorNumberByte >> i).to_string();
					}
				}
				for (size_t i = 0; i < sizeof(row); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(row >> i).to_string();
					}
					else if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(row >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(row >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(row >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(row >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(row >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(row >> i).to_string();
					}
				}
				j += row - 1;

			}/*
			else if (thisColorNumberByte == quantityColors - 1)
			{
				uint8_t rowBit = quantityColors - 1;
				for (size_t i = 0; i < sizeof(rowBit); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(rowBit >> i).to_string();
					}
					if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(rowBit >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(rowBit >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(rowBit >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(rowBit >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(rowBit >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(rowBit >> i).to_string();
					}
				}
				
				for (size_t i = 0; i < sizeof(thisColorNumberByte); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(thisColorNumberByte >> i).to_string();
					}
				}
				row = 1;
				for (size_t i = 0; i < sizeof(row); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(row >> i).to_string();
					}
					else if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(row >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(row >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(row >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(row >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(row >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(row >> i).to_string();
					}
				}
			}*/
			else
			{
				for (size_t i = 0; i < sizeof(thisColorNumberByte); ++i)
				{
					if (quantityColors == 8)
					{
						binaryString += std::bitset<3>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 16)
					{
						binaryString += std::bitset<4>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 32)
					{
						binaryString += std::bitset<5>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 64)
					{
						binaryString += std::bitset<6>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 128)
					{
						binaryString += std::bitset<7>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 256)
					{
						binaryString += std::bitset<8>(thisColorNumberByte >> i).to_string();
					}
					else if (quantityColors == 512)
					{
						binaryString += std::bitset<9>(thisColorNumberByte >> i).to_string();
					}
				}
			}
		}
	}


	for (size_t i = 0; i < binaryString.size(); i += 8)
	{
		uint8_t thisWrite = std::stoi(binaryString.substr(i, 8), nullptr, 2);
		writeFile.write((char*)&thisWrite, sizeof(thisWrite));
	}

	std::cout << "Saved Bin" << std::endl;

}

void ModifyImage::SaveToBinHaffman(std::string fileName, bool isRow)
{
	std::ofstream writeFile(fileName, std::ios::binary);
	if (!writeFile)
	{
		std::cerr << "Error opening file for writing." << std::endl;
	}

	// Размер изображения
	int imageSizeX = originalImage.getSize().x;
	writeFile.write((char*)&imageSizeX, sizeof(imageSizeX));
	int imageSizeY = originalImage.getSize().y;
	writeFile.write((char*)&imageSizeY, sizeof(imageSizeY));

	// Количество цветов
	int quantityColorsBin = optimizedColors.size();
	writeFile.write((char*)&quantityColorsBin, sizeof(quantityColorsBin));
	// Цвета
	for (size_t i = 0; i < quantityColors; i++)
	{
		uint8_t thisColorR = optimizedColors[i].r;
		writeFile.write((char*)&thisColorR, sizeof(thisColorR));
		uint8_t thisColorG = optimizedColors[i].g;
		writeFile.write((char*)&thisColorG, sizeof(thisColorG));
		uint8_t thisColorB = optimizedColors[i].b;
		writeFile.write((char*)&thisColorB, sizeof(thisColorB));
	}

	std::string binaryString = "";

	// Заполнение пикселей
	for (size_t i = 0; i < originalImage.getSize().x; i++)
	{
		for (size_t j = 0; j < originalImage.getSize().y; j++)
		{
			uint8_t row = 0;

			sf::Color thisColor = modifyImage.getPixel(i, j);

			for (size_t k = 0; k < quantityColors; k++)
			{
				if (j + k >= originalImage.getSize().y)
					break;
				if (modifyImage.getPixel(i, j + k) == thisColor and isRow)
					row += 1;
				else
					break;
			}

			uint8_t thisColorNumberByte = 0;

			for (size_t k = 0; k < optimizedColors.size(); k++)
			{
				thisColorNumberByte = k;
				if (thisColor == optimizedColors[k])
					break;
			}

			if (row > 1)
			{
				binaryString += "01";
			}

			switch (thisColorNumberByte)
			{
			case 0:
				binaryString += "10";
				break;
			case 1:
				binaryString += "0001";
				break;
			case 2:
				binaryString += "0011";
				break;
			case 3:
				binaryString += "00101";
				break;
			case 4:
				binaryString += "00100";
				break;
			case 5:
				binaryString += "00001";
				break;
			case 6:
				binaryString += "000001";
				break;
			case 7:
				binaryString += "0000001";
				break;
			case 8:
				binaryString += "00000001";
				break;
			case 9:
				binaryString += "000000001";
				break;
			default:
				binaryString += "11";
				for (size_t i = 0; i < sizeof(thisColorNumberByte); ++i)
				{
					if (quantityColors == 127)
					{

						binaryString += std::bitset<7>(thisColorNumberByte >> i).to_string();
					}
					if (quantityColors == 255)
					{

						binaryString += std::bitset<8>(thisColorNumberByte >> i).to_string();
					}
					if (quantityColors == 511)
					{

						binaryString += std::bitset<9>(thisColorNumberByte >> i).to_string();
					}
				}
			}
			if (row > 1)
			{
				for (size_t i = 0; i < sizeof(row); ++i)
				{
					if (quantityColors == 127)
					{
						binaryString += std::bitset<7>(row >> i).to_string();
					}
					if (quantityColors == 255)
					{

						binaryString += std::bitset<8>(row >> i).to_string();
					}
					if (quantityColors == 511)
					{

						binaryString += std::bitset<9>(row >> i).to_string();
					}
				}
				j += row - 1;
			}

		}
	}

	for (size_t i = 0; i < binaryString.size(); i += 8)
	{
		uint8_t thisWrite = std::stoi(binaryString.substr(i, 8), nullptr, 2);
		writeFile.write((char*)&thisWrite, sizeof(thisWrite));
	}

	// Закрытие файла
	writeFile.close();

	std::cout << "Saved Bin" << std::endl;
}

void ModifyImage::FillImage(bool floydSteinberg)
{
	int thisDistance;
	int minDistance;
	sf::Color minDistanceColor;
	sf::Color thisColor;

	for (size_t i = 0; i < originalImage.getSize().x; i++)
	{
		for (size_t j = 0; j < originalImage.getSize().y; j++)
		{
			thisDistance = 0;
			minDistance = 1000000000;
			minDistanceColor = sf::Color(0, 0, 0);
			thisColor = originalImage.getPixel(i, j);
			for (size_t k = 0; k < quantityColors; k++)
			{
				thisDistance = pifagorMetric(thisColor, optimizedColors[k]);
				if (thisDistance < minDistance)
				{
					minDistance = thisDistance;
					minDistanceColor = optimizedColors[k];
				}
			}

			modifyImage.setPixel(i, j, minDistanceColor);

			if (floydSteinberg && i < originalImage.getSize().x - 1 && j < originalImage.getSize().y - 1)
			{
				sf::Color error = thisColor - minDistanceColor;

				sf::Color error1 = sf::Color(error.r * (7.0 / 16.0), error.g * (7.0 / 16.0), error.b * (7.0 / 16.0));
				sf::Color error2 = sf::Color((sf::Uint8)(error.r * (3.0 / 16.0)), (sf::Uint8)(error.g * (3.0 / 16.0)), (sf::Uint8)(error.b * (3.0 / 16.0)));
				sf::Color error3 = sf::Color(error.r * (5.0 / 16.0), error.g * (5.0 / 16.0), error.b * (5.0 / 16.0));
				sf::Color error4 = sf::Color(error.r * (1.0 / 16.0), error.g * (1.0 / 16.0), error.b * (1.0 / 16.0));
				sf::Color pixel1 = originalImage.getPixel(i + 1, j);
				sf::Color pixel2 = originalImage.getPixel(i - 1, j + 1);
				sf::Color pixel3 = originalImage.getPixel(i, j + 1);
				sf::Color pixel4 = originalImage.getPixel(i + 1, j + 1);
				
				if ((int)pixel1.r + (int)error1.r <= 255 && (int)pixel1.g + (int)error1.g <= 255 && (int)pixel1.b + (int)error1.b <= 255)
					originalImage.setPixel(i + 1, j, pixel1 + error1);
				if (pixel2.r + error2.r <= 255 && pixel2.g + error2.g <= 255 && pixel2.b + error2.b <= 255)
					originalImage.setPixel(i - 1, j + 1, pixel2 + error2);
				if (pixel3.r + error3.r <= 255 && pixel3.g + error3.g <= 255 && pixel3.b + error3.b <= 255)
					originalImage.setPixel(i, j + 1, pixel3 + error3);
				if (pixel4.r + error4.r <= 255 && pixel4.g + error4.g <= 255 && pixel4.b + error4.b <= 255)
					originalImage.setPixel(i + 1, j + 1, pixel4 + error4);
			}
		}
	}

	std::cout << "Final Fill" << std::endl;
}

void ModifyImage::FillFloydImage()
{
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			for (size_t k = 0; k < 16; k++)
			{
				colors255.push_back(sf::Color(i * 16, j * 16, k * 16));
			}
		}
	}

	int thisDistance;
	int minDistance;
	sf::Color newPixel;
	sf::Color oldPixel;

	for (size_t i = 0; i < originalImage.getSize().x - 1; i++)
	{
		for (size_t j = 0; j < originalImage.getSize().y - 1; j++)
		{
			thisDistance = 0;
			minDistance = 1000000000;
			newPixel = sf::Color(0, 0, 0);
			oldPixel = originalImage.getPixel(i, j);
			for (size_t k = 0; k < quantityColors; k++)
			{
				thisDistance = pifagorMetric(oldPixel, colors255[k]);
				if (thisDistance < minDistance)
				{
					minDistance = thisDistance;
					newPixel = colors255[k];
				}
			}


			sf::Color error = oldPixel - newPixel;

			sf::Color error1 = sf::Color(error.r * (7.0 / 16.0), error.g * (7.0 / 16.0), error.b * (7.0 / 16.0));
			sf::Color error2 = sf::Color(error.r * (3.0 / 16.0), error.g * (3.0 / 16.0), error.b * (3.0 / 16.0));
			sf::Color error3 = sf::Color(error.r * (5.0 / 16.0), error.g * (5.0 / 16.0), error.b * (5.0 / 16.0));
			sf::Color error4 = sf::Color(error.r * (1.0 / 16.0), error.g * (1.0 / 16.0), error.b * (1.0 / 16.0));

			originalImage.setPixel(i + 1, j, originalImage.getPixel(i + 1, j) + error1);
			originalImage.setPixel(i - 1, j + 1, originalImage.getPixel(i - 1, j + 1) + error2);
			originalImage.setPixel(i, j + 1, originalImage.getPixel(i, j + 1) + error3);
			originalImage.setPixel(i + 1, j + 1, originalImage.getPixel(i + 1, j + 1) + error4);


			modifyImage.setPixel(i, j, newPixel);
		}
	}

	std::cout << "Final Fill" << std::endl;
}
