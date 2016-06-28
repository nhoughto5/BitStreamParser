#pragma once
#include <vector>
#include <set>
struct coordinate {
	int X;
	int Y;
};
class Device
{
public:
	Device();
	~Device();

	void setDevice_Xa3s100E();
private:
	std::vector<coordinate> LUTCoordinates;

};

