#pragma once

#include "ModifyImage.h"

class ModifyImageStaticCubes : public ModifyImage
{
private:
	// Количество кубов по одной стороне
	int quantityCubes;
	// Разделение цветового пространства на кубы и подсчет количества цветов в каждом
	std::vector<std::vector<std::vector<int>>> colorCubes;


public:
	ModifyImageStaticCubes() {}
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="fileName">Название файла изображения</param>
	/// <param name="_quantityColor">Количество цветов (2^n - 1)</param>
	ModifyImageStaticCubes(std::string folder, std::string fileName, int _quantityColor, int _quantityCubes);

	

	void FillColorCubes();

	void FillOptimizedColors();
	


};
