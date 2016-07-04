#include "stdafx.h"
#include "addressLibrary.h"
#include "structs.h"

addressLibrary::addressLibrary()
{
}


addressLibrary::~addressLibrary()
{
}

void addressLibrary::addEntry(DeviceType deviceType, lutOffsetResponse offset, Coordinate xyCoordinate, std::string location, DeviceConfiguration deviceConfig) {
	library.push_back(libraryEntry(deviceType, offset, xyCoordinate, location, deviceConfig));
}
std::vector<libraryEntry> addressLibrary::getLibrary(){
	return library;
}