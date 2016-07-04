#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "structs.h"
class BitStreamAnalyzer
{
public:
	BitStreamAnalyzer();
	~BitStreamAnalyzer();

	void readBitFile(std::string binFilePath);
	lutOffsetResponse getByteOffSet();
private:
	std::vector<std::string> hexByteValues;
	const char *LUT_Hex_Codes[7] = { "FFF0FFFF","FFFFFAFA","FAFAFFFF", "FFFFFFCC", "FFCCFFFF", "FCFCFFFF", "FFFFFCFC" };
};

