#pragma once

#include "ModifyImage.h"

class ModifyImageStaticCubes : public ModifyImage
{
private:
	// ���������� ����� �� ����� �������
	int quantityCubes;
	// ���������� ��������� ������������ �� ���� � ������� ���������� ������ � ������
	std::vector<std::vector<std::vector<int>>> colorCubes;


public:
	ModifyImageStaticCubes() {}
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="fileName">�������� ����� �����������</param>
	/// <param name="_quantityColor">���������� ������ (2^n - 1)</param>
	ModifyImageStaticCubes(std::string folder, std::string fileName, int _quantityColor, int _quantityCubes);

	

	void FillColorCubes();

	void FillOptimizedColors();
	


};
