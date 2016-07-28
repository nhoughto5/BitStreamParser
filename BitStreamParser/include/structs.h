#ifndef STRUCTS_H
#define STRUCTS_H
#pragma once
#include "enums.h"
struct Coordinate {
	int X;
	int Y;
	Coordinate(int x, int y) : X(x), Y(y) {}
};
struct lutOffsetResponse {
	int offset;
	std::string hexCode;
	//lutOffsetResponse() {}
	//lutOffsetResponse(int o_, std::string h_): offset(o_), hexCode(h_) {}
};
struct IO_Site {
	std::string Type;
	std::string IOB_Alias;
	int padNumber;
	int pin_SiteNumber;
	std::string pinName;
	int IO_Bank;
	std::string Tile;
	bool Accessible;
	Coordinate Clock_Region;
	IO_Site(std::string Type_, std::string IOB_Alias_, int padNumber_, int pin_SiteNumber_, std::string pinName_, int IO_Bank_, std::string Tile_, bool accessible_, Coordinate Clock_Region_) :
		Type(Type_),
		IOB_Alias(IOB_Alias_),
		padNumber(padNumber_),
		pin_SiteNumber(pin_SiteNumber_),
		pinName(pinName_),
		IO_Bank(IO_Bank_),
		Tile(Tile_),
		Accessible(accessible_),
		Clock_Region(Clock_Region_)
	{
	}
};
struct libraryEntry {
	DeviceType deviceType;
	lutOffsetResponse offset;
	Coordinate xyCoordinate;
	std::string location;
	DeviceConfiguration deviceConfig;
	libraryEntry(DeviceType deviceType, lutOffsetResponse offset, Coordinate xyCoordinate, std::string location, DeviceConfiguration deviceConfig) :
		deviceType(deviceType),
		offset(offset),
		xyCoordinate(xyCoordinate),
		location(location),
		deviceConfig(deviceConfig)
	{
		
	}
};


#endif // !1