#include "stdafx.h"
#include "Device.h"


Device::Device()
{
}


Device::~Device()
{
}

void Device::setDevice_Xa3s100E() {
	std::set<coordinate> missingAddresses;

	//====== LUTs missing due to block RAM ===//
	for (int y = 4; y < 40; ++y) {
		for (int x = 4; x < 12; ++x) {
			//missingAddresses.insert();
		}
	}

}