#include "stdafx.h"
#include "Device.h"


Device::Device(): maxX(0), maxY(0)
{
}


Device::~Device()
{
}

bool Device::containsCoordinate(int x_, int y_) {
	//auto target = coordinate(x, y);
	//if (std::find(missingAddresses.begin(), missingAddresses.end(), target) != missingAddresses.end()) {
	//	/* v contains x */
	//	return true;
	//}
	//else {
	//	/* v does not contain x */
	//	return false;
	//}
	for (std::vector<Coordinate>::const_iterator it = missingAddresses.begin(); it != missingAddresses.end(); ++it) {
		if ((it->X == x_) && (it->Y == y_) ) {
			return true;
		}
	}
	return false;
}

void Device::setDevice_Xa3s100E() {
	missingAddresses.clear();
	LUTCoordinates.clear();
	maxX = 31; maxY = 43;


	//====== LUTs missing due to block RAM ===//
	for (int y = 4; y < 40; ++y) {
		for (int x = 4; x < 12; ++x) {
			missingAddresses.push_back(Coordinate(x,y));
		}
	}

	//===== LUTs missing due to DCMs ==== //
	for (int y = 0; y <= 7; ++y) {
		for (int x = 14; x < 24; ++x) {
			missingAddresses.push_back(Coordinate(x, y));
		}
	}
	for (int y = 36; y <= 43; ++y) {
		for (int x = 14; x < 24; ++x) {
			missingAddresses.push_back(Coordinate(x, y));
		}
	}

	//==== Set LUT coordinates for device ==== //
	for (int y = 0; y <= maxY; ++y) {
		for (int x = 0; x <= maxX; ++x) {
			if (!containsCoordinate(x,y)) {
				LUTCoordinates.push_back(Coordinate(x,y));
			}
		}
	}
}

std::vector<Coordinate> Device::getLUTCoordinates() {
	return LUTCoordinates;
}

int Device::getMaxX() {
	return maxX;
}

int Device::getMaxY() {
	return maxY;
}