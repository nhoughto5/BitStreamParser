#pragma once
#include <vector>
#include <set>
#include "structs.h"
class Device
{
public:
	Device();
	~Device();

	void setDevice_Xa3s100E();
	std::vector<Coordinate> getLUTCoordinates();
	int getMaxX(), getMaxY();
private:
	std::vector<Coordinate> LUTCoordinates;
	std::vector<Coordinate> missingAddresses;
	std::vector<IO_Site> pinSites;
	bool containsCoordinate(int x, int y);
	int maxX, maxY;

};

