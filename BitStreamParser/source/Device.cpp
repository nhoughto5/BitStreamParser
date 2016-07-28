#include "stdafx.h"
#include "Device.h"


Device::Device(): maxX(0), maxY(0)
{
}


Device::~Device()
{
}

bool Device::containsCoordinate(int x_, int y_) {
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
	//============ IOB Definitions ==========//
	//Top
	pinSites.push_back(IO_Site("DIFFM","PAD2", 2, 98, "IO_L07P_0", 3, "TIOIS_X1Y23", true, Coordinate(0,1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD1", 1, 99, "IO_L07N_0/HSWAP", 0, "TIOIS_X1Y23", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD8", 8, 94, "IO_L06P_0", 0, "TIOIS_X5Y23", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD7", 7, 95, "IO_L06N_0/VREF_0", 0, "TIOIS_X5Y23", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("IOB", "PAD9", 9, 92, "IO", 0, "TIOIS_X6Y23", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD11", 11, 90, "IO_L05P_0/GCLK10", 0, "TIOIS_X7Y23", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD10", 10, 91, "IO_L05N_0/GCLK11", 0, "TIOIS_X7Y23", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFMI", "IPAD13", 13, 88, "IP_L04P_0/GCLK8", 0, "TIBUFS_X8Y23", false, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFSI", "IPAD12", 12, 89, "IP_L04N_0/GCLK9", 0, "TIBUFS_X8Y23", false, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD15", 15, 85, "IO_L03P_0/GCLK6", 0, "TIOIS_X9Y23", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD14", 14, 86, "IO_L03N_0/GCLK7", 0, "TIOIS_X9Y23", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD18", 18, 83, "IO_L02P_0/GCLK4", 0, "TIOIS_X11Y23", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD17", 17, 84, "IO_L02N_0/GCLK5", 0, "TIOIS_X11Y23", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD25", 25, 78, "IO_L01P_0", 0, "TIOIS_X15Y23", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD24", 24, 79, "IO_L01N_0", 0, "TIOIS_X15Y23", true, Coordinate(1, 1)));

	//Right
	pinSites.push_back(IO_Site("DIFFS", "PAD34", 34, 71, "IO_L07N_1", 1, "RIOIS_X17Y16", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD35", 35, 70, "IO_L07P_1", 1, "RIOIS_X17Y16", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("IBUF", "IPAD36", 36, 69, "IP/VREF_1", 1, "RIBUFS_PCI_X17Y15", false, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD37", 37, 68, "IO_L06N_1/RHCLK7", 1, "RIOIS_PCI_X17Y14", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD38", 38, 67, "IO_L06P_1/RHCLK6", 1, "RIOIS_PCI_X17Y14", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD39", 39, 66, "IO_L05N_1/RHCLK5", 1, "RIOIS_CLK_PCI_X17Y12", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD40", 40, 65, "IO_L05P_1/RHCLK4/IRDY1", 1, "RIOIS_CLK_PCI_X17Y12", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD42", 42, 63, "IO_L04N_1/RHCLK3/TRDY1", 1, "RIOIS_PCI_X17Y10", true, Coordinate(1, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD43", 43, 62, "IO_L04P_1/RHCLK2", 1, "RIOIS_PCI_X17Y10", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD44", 44, 61, "IO_L03N_1/RHCLK1", 1, "RIOIS_PCI_X17Y8", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD45", 45, 60, "IO_L03P_1/RHCLK0", 1, "RIOIS_PCI_X17Y8", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD48", 48, 58, "IO_L02N_1", 1, "RIOIS_X17Y5", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD49", 49, 57, "IO_L02P_1", 1, "RIOIS_X17Y5", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD53", 53, 54, "IO_L01N_1", 1, "RIOIS_X17Y1", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD54", 54, 53, "IO_L01P_1", 1, "RIOIS_X17Y1", true, Coordinate(1, 0)));

	//Bottom
	pinSites.push_back(IO_Site("DIFFS", "PAD55", 55, 50, "IO_L09N_2", 2, "BIOIS_X16Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD56", 56, 49, "IO_L09P_2/VS0", 2, "BIOIS_X16Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD58", 58, 48, "IO_L08N_2/VS1", 2, "BIOIS_X14Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD59", 59, 47, "IO_L08P_2/VS2", 2, "BIOIS_X14Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD61", 61, 44, "IO_L07N_2/DIN/D0", 2, "BIOIS_X12Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD62", 62, 43, "IO_L07P_2/M0", 2, "BIOIS_X12Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("IOB", "PAD63", 63, 42, "IO_M1", 2, "BIOIS_X11Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD64", 64, 41, "IO_L06N_2/D1/GCLK3", 2, "BIOIS_X10Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD65", 65, 40, "IO_L06P_2/D2/GCLK2", 2, "BIOIS_X10Y0", true, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFSI", "IPAD66", 66, 39, "IP_L05N_2/M2/GCLK1", 2, "BIOIS_X9Y0", false, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFMI", "IPAD67", 67, 38, "IP_L05P_2/RDWR_B/GCLK0", 2, "BIOIS_X9Y0", false, Coordinate(1, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD68", 68, 36, "IO_L04N_2/D3/GCLK15", 2, "BIOIS_X8Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD69", 69, 35, "IO_L04P_2/D4/GCLK14", 2, "BIOIS_X8Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("IOB", "PAD70", 70, 34, "IO/D5", 2, "BIOIS_X7Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD71", 71, 33, "IO_L03N_2/D6/GCLK13", 2, "BIOIS_X6Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD72", 72, 32, "IO_L03P_2/D7/GCLK12", 2, "BIOIS_X6Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFSI", "IPAD73", 73, 30, "IP/VREF_2", 2, "BIOIS_X5Y0", false, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD75", 75, 27, "IO_L02N_2/MOSI/CSI_B", 2, "BIOIS_X4Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD76", 76, 26, "IO_L02P_2/DOUT/BUSY", 2, "BIOIS_X4Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD78", 78, 25, "IO_L01N_2/INIT_B", 2, "BIOIS_X2Y0", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD79", 79, 24, "IO_L01P_2/CSO_B", 2, "BIOIS_X2Y0", true, Coordinate(0, 0)));

	//Left
	pinSites.push_back(IO_Site("DIFFM", "PAD83", 83, 22, "IO_L07P_3", 3, "LIOIS_X0Y2", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD82", 82, 23, "IO_L07N_3", 3, "LIOIS_X0Y2", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD92", 92, 17, "IO_L06P_3/LHCLK6", 3, "LIOIS_X0Y9", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD91", 91, 18, "IO_L06N_3/LHCLK7", 3, "LIOIS_X0Y9", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFM", "PAD94", 94, 15, "IO_L05P_3/LHCLK4/TRDY2", 3, "LIOIS_CLK_PCI_X0Y11", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("DIFFS", "PAD93", 93, 16, "IO_L05N_3/LHCLK5", 3, "LIOIS_CLK_PCI_X0Y11", true, Coordinate(0, 0)));
	pinSites.push_back(IO_Site("IBUF", "IPAD95", 95, 13, "IP", 3, "LIBUFS_CLK_PCI_X0Y12", false, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD97", 97, 11, "IO_L04P_3/LHCLK2", 3, "LIOIS_PCI_X0Y13", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD96", 97, 12, "IO_L04N_3/LHCLK3/IRDY2", 3, "LIOIS_PCI_X0Y13", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD99", 99, 9, "IO_L03P_3/LHCLK0", 3, "LIOIS_PCI_X0Y15", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD98", 98, 10, "IO_L03N_3/LHCLK1", 3, "LIOIS_PCI_X0Y15", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD106", 106, 4, "IO_L02P_3", 3, "LIOIS_X0Y20", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD105", 105, 5, "IO_L02N_3/VREF_3", 3, "LIOIS_X0Y20", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFM", "PAD108", 108, 2, "IO_L01P_3", 3, "LIOIS_X0Y22", true, Coordinate(0, 1)));
	pinSites.push_back(IO_Site("DIFFS", "PAD107", 107, 3, "IO_L01N_3", 3, "LIOIS_X0Y22", true, Coordinate(0, 1)));
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