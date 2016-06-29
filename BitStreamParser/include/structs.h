#ifndef STRUCTS_H
#define STRUCTS_H
#pragma once
#include "enums.h"
struct Coordinate {
	int X;
	int Y;
	Coordinate(int x, int y) : X(x), Y(y) {}
};

struct libraryEntry {
	DeviceType deviceType;
	int offset;
	Coordinate xyCoordinate;
	std::string location;
	DeviceConfiguration deviceConfig;
	libraryEntry(DeviceType deviceType, int offset, Coordinate xyCoordinate, std::string location, DeviceConfiguration deviceConfig) :
		deviceType(deviceType),
		offset(offset),
		xyCoordinate(xyCoordinate),
		location(location),
		deviceConfig(deviceConfig)
	{
		
	}
};
#endif // !1