#pragma once
#include <string>
#include <vector>
#include "enums.h"
#include "structs.h"

class addressLibrary
{
public:
	addressLibrary();
	~addressLibrary();

	void addEntry(DeviceType deviceType, lutOffsetResponse offset, Coordinate xyCoordinate, std::string location = "NA", DeviceConfiguration deviceConfig = NONE);
	std::vector<libraryEntry> getLibrary();
private:
	std::vector<libraryEntry> library;
};

