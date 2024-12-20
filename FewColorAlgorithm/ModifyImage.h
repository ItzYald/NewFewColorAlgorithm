#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

#include "SFML/Graphics.hpp"

#include "Point.h"

class ModifyImage
{
public:
	sf::Image originalImage;
	sf::Image modifyImage;

	int quantityColors;

	std::vector<sf::Color> optimizedColors;
	std::vector<sf::Color> colors255;

	static float pifagorMetric(Point vec1, sf::Color vec2);
	static float pifagorMetric(sf::Color vec1, sf::Color vec2);
	static float maxCoordsDistance(Point vec1, sf::Color vec2);
	static float maxCoordsDistance(sf::Color vec1, sf::Color vec2);

	

	void SaveToJpg(std::string fileName);
	/// <summary>
	/// Сохранение изображения в bin file
	/// </summary>
	/// <param name="fileName">Путь к файлу</param>
	/// <param name="typeCompress">
	/// Тип дополнительного сжатия без потерь:
	/// 0 - без дополнительного сжатия
	/// 1 - линейное сжатие
	/// 2 - квадратичное сжатие
	/// </param>
	void SaveToBin(std::string fileName, int typeCompress);

	void SaveToBinHaffman(std::string fileName, bool isRow);
	// Заполнение изображения пикселями
	void FillImage(bool floydSteinberg);

	void FillFloydImage();

};

//sf::Color operator*(double d, const sf::Color& c)
//{
//	return sf::Color(std::max(c.r * d, 255.0), std::max(c.g * d, 255.0), std::max(c.b * d, 255.0));
//}